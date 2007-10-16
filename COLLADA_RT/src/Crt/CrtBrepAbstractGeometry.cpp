#include "Crt/CrtBrepBuilder.h"
#include "Crt/CrtUtils.h"
#include <tcolstd_array1ofinteger.hxx>
#include <tcolStd_array1Ofreal.hxx>
#include <tcolgp_array2ofpnt.hxx>
#include <tcolStd_array2Ofreal.hxx>

gp_Pnt AbsCurve_OCC_Parser::o(0.0, 0.0, 0.0 );
gp_Dir AbsCurve_OCC_Parser::x(1.0, 0.0, 0.0 );
gp_Dir AbsCurve_OCC_Parser::n(0.0, 0.0, 1.0 ); // z-up

// PRE: ele should be a curve element: why can't we use const here???
bool AbsCurve_OCC_Parser::ReadCurve(daeElement *ele, Handle_Geom_Curve &curve)
{
	bool IsValid = false;

	// get curve child element of current curve
	daeElementRefArray elements;
	ele->getChildren(elements);

	// when curve is NULL: corresponding degenerated edge.
	if (elements.getCount() == 0)
	{
		curve = NULL;
		return true;
	}

	for (size_t i = 0;i < elements.getCount();i++)
	{
		daeElement * e = elements.get(i);

		// find name of this curve
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		// find correct parser for it
		if (CrtCmp(name, COLLADA_ELEMENT_CIRCLE)) // it is circle
		{
			// load the circle 
			IsValid = ReadCircle(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_LINE)) // it is a line
		{
			// load the line
			IsValid = ReadLine(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_ELLIPSE)) // ellipse
		{
			// load ellipse
			IsValid = ReadEllipse(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_PARABOLA)) // parabola
		{
			// load parabola
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_HYPERBOLA)) // HYPERBOLA
		{
			// load hyperbola
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_SPLINE)) // BSPLINE curve
		{
			// load bspline
			IsValid = ReadBSplineCurve(e, curve);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_ROTATE))
		{
			domFloat4 axis_angle = ((domRotate * )e)->getValue();

			// build OCC rotation:
			// Do we need the unit dir????
			gp_Dir dir(axis_angle.get(0), axis_angle.get(1), axis_angle.get(2));
			gp_Ax1 ax(AbsCurve_OCC_Parser::o, dir);
			gp_Trsf rot;
			// from angle to radian unit
			rot.SetRotation(ax, axis_angle.get(3) * PI / 180.0);
			// Why invert????
			rot.Invert();

			// If there is not a null curve, then apply the transformation
			if ( !curve.IsNull() )
			{
				curve->Transform( rot );
			}
			else
				return false;

		}
		else if (CrtCmp(name, COLLADA_ELEMENT_TRANSLATE))
		{
			domFloat3 trans_xyz = ((domTranslate * ) e)->getValue();

			// build OCC translation
			gp_Vec vec( trans_xyz.get( 0 ), trans_xyz.get( 1 ), trans_xyz.get( 2 ) );
			gp_Trsf trans;
			trans.SetTranslation( vec );

			if ( !curve.IsNull() )
			{
				curve->Transform( trans );
			}
			else
				return false;
		}
		else
		{
			// extra element here: not defined in schema
			return false;
		}
	}

	return IsValid;
}

// Loading circles
// PRE: e is type of circle

bool AbsCurve_OCC_Parser::ReadCircle(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// daeElement must be circle type
	domCircle *circle = NULL;
	circle = daeSafeCast <domCircle>((daeElement*)ele);
	if (circle == NULL)
	{
		CrtPrint("Error: circle is not from correct type conversion.\n");
		return false;
	}
	daeElementRefArray elements;
	circle->getChildren(elements);

	double r = -1.0;

	// scan the circle children
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		// check the radius
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS)) // this is radius?
		{
			// init the radius
			r = ((domCircle::domRadius *)e)->getValue();

			// Judge whether it is in the correct domain
			if (r <=0.0)
				return false;
			else
			{
				// generate the curve for OCC
				gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
				curve = new Geom_Circle(ax, r);
				return true;
			}
		}
	}

	// did not find any radius information
	return false;
}

