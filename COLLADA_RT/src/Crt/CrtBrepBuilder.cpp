#include "Crt/CrtBrepBuilder.h"
#include "Crt/CrtUtils.h"
#include <shapefix_shape.hxx>
#include <brepgprop_face.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

CrtBrep::~CrtBrep()
{
	// will only clear the pointer of toposh_shape
	data = NULL;
	mShape.Nullify();
}

// This functions will load vertices of every BREP and 
// then init them to corresponding shape structure.
bool CrtBrep::initVertices(domVertices *brepVertices)
{
	domUint num_vertices;
	domListOfFloats * position_floats = NULL;
	domInputLocal_Array& brep_vertices_inputs = brepVertices->getInput_array();
	
	// Though there is a for loop, it should be only one input for vertices based on schema
	for(CrtUInt i=0; i<brep_vertices_inputs.getCount(); i++)
	{
		// getSource() -> url
		// getElement() url -> elment
		// 
		domSource * source = (domSource*) (domElement*) brep_vertices_inputs[i]->getSource().getElement();
		if(CrtCmp("POSITION", brep_vertices_inputs[i]->getSemantic())) {
			num_vertices = (source->getFloat_array()->getCount())/3;
			position_floats = & source->getFloat_array()->getValue();
			
			// put data into Builder
			for (domUint j = 0;j < num_vertices;j++)
			{
				double x, y, z;
				position_floats->get3at((size_t)j * 3, x, y, z);
				gp_Pnt p;
				p.SetCoord(x, y, z);
				TopoDS_Vertex v;
				mBuilder.MakeVertex(v, p, dTol);
				// do not need to add instead to substitute? Will it be slower or faster?
				mVertexMap.Add(v);
			}
		}
	}
	return true;
}

// PRE: vertices have been built.
bool CrtBrep::initEdges(domEdges *brepEdges) // Edge element
{
	enum edge_offset_index{
		CURVE_OFFSET_INDEX,
		PARAM_OFFSET_INDEX,
		EDGE_OFFSET_NUM
	};

	// init inputs, count and sid ref and list
	brepComponent edge_coms(brepEdges->getInput_array());
	edge_coms.p_list = (brepEdges->getP())->getValue();
	edge_coms.num = brepEdges->getCount();
	edge_coms.sid_vector.resize(1);
	edge_coms.sid_vector.at(0) = NULL; // CURVE
	edge_coms.list_floats_vector.resize(1);
	edge_coms.list_floats_vector.at(0) = NULL; // PARAM
	
	// init inputs arrays to members of brepComponent 
	for(size_t i=0; i < edge_coms.num_inputs; i++)
	{
		domSource * source;

		// compare name
		if (CrtCmp("CURVE", (* edge_coms.input_arrays)[i]->getSemantic()))
		{
			// resolve SID source
			source = (domSource *) (* edge_coms.input_arrays)[i]->getSource().getElement().cast();
			// init the SID array
			edge_coms.sid_vector.at(0) = source->getSIDREF_array();
			// get offset information of curve
			edge_coms.offset[CURVE_OFFSET_INDEX] = (* edge_coms.input_arrays)[i]->getOffset();
			// check valid pointer or not
			if (edge_coms.sid_vector.at(0) == NULL)
				return false;
		}
		else if (CrtCmp("PARAM", (* edge_coms.input_arrays)[i]->getSemantic()))
		{
			// resolve param source
			source = (domSource *) (* edge_coms.input_arrays)[i]->getSource().getElement().cast();
			// init the parameter array
			edge_coms.list_floats_vector.at(0) = & source->getFloat_array()->getValue();
			// get offset information of param
			edge_coms.offset[PARAM_OFFSET_INDEX] = (* edge_coms.input_arrays)[i]->getOffset();
			// check valid pointer or not
			if (edge_coms.list_floats_vector.at(0) == NULL)
				return false;
		}
	}
	
	AbsCurve_OCC_Parser* cur_occ_parser = new AbsCurve_OCC_Parser(); // define pointer for curve parser
	Handle( Geom_Curve ) curve_occ;	// define curve pointer for OCC
	
	// set container to be the brep element
	daeSIDResolver resolver(data, "");

	// load that curve and two vertices
	for (size_t i = 0; i < (size_t)edge_coms.num;i++)
	{
		// find index of curve: curve[3 * i] OFFSET as 0
		resolver.setTarget( (string("./") + (edge_coms.sid_vector.at(0)->getValue()).get( (size_t)edge_coms.p_list[edge_coms.num_inputs * i + (size_t)edge_coms.offset[CURVE_OFFSET_INDEX]] )).c_str() );
		
		// resolve it by sid
		domCurveType * brepCurves = NULL;
		brepCurves = daeSafeCast <domCurveType> (resolver.getElement());
		
		// if error is critical then skip this element
		if (brepCurves == NULL)
		{
			delete cur_occ_parser;
			return false;
		}

		// load curve:
		cur_occ_parser->ReadCurve(brepCurves, curve_occ);

		// find the indices of two vertices of curve: OFFSET as 1 and 2 
		// this do not need inputs because of mVertexMap
		domUint vIndex1 = edge_coms.p_list[edge_coms.num_inputs * i + 1];
		domUint vIndex2 = edge_coms.p_list[edge_coms.num_inputs * i + 2];

		// find the orientation of edge
		domUint ori = edge_coms.p_list[edge_coms.num_inputs * i + 3];

		// find parameters:
		domFloat u[2];
		size_t base_index = (size_t)edge_coms.p_list[edge_coms.num_inputs * i + (size_t)edge_coms.offset[PARAM_OFFSET_INDEX]];
		for (size_t j = 0;j < 2;j++)
			u[j] = edge_coms.list_floats_vector.at(0)->get(  base_index * 2 + j);
		
		// Make edge
		TopoDS_Vertex v1 = TopoDS::Vertex( mVertexMap.FindKey( (Standard_Integer)vIndex1 + 1 ) );
		TopoDS_Vertex v2 = TopoDS::Vertex( mVertexMap.FindKey( (Standard_Integer)vIndex2 + 1 ) );
		TopoDS_Edge e;

		// degenerate edge or not:
		if ( !curve_occ.IsNull() )
		{
			// there is curve related this edge:
			mBuilder.MakeEdge( e, curve_occ, dTol );
		}
		else
		{
			// set it as degerated edge
			mBuilder.MakeEdge( e );
            mBuilder.Degenerated( e, true );
		}

		// related orientation with vertex:
		v1.Orientation( ori == 1 ? TopAbs_FORWARD : TopAbs_REVERSED );
        mBuilder.Add( e, v1 );
        v2.Orientation( ori == 0 ? TopAbs_FORWARD : TopAbs_REVERSED );
        mBuilder.Add( e, v2 );

		// put vertex and parameters into edge information:
		if ( !curve_occ.IsNull() )
        {
            if ( ori == 1 )
            {
                mBuilder.UpdateVertex( v1, u[0], e, dTol );
                mBuilder.UpdateVertex( v2, u[1], e, dTol );
            }

            else
            {
                mBuilder.UpdateVertex( v1, u[1], e, dTol );
                mBuilder.UpdateVertex( v2, u[0], e, dTol );
            }
        }
        else
        {
            mBuilder.Range( e, u[0], u[1] );
        }

		// put it into EdgeMap
        mEdgeMap.Add( e );
	} // 
	
	
	// release parser
	delete cur_occ_parser;
	return true;
}

bool CrtBrep::initWires(domWires *wires)
{
	enum wire_offset_index
	{
		EDGE_OFFSET_INDEX,
		ORIENTATION_OFFSET_INDEX,
		NUM_OFFSET_INDEX
	};

	brepComponent wire_coms(wires->getInput_array());
	wire_coms.p_list = (wires->getP())->getValue();
	wire_coms.v_list = (wires->getVcount())->getValue(); 
	wire_coms.num = wires->getCount();

	wire_coms.list_floats_vector.clear();
	wire_coms.name_vector.clear();
	wire_coms.sid_vector.clear();

	size_t index = 0;
	size_t index_edge = 0;
	size_t index_orientation = 0;
	
	// read the offset
	for(size_t i=0; i < wire_coms.num_inputs; i++)
	{
		if (CrtCmp("EDGE", (* (wire_coms.input_arrays))[i]->getSemantic()))
		{
			wire_coms.offset[EDGE_OFFSET_INDEX] = ( * (wire_coms.input_arrays))[i]->getOffset();
		}
		else if (CrtCmp("ORIENTATION", (* (wire_coms.input_arrays))[i]->getSemantic()))
		{
			wire_coms.offset[ORIENTATION_OFFSET_INDEX] = ( * (wire_coms.input_arrays))[i]->getOffset();
		}
	}

	// Make wire
	for (size_t i = 0; i < wire_coms.num;i++)
	{
		TopoDS_Wire wire;
		mBuilder.MakeWire( wire );

		// link edges to current wire
		for (size_t j = 0;j < wire_coms.v_list[i];j++)
		{
			size_t base_index = index * wire_coms.num_inputs;
			index_edge = base_index + (size_t) wire_coms.offset[EDGE_OFFSET_INDEX];
			index_orientation = base_index + (size_t) wire_coms.offset[ORIENTATION_OFFSET_INDEX];
			// get edge from edgemap
			TopoDS_Edge e = TopoDS::Edge( mEdgeMap.FindKey ( 
				(Standard_Integer) wire_coms.p_list[index_edge] + 1) );
			// init orientation
			e.Orientation( wire_coms.p_list[index_orientation] == 1 ? TopAbs_FORWARD : TopAbs_REVERSED );
            mBuilder.UpdateEdge( e, dTol );
            mBuilder.Add( wire, e );
			// move to next edge
			index++;
		}
		mWireMap.Add(wire);
	}

	return true;
}