// Loading line
// PRE: e is type of Line
bool AbsCurve_OCC_Parser::ReadLine(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init the Line element
	domLine *line = NULL;
	line = daeSafeCast <domLine> ( (daeElement *)ele );
	if (line == NULL)
		return false;

	domFloat3 originDom;
	domFloat3 dirDom;

	// get two elements of line:
	daeElementRefArray elements;
	line->getChildren(elements);
	
	// scan children of line
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_ORIGIN))
		{
			originDom = ((domLine::domOrigin *)e)->getValue();
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_DIRECTION))
		{
			dirDom = ((domLine::domDirection *)e)->getValue();
		}
	}

	// build the OCC data format:
	gp_Pnt origin;
    gp_Dir direction;

	origin.SetCoord(originDom.get(0), originDom.get(1), originDom.get(2));
	direction.SetCoord(dirDom.get(0), dirDom.get(1), dirDom.get(2));

	curve = new Geom_Line (origin, direction);

	return true;
}

// Loading Ellipse
// PRE: e is type of Ellipse
bool AbsCurve_OCC_Parser::ReadEllipse(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init Ellipse
	domEllipse * ellipse = NULL;
	ellipse = daeSafeCast <domEllipse> ( (daeElement *)ele );
	domFloat2 r2;
	domFloat r_maj, r_min;

	// init two data
	// get two elements of ellipse:
	daeElementRefArray elements;
	ellipse->getChildren(elements);
	
	// scan children of line
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS))
		{
			r2 = ( (domEllipse::domRadius *)e )->getValue(); 
		}
	}

	r2.get2at(0, r_maj, r_min);

	// build the OCC data format:
	if (r_maj < 0 || r_min < 0) // not fit domain of radius
		return false;
	else
	{
		// generate the ellipse for OCC
		gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
		curve = new Geom_Ellipse(ax, r_maj, r_min);
		return true;
	}
}

bool AbsCurve_OCC_Parser::ReadHyperbola(const daeElement *ele, Handle_Geom_Curve &curve)
{
	// init Hyperbolic:
	domHyperbola *hyperbola = NULL;
	hyperbola = daeSafeCast <domHyperbola> ( (daeElement *)ele );
	if (hyperbola == NULL)
		return false;

	// init two data
	domFloat2 r2;
	domFloat r_maj, r_min;

	// get two elements of Hyperbola:
	daeElementRefArray elements;
	hyperbola->getChildren(elements);

	// get children
	for (size_t j = 0; j < elements.getCount(); j++)
	{
		daeElement* e = elements[j];
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		if (CrtCmp(name, COLLADA_ELEMENT_RADIUS))
		{
			r2 = ( (domHyperbola::domRadius *)e )->getValue(); 
		}
	}

	r2.get2at(0, r_maj, r_min);

	// build the OCC data format:
	if (r_maj < 0 || r_min < 0) // not fit domain of radius
		return false;
	else
	{
		// generate the ellipse for OCC
		gp_Ax2 ax(AbsCurve_OCC_Parser::o, AbsCurve_OCC_Parser::n, AbsCurve_OCC_Parser::x);
		curve = new Geom_Hyperbola( ax, r_maj, r_min );
		return true;
	}
}

// Parse the list to arrays that is BSpline required
bool ParseOCCKnots(bool IsPeriodic, TColStd_Array1OfReal** karray, TColStd_Array1OfInteger** marray, int num_cv, int degree, domListOfFloats &list)
{
	// judge whether num of knots is valid
	size_t num_knots = list.getCount();
	if (num_knots != (size_t) (num_cv + degree + 1))
		return false;

	std::vector <int> m_tmp;
	std::vector <domFloat> k_tmp;
	int cur_multiplicity = 1;

	// parse the knot vector to these two arrays:
	for (size_t i = 1;i < num_knots;i++)
	{
		if ( list[i] - list[i - 1] < Precision::Confusion() )
		{
			cur_multiplicity++;
		}
		else
		{
			m_tmp.push_back( cur_multiplicity );
			k_tmp.push_back( list[i - 1] );
			// update multiplicity
			cur_multiplicity = 1;
		}
	}

	// push last value
	m_tmp.push_back(cur_multiplicity);
	k_tmp.push_back(list[ num_knots - 1 ]);

	// when periodic
	if (IsPeriodic)
	{
		int test = num_knots - m_tmp.at(0);
		int index_remove = ( test - num_cv ) / 4 ;

		size_t s = m_tmp.size();
        m_tmp.erase( m_tmp.end() - index_remove, m_tmp.end() );
        s = m_tmp.size();
        m_tmp.erase( m_tmp.begin(), m_tmp.begin() + index_remove );
        s = m_tmp.size();
        k_tmp.erase( k_tmp.end() - index_remove, k_tmp.end() );
        k_tmp.erase( k_tmp.begin(), k_tmp.begin() + index_remove );
	}

	if ( m_tmp.size() == k_tmp.size() )
    {
        *marray = new TColStd_Array1OfInteger( 1, ( Standard_Integer ) m_tmp.size() );
        *karray = new TColStd_Array1OfReal( 1, ( Standard_Integer ) k_tmp.size() );

        for ( size_t i = 0; i < k_tmp.size(); i++ )
        {
            (*marray)->SetValue( ( Standard_Integer ) ( i + 1 ), m_tmp[ i ] );
            (*karray)->SetValue( ( Standard_Integer ) ( i + 1 ), k_tmp[ i ] );
        }
		return true;
    }
	return false;
}

bool AbsCurve_OCC_Parser::ReadBSplineCurve(const daeElement *ele, Handle( Geom_Curve ) &curve)
{
	domSpline *splinecurve = daeSafeCast <domSpline> ( (daeElement *) ele);
	if (splinecurve == NULL)
		return false;

	domSpline::domControl_verticesRef cv = splinecurve->getControl_vertices();
	domInputLocal_Array &inputs = cv->getInput_array();

	// for OCC data stucutre
    TColgp_Array1OfPnt* polesOCC = NULL;
    TColStd_Array1OfReal* knotsOCC = NULL;
    TColStd_Array1OfInteger* multsOCC = NULL;
    TColStd_Array1OfReal* weightsOCC = NULL;
    int degreeOCC=-1;
    bool periodicOCC = false;

	// These input arrays contains information such as interpolation...
	for (size_t i = 0;i < inputs.getCount();i++)
	{
		domInputLocal * input = inputs.get(i);
		// get source
		domSource * source = daeSafeCast <domSource> (input->getSource().getElement() );
		// get size
		domSource::domTechnique_common* tech = source->getTechnique_common();
		domAccessor *acc = tech->getAccessor();
		size_t size = ( size_t ) acc->getCount();

		// Interpolation: close or open
		if ( CrtCmp( input->getSemantic(), "INTERPOLATIONS" ) )
        {
			domListOfNames &interpolations = ( source->getName_array() )->getValue();
			
			for (size_t j = 0;j < size;j++)
				if (CrtCmp (interpolations.get(j), "CLOSED") )
					periodicOCC = true;
		}
		else if ( CrtCmp(input->getSemantic(), "POSITIONS") )
		{
			polesOCC = new TColgp_Array1OfPnt( 1, ( Standard_Integer ) size );
			domListOfFloats &positions = ( source->getFloat_array() )->getValue();

            for ( size_t j = 0; j < size; j++ )
            {
                double x, y, z;
                positions.get3at( ( j * (size_t)acc->getStride() ), x, y, z );
                polesOCC->SetValue( (Standard_Integer) ( j + 1 ), gp_Pnt(x, y, z) );
            }
		}
		else if ( CrtCmp(input->getSemantic(), "WEIGHTS") )
		{
			weightsOCC = new TColStd_Array1OfReal( 1, ( Standard_Integer ) size );
			domListOfFloats &weight = ( source->getFloat_array() )->getValue();

            for ( size_t j = 0; j < size; j++ )
            {
                double w = weight.get( ( j * ( size_t ) acc->getStride() ) );
                weightsOCC->SetValue( ( Standard_Integer ) ( j + 1 ), w );
            }
		}
		else if ( CrtCmp(input->getSemantic(), "DEGREES") )
		{
			domListOfInts &degrees = ( source->getInt_array() )->getValue();
			degreeOCC = (int)degrees.get(0);
		}
		else if ( CrtCmp(input->getSemantic(), "KNOTS") )
		{
			domListOfFloats &knots = ( source->getFloat_array() )->getValue();
			if (!ParseOCCKnots(periodicOCC, &knotsOCC , &multsOCC, polesOCC->Length(), degreeOCC, knots))
				return false;
		}
	}

	if ( polesOCC && knotsOCC && multsOCC && weightsOCC && degreeOCC > 0)
    {
        curve = new Geom_BSplineCurve( *polesOCC, *weightsOCC, *knotsOCC, *multsOCC, degreeOCC, periodicOCC );
        delete polesOCC;
        delete weightsOCC;
        delete knotsOCC;
        delete multsOCC;
		return true;
    }
	return false;
}