bool CrtBrep::initFaces(domFaces *faces)
{
	enum face_offset_index
	{
		SURFACE_OFFSET_INDEX,
		WIRE_OFFSET_INDEX,
		MATERIAL_OFFSET_INDEX,
		ORIENTATION_OFFSET_INDEX,
		NUM_OFFSET_INDEX
	};

	// init inputs, count and sid ref and list
	brepComponent face_coms(faces->getInput_array());
	face_coms.p_list = (faces->getP())->getValue();
	face_coms.v_list = (faces->getVcount())->getValue(); 
	face_coms.num = faces->getCount();

	face_coms.sid_vector.resize(1);
	face_coms.sid_vector.at(0) = NULL; // SURFACE
	
	face_coms.list_floats_vector.clear();

	face_coms.name_vector.resize(1);
	face_coms.name_vector.at(0) = NULL;// MATERIAL
			
	size_t index = 0;

	// init inputs arrays to members of brepComponent
	for(size_t i=0; i < face_coms.num_inputs; i++)
	{
		domSource * source;

		// compare name
		if (CrtCmp("SURFACE", (* (face_coms.input_arrays))[i]->getSemantic()))
		{
			// resolve SID source
			source = (domSource *) (* face_coms.input_arrays)[i]->getSource().getElement().cast();
			// init the SID array
			face_coms.sid_vector.at(0) = source->getSIDREF_array();
			// get offset information of curve
			face_coms.offset[SURFACE_OFFSET_INDEX] = (* face_coms.input_arrays)[i]->getOffset();
			// check valid pointer or not
			if (face_coms.sid_vector.at(0) == NULL)
				return false;
		}
		else if (CrtCmp("WIRE", (* (face_coms.input_arrays))[i]->getSemantic()))
		{
			face_coms.offset[WIRE_OFFSET_INDEX] = ( * (face_coms.input_arrays))[i]->getOffset();
		}
		else if (CrtCmp("MATERIAL", (* (face_coms.input_arrays))[i]->getSemantic()))
		{
			// resolve Name source
			source = (domSource *) (* face_coms.input_arrays)[i]->getSource().getElement().cast();
			// init the name array
			face_coms.name_vector.at(0) = source->getName_array();
			// get offset information of surface
			face_coms.offset[MATERIAL_OFFSET_INDEX] = ( * (face_coms.input_arrays))[i]->getOffset();
			// check valid:
			if (face_coms.name_vector.at(0) == NULL)
				return false;
		}
		else if (CrtCmp("ORIENTATION", (* (face_coms.input_arrays))[i]->getSemantic()))
		{
			face_coms.offset[ORIENTATION_OFFSET_INDEX] = ( * (face_coms.input_arrays))[i]->getOffset();
		}
	}

	// build OCC shape:
	AbsSurface_OCC_Parser* sur_occ_parser = new AbsSurface_OCC_Parser(); // define pointer for curve parser
	Handle( Geom_Surface ) surface_occ;	// define curve pointer for OCC

	// set container to be the brep element
	daeSIDResolver resolver(data, "");

	// load that surface and several wires
	for (size_t i = 0; i < (size_t)face_coms.num;i++)
	{
		// find index of surface: surface[4 * index] OFFSET as 0
		size_t sur_index = (size_t)face_coms.p_list[face_coms.num_inputs * index + (size_t)face_coms.offset[SURFACE_OFFSET_INDEX]];
		daeString sur_sid = face_coms.sid_vector.at(0)->getValue().get( sur_index );
		resolver.setTarget( (string("./") + sur_sid).c_str() );
		
		// resolve it by sid
		domSurfaceType * brepSurfaces = NULL;
		brepSurfaces = daeSafeCast <domSurfaceType> (resolver.getElement());

		// if error is critical then skip this element
		if (brepSurfaces == NULL)
		{
			delete sur_occ_parser;
			return false;
		}

		// load surface:
		sur_occ_parser->ReadSurface(brepSurfaces, surface_occ);

		// Make face by surface first:
		if (!surface_occ.IsNull())
		{
			TopoDS_Face face;
			mBuilder.MakeFace( face, surface_occ, dTol );
			
#if DEBUG_SHAPE_CHECKING
			// check whether current wire is valid or not
			Standard_Boolean ori_sur_status = BRepAlgo::IsValid(face);
#endif			
			// add wire to current surface
			for (size_t j = 0;j < face_coms.v_list[i];j++)
			{			
				size_t index_wire = index * face_coms.num_inputs + (size_t)face_coms.offset[WIRE_OFFSET_INDEX];
				TopoDS_Wire w = TopoDS::Wire( mWireMap.FindKey( face_coms.p_list.get(index_wire) + 1) );
#if DEBUG_SHAPE_CHECKING
				size_t wire_index_tmp = face_coms.p_list.get(index_wire);
				// check whether current wire is valid or not
				BRepAlgo::IsValid(w);
					//return false;
#endif
				// orientation
				size_t index_orientation = index * face_coms.num_inputs + (size_t)face_coms.offset[ORIENTATION_OFFSET_INDEX];
				w.Orientation( face_coms.p_list.get(index_orientation) == 1 ? TopAbs_FORWARD : TopAbs_REVERSED );
				mBuilder.Add( face, w );	

#if DEBUG_SHAPE_CHECKING
				//ShapeFix_Wire sfw(w, face, dTol);
				//sfw.Perform();
#endif
				index++;
			}
#if DEBUG_SHAPE_CHECKING
			Standard_Boolean status = BRepAlgo::IsValid(face) ;
#endif
			// add face to map
			mFaceMap.Add(face);
		}
		else
			return false;
	}

	return true;
}