bool AbsSurface_OCC_Parser::ReadSurface(daeElement *ele, Handle_Geom_Surface &surface)
{
	bool IsValid = false;

	// surface type
	// get curve child element of current surface
	daeElementRefArray elements;
	ele->getChildren(elements);

	// when surface is NULL: return error
	if (elements.getCount() == 0)
	{
		return false;
	}

	for (size_t i = 0;i < elements.getCount();i++)
	{
		daeElement * e = elements.get(i);

		// find name of this surface
		daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();
		
		// find correct parser for it
		if (CrtCmp(name, COLLADA_ELEMENT_CYLINDER))
		{
			IsValid = ReadCylinder( e, surface);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_PLANE))
		{
			IsValid = ReadPlane( e, surface);
		}
		else if(CrtCmp(name, COLLADA_ELEMENT_SPLINE) )
		{
			IsValid = ReadBSpline(e, surface);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_TAPERED_CYLINDER) )
		{
			IsValid = ReadTaperedCylinder(e, surface);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_CYLINDRICAL) )
		{
			IsValid = ReadCylindrical( e, surface);
		}
		else if (CrtCmp(name, COLLADA_ELEMENT_TRANSLATE ) )
        {
            domTranslate * translation = daeSafeCast<domTranslate>( e );
            domFloat3 &t = translation->getValue();
            gp_Vec vec( t.get( 0 ), t.get( 1 ), t.get( 2 ) );
            gp_Trsf trans;
            trans.SetTranslation( vec );

            if ( !surface.IsNull() )
            {
                surface->Transform( trans );
            }

        }
        else if (CrtCmp(name, COLLADA_ELEMENT_ROTATE ) )
        {
            domRotate * rotation = daeSafeCast<domRotate>( e );
            domFloat4 &r = rotation->getValue();
            gp_Pnt o( 0.0, 0.0, 0.0 );
            gp_Dir dir( r.get( 0 ), r.get( 1 ), r.get( 2 ) );
            gp_Ax1 ax( o, dir );
            gp_Trsf rot;
            rot.SetRotation( ax, r.get( 3 ) * PI / 180 );
            rot.Invert();

            if ( !surface.IsNull() )
            {
                surface->Transform( rot );
            }
        }
		else
			return false;
	}
	return IsValid;
}

bool AbsSurface_OCC_Parser::ReadPlane(const daeElement *ele, Handle_Geom_Surface &surface)
{
	domPlane * e = NULL;
	e = daeSafeCast <domPlane> (( (daeElement *) ele));
	if (e == NULL)
		return false;

	domPlane::domEquation * equation = e->getEquation();

	domFloat4 &v = equation->getValue();
    double a, b, c, d;
    v.get4at( 0, a, b, c, d );

    surface = new Geom_Plane( a, b, c, d );

	return true;
}

bool AbsSurface_OCC_Parser::ReadCylinder(const daeElement *ele, Handle_Geom_Surface &surface)
{
	domCylinder * e = NULL;
	e = daeSafeCast <domCylinder> (( (daeElement *) ele));
	if (e == NULL)
		return false;

	gp_Pnt o( 0.0, 0.0, 0.0 );
	gp_Dir x( 1.0, 0.0, 0.0 );
	gp_Dir n( 0.0, 0.0, 1.0 );
	gp_Ax3 ax( o, n, x );

	double radius, tmp;

	domCylinder::domRadius * radiuses = e->getRadius();
	domFloat2 &v = radiuses->getValue();
	v.get2at(0, radius, tmp);

	surface = new Geom_CylindricalSurface( ax, radius );

	return true;
}

bool AbsSurface_OCC_Parser::ReadCylindrical(const daeElement *ele, Handle_Geom_Surface &surface)
{
	domCylindrical * e = NULL;
	e = daeSafeCast <domCylindrical> (( (daeElement *) ele));
	if (e == NULL)
		return false;

	gp_Pnt o( 0.0, 0.0, 0.0 );
	gp_Dir x( 1.0, 0.0, 0.0 );
	gp_Dir n( 0.0, 0.0, 1.0 );
	gp_Ax3 ax( o, n, x );

	domCylindrical::domRadius * radiuses = e->getRadius();
	domFloat radius = radiuses->getValue();

	surface = new Geom_CylindricalSurface( ax, (Standard_Real)radius );

	return true;
}