bool CrtBrep::initShells(domShells *shells)
{
	enum shell_offset_index
	{
		FACE_OFFSET_INDEX,
		ORIENTATION_OFFSET_INDEX,
		NUM_OFFSET
	};

	brepComponent shell_coms(shells->getInput_array());
	shell_coms.p_list = (shells->getP())->getValue();
	shell_coms.v_list = (shells->getVcount())->getValue(); 
	shell_coms.num = shells->getCount();

	shell_coms.list_floats_vector.clear();
	shell_coms.name_vector.clear();
	shell_coms.sid_vector.clear();

	size_t index = 0;
	size_t index_face = 0;
	size_t index_orientation = 0;

	// read the offset
	for (size_t i = 0;i < shell_coms.num_inputs;i++)
	{
		if (CrtCmp("FACE", ( * (shell_coms.input_arrays))[i]->getSemantic()) )
		{
			shell_coms.offset[FACE_OFFSET_INDEX] = ( * (shell_coms.input_arrays))[i]->getOffset();
		}
		else if(CrtCmp("ORIENTATION", ( * (shell_coms.input_arrays))[i]->getSemantic()) )
		{
			shell_coms.offset[ORIENTATION_OFFSET_INDEX] = ( * (shell_coms.input_arrays))[i]->getOffset();
		}
	}

	// build shells
	for (size_t i = 0;i < shell_coms.num;i++)
	{
		TopoDS_Shell shell;
		mBuilder.MakeShell( shell );
		
		for (size_t j = 0;j < shell_coms.v_list[i];j++)
		{
			size_t base_index = index * shell_coms.num_inputs;
			
			index_face = (size_t)shell_coms.p_list[base_index + (size_t)shell_coms.offset[FACE_OFFSET_INDEX]];
			index_orientation = shell_coms.p_list[base_index + (size_t)shell_coms.offset[ORIENTATION_OFFSET_INDEX]];

			TopoDS_Face f = TopoDS::Face( mFaceMap.FindKey( index_face + 1) );
			f.Orientation( index_orientation == 1 ? TopAbs_FORWARD : TopAbs_REVERSED );
            mBuilder.Add( shell, f );
			index++;
        }

		mShellMap.Add( shell );
	}

	return true;
}

bool CrtBrep::initSolids(domSolids *solids)
{
	enum solid_offset_index
	{
		SHELL_OFFSET_INDEX,
		ORIENTATION_OFFSET_INDEX,
		NUM_OFFSET
	};

	brepComponent solid_coms(solids->getInput_array());
	solid_coms.p_list = (solids->getP())->getValue();
	solid_coms.v_list = (solids->getVcount())->getValue(); 
	solid_coms.num = solids->getCount();

	solid_coms.list_floats_vector.clear();
	solid_coms.name_vector.clear();
	solid_coms.sid_vector.clear();

	size_t index = 0;
	size_t index_shell = 0;
	size_t index_orientation = 0;

	// find offset:
	for (size_t i = 0;i < solid_coms.num_inputs;i++)
	{
		if (CrtCmp("SHELL", ( * (solid_coms.input_arrays))[i]->getSemantic()) )
		{
			solid_coms.offset[SHELL_OFFSET_INDEX] = ( * (solid_coms.input_arrays))[i]->getOffset();
		}
		else if(CrtCmp("ORIENTATION", ( * (solid_coms.input_arrays))[i]->getSemantic()) )
		{
			solid_coms.offset[ORIENTATION_OFFSET_INDEX] = ( * (solid_coms.input_arrays))[i]->getOffset();
		}
	}

	// build solid
	for (size_t i = 0;i < solid_coms.num;i++)
	{
		TopTools_ListOfShape list;

		TopoDS_Solid solid;
		mBuilder.MakeSolid( solid );

		// link shells
		for (size_t j = 0;j < solid_coms.v_list[i];j++)
		{
			size_t base_index = index * solid_coms.num_inputs;
			
			index_shell = base_index + (size_t)solid_coms.offset[SHELL_OFFSET_INDEX];
			index_orientation = base_index + (size_t)solid_coms.offset[ORIENTATION_OFFSET_INDEX];

			TopoDS_Shell s = TopoDS::Shell( mShellMap.FindKey( solid_coms.p_list[index_shell] + 1) );
			s.Orientation( solid_coms.p_list[index_orientation] == 1 ? TopAbs_FORWARD : TopAbs_REVERSED );
			mBuilder.Add( solid, s );

			index++;
		}

		mSolidMap.Add(solid);
	}

	return true;
}

// PRE: index of TopoDS_Shape mShape[], which should be less than current number of breps
bool CrtBrep::initShapes()
{
	int num = mVertexMap.Extent() + mEdgeMap.Extent() + mWireMap.Extent() + mFaceMap.Extent() + mShellMap.Extent() + mSolidMap.Extent();

	if (num == 1)
	{
		if (mVertexMap.Extent())
			mShape = mVertexMap.FindKey(1);
		else if (mEdgeMap.Extent())
			mShape = mEdgeMap.FindKey(1);
		else if (mWireMap.Extent())
			mShape = mWireMap.FindKey(1);
		else if (mFaceMap.Extent())
			mShape = mFaceMap.FindKey(1);
		else if (mShellMap.Extent())
			mShape = mShellMap.FindKey(1);
		else if (mSolidMap.Extent())
			mShape = mSolidMap.FindKey(1);
	}
	else
	{
		TopoDS_Compound c;
		mBuilder.MakeCompound( c );

#if DEBUG_SHAPE_CHECKING
		bool valid_status = false;
		for ( int i = 1; i <= mVertexMap.Extent(); i++ )
		{
			valid_status = BRepAlgo::IsValid(mVertexMap.FindKey(i));
			//	return false;
		}
		for ( int i = 1; i <= mEdgeMap.Extent(); i++ )
		{
			valid_status = (BRepAlgo::IsValid(mEdgeMap.FindKey( i )) );
			//	return false;
		}
		for ( int i = 1; i <= mWireMap.Extent(); i++ )
		{
			valid_status = BRepAlgo::IsValid(mWireMap.FindKey( i ) );
				//return false;
		}
		for ( int i = 1; i <= mFaceMap.Extent(); i++ )
		{
			valid_status = (BRepAlgo::IsValid(mFaceMap.FindKey( i )) );
			//	return false;
		}
		for ( int i = 1; i <= mShellMap.Extent(); i++ )
		{
			valid_status = BRepAlgo::IsValid(mShellMap.FindKey( i )) ;
				//return false;
		}
		for ( int i = 1; i <= mSolidMap.Extent(); i++ )
		{
			valid_status = BRepAlgo::IsValid(mSolidMap.FindKey( i )) ;
				//return false;
		}
#endif
		for ( int i = 1; i <= mVertexMap.Extent(); i++ )
			mBuilder.Add( c, mVertexMap.FindKey( i ) );
		for ( int i = 1; i <= mEdgeMap.Extent(); i++ )
			mBuilder.Add( c, mEdgeMap.FindKey( i ) );
		for ( int i = 1; i <= mWireMap.Extent(); i++ )
			mBuilder.Add( c, mWireMap.FindKey( i ) );
		for ( int i = 1; i <= mFaceMap.Extent(); i++ )
			mBuilder.Add( c, mFaceMap.FindKey( i ) );
		for ( int i = 1; i <= mShellMap.Extent(); i++ )
			mBuilder.Add( c, mShellMap.FindKey( i ) );
		for ( int i = 1; i <= mSolidMap.Extent(); i++ )
			mBuilder.Add( c, mSolidMap.FindKey( i ) );

		mShape = c;

#if DEBUG_SHAPE_CHECKING // http://www.opencascade.org/org/forum/thread_11618/	
		//OutputVertex(c, TopAbs_VERTEX);
		//OutputEdge(c, TopAbs_EDGE);
	//	OutputWire(c, TopAbs_WIRE);
		OutputFace(c, TopAbs_FACE);
#endif
	}

	return true;
}

//-----------------------------------------------------------------------
void CrtBrep::removeBoundShapes(TopTools_IndexedMapOfShape &map1, TopTools_IndexedMapOfShape &map2, TopAbs_ShapeEnum type)
{
	TopTools_IndexedMapOfShape bound;
	
	for (int i = 1; i <= map1.Extent(); i++)
	{
		TopExp_Explorer exp(map1(i), type);
		for (; exp.More(); exp.Next())
		{
			bound.Add(exp.Current());
		}
	}

	removeUsedShapes(map2, bound);
}

void CrtBrep::removeUsedShapes(TopTools_IndexedMapOfShape &map1, TopTools_IndexedMapOfShape &map2)
{
	TopTools_IndexedMapOfShape copy;
	copy.Assign(map1);
	map1.Clear();
	for (int i = 1; i <= copy.Extent(); i++)
	{
		int index = map2.FindIndex(copy(i));
		if (index == 0)
		{
			map1.Add(copy(i));
		}
	}
}