bool AbsSurface_OCC_Parser::ReadBSpline(const daeElement *ele, Handle_Geom_Surface &surface)
{
	domSpline *spline_sur = daeSafeCast<domSpline> (( (daeElement *) ele));
	if (spline_sur == NULL)
		return false;

	// get input informations
	domSpline::domControl_verticesRef cv = spline_sur->getControl_vertices();
	domInputLocal_Array &inputs = cv->getInput_array();

	// for OCC data stucutre
    TColgp_Array2OfPnt* polesOCC = NULL;
    TColStd_Array1OfReal* u_knotsOCC = NULL;
	TColStd_Array1OfReal* v_knotsOCC = NULL;
    TColStd_Array1OfInteger* u_multsOCC = NULL;
	TColStd_Array1OfInteger* v_multsOCC = NULL;
    TColStd_Array2OfReal* weightsOCC = NULL;
	size_t u_num_cv, v_num_cv; // number of vertices
    int u_degreeOCC=-1, v_degreeOCC=-1;
    bool u_periodicOCC = false, v_periodicOCC = false;


	for (size_t i = 0;i < inputs.getCount();i++)
	{
		domInputLocal * input = inputs.get(i);
		// get source
		domSource * source = daeSafeCast <domSource> (input->getSource().getElement() );
		// get size
		domSource::domTechnique_common* tech = source->getTechnique_common();
		domAccessor *acc = tech->getAccessor();
		size_t size = ( size_t ) acc->getCount();
		size_t stride = ( size_t )acc->getStride();

		// Interpolation: close or open, and find dimension for each direction:
		if ( CrtCmp( input->getSemantic(), "INTERPOLATIONS_U" ) )
        {
			// TODO: need to make sure that for this part, names follows: NURBS...NURBS, CLOSE/OPEN
			// list of names
			domListOfNames &interpolations = ( source->getName_array() ) ->getValue();

			// num of vertices along u:
			u_num_cv = interpolations.getCount() + 1;

			for (size_t j = 0;j < size;j++)
			{
				if (CrtCmp(interpolations.get(j), "CLOSE"))
				{
					u_periodicOCC = true;
				}
			}
		}
		else if ( CrtCmp( input->getSemantic(), "INTERPOLATIONS_V") )
		{
			// list of names
			domListOfNames &interpolations = ( source->getName_array() ) ->getValue();

			// num of vertices along v
			v_num_cv = interpolations.getCount() + 1;

			for (size_t j = 0;j < size;j++)
			{
				if (CrtCmp(interpolations.get(j), "CLOSE"))
				{
					v_periodicOCC = true;
				}
			}
		}
		else if ( (CrtCmp( input->getSemantic(), "POSITIONS" ) ) )
		{
			domListOfFloats &positions = (source->getFloat_array())->getValue();
			polesOCC = new TColgp_Array2OfPnt(1, (Standard_Integer)u_num_cv, 1, (Standard_Integer)v_num_cv);
			
			// init the poles
			for (size_t j = 0; j < size;j++)
			{
				domFloat x, y, z;
				positions.get3at(stride * j, x, y, z);

				// put x, y, z to OCC structures
				Standard_Integer row = j / v_num_cv + 1;
				Standard_Integer col = j % v_num_cv + 1;
				polesOCC->SetValue(row, col, gp_Pnt(x, y, z));
			}
		}
		else if ( (CrtCmp( input->getSemantic(), "WEIGHTS") ) )
		{
			domListOfFloats &weights = (source->getFloat_array())->getValue();
			weightsOCC = new TColStd_Array2OfReal(1, u_num_cv, 1, v_num_cv);
			// init the weights
			for (size_t j = 0; j < size;j++)
			{
				domFloat w;
				weights.get(j);

				// put w to OCC structures
				Standard_Integer row = j / v_num_cv + 1;
				Standard_Integer col = j % v_num_cv + 1;
				weightsOCC->SetValue(row, col, (Standard_Real)w);
			}
		}
		else if ( (CrtCmp( input->getSemantic(), "DEGREES_U") ) )
		{
			domListOfInts &degree = (source ->getInt_array() )->getValue();
			u_degreeOCC = degree.get(0);
		}
		else if ( (CrtCmp( input->getSemantic(), "DEGREES_V") ) )
		{
			domListOfInts &degree = (source ->getInt_array() )->getValue();
			v_degreeOCC = degree.get(0);
		}
		else if ( (CrtCmp( input->getSemantic(), "KNOTS_U") ) )
		{
			domListOfFloats u_knots = (source->getFloat_array())->getValue();
			if (!ParseOCCKnots(u_periodicOCC, &u_knotsOCC , &u_multsOCC, u_num_cv, u_degreeOCC, u_knots))
				return false;
		}
		else if ( (CrtCmp( input->getSemantic(), "KNOTS_V") ) )
		{
			domListOfFloats v_knots = (source->getFloat_array())->getValue();
			if (!ParseOCCKnots(v_periodicOCC, &v_knotsOCC , &v_multsOCC, v_num_cv, v_degreeOCC, v_knots))
				return false;
		}
	}

	if (polesOCC && u_knotsOCC && v_knotsOCC && u_multsOCC && v_multsOCC && weightsOCC && u_degreeOCC > 0 && v_degreeOCC > 0)
	{
		surface = new Geom_BSplineSurface(*polesOCC, *u_knotsOCC, *v_knotsOCC, *u_multsOCC, *v_multsOCC, u_degreeOCC, v_degreeOCC);

		delete polesOCC;
		delete u_knotsOCC;
		delete v_knotsOCC;
		delete u_multsOCC;
		delete v_multsOCC;
		delete weightsOCC;

		if (surface == NULL)
			return false;
		else 
			return true;
	}

	return false;
}

// this is a cone in fact.
bool AbsSurface_OCC_Parser::ReadTaperedCylinder(const daeElement *ele, Handle_Geom_Surface &surface)
{
	domTapered_cylinder *cone = daeSafeCast<domTapered_cylinder> ( (daeElement *) ele );
	if (cone == NULL)
		return false;

	// read the cone radius	
	double height = cone->getHeight()->getValue();
	double radius1 = cone->getRadius1()->getValue().get(0);
	double radius2 = cone->getRadius2()->getValue().get(0);
	
	gp_Pnt o( 0.0, 0.0, 0.0 );
    gp_Dir x( 1.0, 0.0, 0.0 );
	gp_Dir n;
	Standard_Real ang, r;

    if ( radius1 < radius1 )
    {
        n = gp_Dir( 0.0, 0.0, -1.0 ); 
        r = radius2 / 2;
        ang = -atan( radius2 / height );
    }
    else
    {
        n = gp_Dir( 0.0, 0.0, 1.0 );
        r = radius1 / 2;
        ang = atan( radius1 / height );
    }

	// construct frame
	gp_Ax3 ax( o, n, x );

	surface = new Geom_ConicalSurface( ax, ang, r );
}