// This function will load all BREPs together to OCC data structure
bool CrtBrep::LoadBrep()
{		
	if (data == NULL)
		return false;

	// get the BREP elements:
	// init the brep elements
//	domBrep * breps;


	daeElementRefArray elements;
	// Get children elements of brep
	data->getChildren(elements);

	// scan vertices, edges, ... on current brep
	// have to scan vertices this way because there are vertices defined in the mesh as well
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		
		// check if we get valid element
		if (e == NULL)
			return false;

		// get name of child
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		// when any element is not correctly loaded, exit
		//if (!IsLoaded)
		//	return false;

		if (CrtCmp(name, "vertices")) // load vertex information
		{
			is_topology_loaded[VERTEX] = initVertices((domVertices *) e);
		}
		else if (CrtCmp(name, "edges")) // load edge information
		{
			is_topology_loaded[EDGE] = initEdges((domEdges *) e);
		}
		else if (CrtCmp(name, "wires")) 
		{
			is_topology_loaded[WIRE] = initWires((domWires *) e);
		}
		else if (CrtCmp(name, "faces")) // load face information
		{
			is_topology_loaded[FACE] = initFaces((domFaces *) e);
		}
		else if (CrtCmp(name, "shells")) // load shell information
		{
			is_topology_loaded[SHELL] = initShells((domShells *) e);
		}
		else if (CrtCmp(name, "solids")) // load solid information
		{
			is_topology_loaded[SOLID] = initSolids((domSolids *) e);
		}
		else if ( CrtCmp(name, "source") || CrtCmp(name, "curves") || CrtCmp(name, "surfaces"))
		{
		}
		else // when it is not a <source>, error			
		{	
			return false;
		}
	} // end of loop of scanning child elements of current brep

	// Remove bound shapes
	removeBoundShapes(mEdgeMap, mVertexMap, TopAbs_VERTEX);
	removeBoundShapes(mWireMap, mEdgeMap, TopAbs_EDGE);
	removeBoundShapes(mFaceMap, mWireMap, TopAbs_WIRE);
	removeBoundShapes(mShellMap, mFaceMap, TopAbs_FACE);
	removeBoundShapes(mSolidMap, mShellMap, TopAbs_SHELL);

	// build BREP data structure
	initShapes();

	bool bRet=false;

	if ( !mShape.IsNull() )
    {
		// when it is not a valid shape, try to fix it
		if ( !BRepAlgo::IsValid( mShape ) )
		{
			ShapeFix_Shape fix(mShape);
			fix.Perform();
			mShape = fix.Shape();
		}

        bRet = BRepAlgo::IsValid( mShape );
        //std::ofstream of("test2.txt");
        //BRepTools::Dump(mRetShape, of);
    }

	// clear Map
	mVertexMap.Clear();
	mEdgeMap.Clear();
	mWireMap.Clear();
	mFaceMap.Clear();
	mShellMap.Clear();
	mSolidMap.Clear();

	if (!bRet)
		return bRet;

	return true;
}

MeshMerger::~MeshMerger()
{
	brep=NULL;
	clear();
}
	
void MeshMerger::clear()
{	
	// no scan data availiable any more
	IsScanDone = false;

	// reset number of faces
	numFace = 0;

	// clean the data sturcture we have:
	if ( !fs_vec.empty() )
		fs_vec.clear();

	if ( !vertexSearch.empty() )
		vertexSearch.clear();

	// vertex index for map
	global_index_vertex = 0;
	
	// vertices coordinates
	if ( !global_vertices.empty() )
		global_vertices.clear();

	// triangles informations:
	if ( !global_tris.empty() )
		global_tris.clear();

	// normals:
	if ( !global_vnormals.empty() )
		global_vnormals.clear();
}

void MeshMerger::InitCrtGeometry(CrtGeometry *geo)
{
	// Get the totoal number of geometry vertices
	CrtUInt num_tris = (fs_vec.at(fs_vec.size() - 1));

	// release old memory space
	delete [] geo->Points;
	delete [] geo->Normals;

	// assign new memeory space
	geo->Points = new CrtVec3f [num_tris * 3];
	geo->Normals = new CrtVec3f [num_tris * 3];
}

// allocate the triangles of face i to CrtGeometry
CrtTriangles * MeshMerger::TriangleFace(CrtGeometry *geo, const CrtUInt index)
{
	if (!IsScanDone) 
		return NULL;

	// build rt trianges
	CrtTriangles * triangles = CrtNew(CrtTriangles);
	// triangles count
	triangles->count = fs_vec.at(index + 1) - fs_vec.at(index);
	
	// resolve Material	
//	daeString str_material = dom_triangles->getMaterial();
//	if (str_material)
//		CrtCpy(triangles->MaterialName, str_material);

	// set index, they all have the same index since we process deindexer conditioner
	triangles->indexes = CrtNewData(CrtUInt, triangles->count * 3);

	for (CrtUInt itri = 0; itri < triangles->count;itri++)
	{
		CrtVec3i iv3 = (global_tris.at(itri + fs_vec.at(index))).index;
		CrtVec3f nf = (global_tris.at(itri + fs_vec.at(index))).normal;
		
		geo->Points[geo->vertexcount] = global_vertices.at( iv3.x );
		geo->Normals[geo->vertexcount] = nf;
		triangles->indexes[3 * itri ] = geo->vertexcount;
		geo->vertexcount++;

		geo->Points[geo->vertexcount] = global_vertices.at( iv3.y );
		geo->Normals[geo->vertexcount] = nf;
		triangles->indexes[3 * itri + 1] = geo->vertexcount;
		geo->vertexcount++;
	
		geo->Points[geo->vertexcount] = global_vertices.at( iv3.z );
		geo->Normals[geo->vertexcount] = nf;
		triangles->indexes[3 * itri + 2] = geo->vertexcount;
		geo->vertexcount++;
	}
	
	return triangles;
}

bool MeshMerger::scanFaces()
{
	if (brep == NULL || !BRepAlgo::IsValid( (*brep)))
		return false;

	BRepMesh::Mesh( (*brep) ,1);

	int fs_index = 0;

	for (TopExp_Explorer ex((*brep),TopAbs_FACE) ; ex.More(); ex.Next()) 
	{	
		TopoDS_Face F = TopoDS::Face(ex.Current());	
		TopLoc_Location L;	
		Handle (Poly_Triangulation) facing = BRep_Tool::Triangulation(F,L);
		// get num of triangles of each face and store it in the vector
		int num_tris = facing->NbTriangles();
		fs_vec.push_back(fs_index);
		fs_index+=num_tris;

		// valid face triangulation
		if ( !facing.IsNull() && num_tris > 0)
		{
			vector <gp_Vec> local_normal;
			vector <int> index_array;

			local_normal.push_back(gp_Vec());
			index_array.push_back(0);

			BRepGProp_Face prop( F );

			for (int i = 1;i <= facing->NbNodes();i++)
			{
				gp_Pnt tmp;
				gp_Vec vn;
				gp_Pnt2d uv = ( facing->UVNodes() ) ( i );
				gp_Pnt p = ( facing->Nodes() ) ( i );

				// compute the normal of each vertex based on paramatric space
				prop.Normal(uv.X(), uv.Y(), tmp, vn);
				
				// local normal is stored
				local_normal.push_back( vn );

				// put it in global vertices vector: transform it as well
				index_array.push_back(UpdateGlobalVertices(p, L));
			}

			for (int i = 1; i <= num_tris;i++)
			{
				Poly_Triangle tri = facing->Triangles() ( i );

				// get local vertices indices
                int index_tri[3];
                tri.Get( index_tri[0], index_tri[1], index_tri[2] );
				
				// get current triangle normal
				// reference of fn: average of 3 vertex normal, 
				// then decide dir of cross product
				gp_Vec fn(0.0, 0.0, 0.0);
				for (int j = 0;j < 3;j++)
					fn += local_normal[ index_tri[j] ]; 

				// update the global indices based on current triangle
				// only continue when there is valid triangulation of each face
				if ( !UpdateGlobalTriangles(fn, L, 
					index_array[ index_tri[0] ], 
					index_array[ index_tri[1] ], 
					index_array[ index_tri[2] ]) )
					return false;
			}
		}
		else
			return false;

		// update number of face:
		numFace++;
	}

	// put index of last tri + 1 at very last
	fs_vec.push_back(fs_index);

	// generate the vertex normal
	// generateVertexNormal();
	
	// clear the tri data inside of brep *
	BRepTools::Clean( (*brep) );

	// update Scan status
	IsScanDone = true;

	return true;
}

bool MeshMerger::generateVertexNormal()
{
	// clear the map because it is never useful:
	vertexSearch.clear();

	if (!global_vnormals.empty())
		global_vnormals.clear();

	// init the global normal vectors
	global_vnormals.resize(global_vertices.size());

	vector <tri> ::iterator iter = global_tris.begin();

	for (;iter != global_tris.end();iter++)
	{
		// put normal into vertices
		global_vnormals.at( (*iter).index.x ) += (*iter).normal;
		global_vnormals.at( (*iter).index.y ) += (*iter).normal;
		global_vnormals.at( (*iter).index.z ) += (*iter).normal;
	}

	// average the normal
	vector <CrtVec3f> ::iterator itern= global_vnormals.begin();
	for (;itern != global_vnormals.end();itern++)
	{
		// add those and then compute average
		(*itern) = (*itern).Normalize();
	}

	return true;
}

int MeshMerger::UpdateGlobalVertices(const gp_Pnt &pt, const TopLoc_Location &L)
{
	// get vertices coordinates with transformation in local coord
	// (origin and orien define in COLLADA)
	gp_Pnt p_transformed = pt.Transformed(L);

	CrtVec3f v((float)p_transformed.X(), (float)p_transformed.Y(), (float)p_transformed.Z());

	std::map<CrtVec3f, int>::iterator iter = vertexSearch.find(v);

	// if this is not in the map
	if (iter == vertexSearch.end())
	{
		vertexSearch[v] = global_index_vertex;
		global_vertices.push_back(v);
		global_index_vertex++;
		return global_index_vertex-1;
	}
	else
	{
		return vertexSearch[v];
	}
}

bool MeshMerger::UpdateGlobalTriangles(const gp_Vec &fn, const TopLoc_Location &L, 
									   const int index0, const int index1, const int index2)
{
	// transformed face normal:
	gp_Vec n(fn.XYZ());
	if (n.Dot(n) > DBL_MIN)
	{
		// normalized fn
		n.Normalize();

		// transform it
		gp_Vec transformed = n.Transformed(L);

		// 3 vertices
		CrtVec3f v1 = global_vertices.at(index0);
		CrtVec3f v2 = global_vertices.at(index1);
		CrtVec3f v3 = global_vertices.at(index2);

		gp_Vec v12( v2.x - v1.x, v2.y - v1.y, v2.z - v1.z );
        gp_Vec v13( v3.x - v1.x, v3.y - v1.y, v3.z - v1.z );
        
		// check area
		if (v12.Dot(v12) > 0 && v13.Dot(v13) > 0)
		{
			v12.Normalize();
			v13.Normalize();

			// compute discrete normal with cross product:
			gp_Vec normal = v12.Crossed(v13);

			// normalize it
			if (normal.Dot(normal) > 0)
			{
				normal.Normalize();

				// reverse if direction is point inside:
				// check whether CCW
				if ( normal.Angle(n) > PI / 2)
				{
					normal *= -1.0;
					// switch global indices:
					global_tris.push_back(tri(index0, index2, index1, 
						(float)normal.X(), (float)normal.Y(), (float)normal.Z()));
				}
				else
				{
					global_tris.push_back(tri(index0, index1, index2, 
						(float)normal.X(), (float)normal.Y(), (float)normal.Z()));			
				}
			}
			else
			{
				// TODO: we can consider to discard this triangle from current mesh
				CrtPrint("Error: degerated triangle.\n");
				return false;
			}
		}
		else
		{
			// TODO: we can consider to discard this triangle from current mesh
			CrtPrint("Error: degerated triangle.\n");
			return false;
		}
	}
	else
	{
		// not valid normal
		return false;
	}
	return true;
}


#if DEBUG_SHAPE_CHECKING
void OutputVertex(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
	TopExp_Explorer t_e;
	t_e.Init(c, ToFind, ToAvoid);
	CrtPrint("vertex info:\n");
	size_t index = 0;
	while(t_e.More())
	{
		TopoDS_Vertex v = TopoDS::Vertex(t_e.Current());
		gp_Pnt p = BRep_Tool::Pnt(v);
		CrtPrint("%d: %f %f %f\n", index, p.X(), p.Y(), p.Z());
		CrtPrint("Orientation: %d\n", v.Orientation());
		t_e.Next();
		index++;
	}
	CrtPrint("\n");
	t_e.Clear();
}

void OutputEdge(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
	TopExp_Explorer t_e;
	size_t index = 0;

	t_e.Init(c, ToFind, ToAvoid);
	CrtPrint("edge info:\n");
	while(t_e.More())
	{
		CrtPrint("index of edge %d: ", index);
		TopoDS_Edge e = TopoDS::Edge(t_e.Current());
		TopLoc_Location L;
		double first, last;
		Handle_Geom_Curve c = BRep_Tool::Curve(e, L, first, last);
		gp_XYZ transl = L.Transformation().TranslationPart();
		CrtPrint("origin: %f %f %f\n", transl.X(), transl.Y(), transl.Z());
		if (c->DynamicType() == STANDARD_TYPE(Geom_Circle)) 
		{
			Geom_Circle * circle = (Geom_Circle *) c.Access();
			CrtPrint("Radius = %f ", circle->Radius());
		}
		else if (c->DynamicType() == STANDARD_TYPE(Geom_Line))
		{
			Geom_Line * line = (Geom_Line *) c.Access();
			gp_Ax1 ax1 = line->Position();
			gp_Dir d = ax1.Direction();
			gp_Pnt p = ax1.Location();
			CrtPrint("origin: %f %f %f, dir: %f %f %f", p.X(), p.Y(), p.Z(), d.X(), d.Y(), d.Z()); 
		}
		CrtPrint(" ( %f %f )\n", first, last);
		CrtPrint("Orientation: %d\n", e.Orientation());
		t_e.Next();
		index++;
	}
	t_e.Clear();
}

void OutputWire(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
	TopExp_Explorer t_e;
	size_t index = 0;

	t_e.Init(c, ToFind, ToAvoid);
	CrtPrint("wire info:\n");
	while(t_e.More())
	{
		CrtPrint("index of wire: %d\n", index);
		TopoDS_Wire w = TopoDS::Wire(t_e.Current());
		OutputEdge(w, TopAbs_EDGE);
		CrtPrint("Orientation: %d\n", w.Orientation());
		t_e.Next();
		index++;
	}	
	t_e.Clear();
}

void OutputFace(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
	TopExp_Explorer t_e;
	size_t index = 0;

	t_e.Init(c, ToFind, ToAvoid);
	CrtPrint("Face info:\n");

	while(t_e.More())
	{
		CrtPrint("index of face: %d\n", index);
		TopoDS_Face f = TopoDS::Face(t_e.Current());
		TopLoc_Location L;
		Handle_Geom_Surface sur = BRep_Tool::Surface(f, L);
		gp_XYZ transl = L.Transformation().TranslationPart();
		CrtPrint("Geometry: ");
		CrtPrint("origin: %f %f %f\n", transl.X(), transl.Y(), transl.Z());
		if (sur->DynamicType() == STANDARD_TYPE(Geom_CylindricalSurface))
		{
			Geom_CylindricalSurface * cylind = (Geom_CylindricalSurface *) sur.Access();
			gp_Ax1 ax = cylind->Axis();
			gp_Pnt location = ax.Location();
			gp_Dir dir = ax.Direction();
			double r = cylind->Radius();
			CrtPrint("location: %f %f %f dir: %f %f %f and r = %f\n", 
				location.X(), location.Y(), location.Z(), 
				dir.X(), dir.Y(), dir.Z(),
				r);
		}
		else if (sur->DynamicType() == STANDARD_TYPE(Geom_Plane))
		{
			Geom_Plane * p = (Geom_Plane *)sur.Access();
			gp_Pln peq = p->Pln();
			double a, b, c, d;
			peq.Coefficients(a, b, c, d);
			CrtPrint("Plane: %f %f %f %f\n", a, b, c, d);
		}

		CrtPrint("Wire Info\n");
		OutputWire(f, TopAbs_WIRE);

		CrtPrint("Orientation: %d\n", f.Orientation());

		t_e.Next();

		index++;
	}
}

void OutputShell(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
}

void OutputSolid(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid)
{
}

#endif