#ifndef CRT_BREP_BUILDER
#define CRT_BREP_BUILDER


#include <Crt/CrtBrepHeaderFiles.h>
#include <Crt/CrtUtils.h>
#include <Crt/CrtGeometry.h>

#include <stdio.h>
#include <string>
#include <vector>

#define MAX_OFFSET 5
using namespace std;
#define DEBUG_SHAPE_CHECKING 0

// This will be called for EDGE elements
class AbsCurve_OCC_Parser
{
public:
	bool ReadCurve(daeElement *, Handle( Geom_Curve ) &curve);

	bool ReadLine(const daeElement *, Handle( Geom_Curve ) &curve);
	bool ReadCircle(const daeElement *, Handle( Geom_Curve ) &curve);
	bool ReadEllipse(const daeElement *, Handle( Geom_Curve ) &curve);
	bool ReadHyperbola(const daeElement *, Handle( Geom_Curve ) &curve);
	bool ReadParabolics(const daeElement *, Handle( Geom_Curve ) &curve);
	bool ReadBSplineCurve(const daeElement *, Handle( Geom_Curve ) &curve);

	// This will be for curve class:
	virtual ~AbsCurve_OCC_Parser() {;}

protected:
	// default coordinate for all Conic curves
	static gp_Pnt o; //( 0.0, 0.0, 0.0 );
    static gp_Dir x; //( 1.0, 0.0, 0.0 );
    static gp_Dir n; //( 0.0, 0.0, 1.0 );

};

// This will be called for SURFACE elements
struct AbsSurface_OCC_Parser
{
	// This will be for surface class:
	bool ReadSurface(daeElement *, Handle( Geom_Surface ) &surface);

	bool ReadCylinder(const daeElement *, Handle( Geom_Surface ) &surface);
	bool ReadPlane(const daeElement *, Handle( Geom_Surface ) &surface);
	bool ReadBSpline(const daeElement *, Handle( Geom_Surface ) &surface); 
	bool ReadTaperedCylinder(const daeElement *, Handle( Geom_Surface ) &surface); 
	bool ReadCylindrical(const daeElement *, Handle( Geom_Surface ) &surface); 
};


class CrtBrep // read COLLADA and transfer it to OCC data structure
{
public:
	// constructor
	CrtBrep(domBrep *input, double dTol_=0.01):data(input), dTol(dTol_){
		for (int i =0;i < NUM_TOP;i++)
			is_topology_loaded[i] = false;
	}

	struct brepComponent 
	{
		domListOfFloats floats_pt;
		domInputLocalOffset_Array *input_arrays;
		size_t num_inputs;
		domListOfUInts p_list;
		domListOfUInts v_list;
		domUint num;
		domUint offset[MAX_OFFSET];
		vector <domSIDREF_array * > sid_vector;
		vector <domListOfFloats * > list_floats_vector;
		vector <domName_array *> name_vector;
		
		brepComponent (domInputLocalOffset_Array &input_arrays_) 
		{
			input_arrays=&input_arrays_;
			num_inputs = input_arrays->getCount();
		}
	};
	
	// main function to process BREP: this will parse the COLLADA contents 
	// to OCC shape
	bool LoadBrep();

	// clear all the data in OCC_structure
	~CrtBrep();

	// get OCC data of brep at index	
	inline TopoDS_Shape & getBrep() 
	{
		return mShape;
	}

protected:
	// init topology elements
	bool initVertices(domVertices *);
	bool initEdges(domEdges *);
	bool initWires(domWires *);
	bool initFaces(domFaces *);
	bool initShells(domShells *);
	bool initSolids(domSolids *);

	// shapes is not a element of COLLADA and just for OCC data structure.
	bool initShapes();

	// To find out whether to build a Compound or not.
	void removeBoundShapes(TopTools_IndexedMapOfShape &map1, TopTools_IndexedMapOfShape &map2, TopAbs_ShapeEnum type);
	void removeUsedShapes(TopTools_IndexedMapOfShape &map1, TopTools_IndexedMapOfShape &map2);

	enum topology{
	VERTEX,
	EDGE,
	WIRE,
	FACE,
	SHELL,
	SOLID,
	NUM_TOP
	};

private:
	// Shape def in OCC
	TopoDS_Shape mShape;
	BRep_Builder mBuilder;

	// Total num of Brep
//	daeUInt num_breps;

	// Map for building the Topology elements
	TopTools_IndexedMapOfShape mVertexMap;
	TopTools_IndexedMapOfShape mEdgeMap;
	TopTools_IndexedMapOfShape mWireMap;
	TopTools_IndexedMapOfShape mFaceMap;
	TopTools_IndexedMapOfShape mShellMap;
	TopTools_IndexedMapOfShape mSolidMap;

	// This is the link from outside and we won't release the memory here.
	domBrep *data;

	double dTol;

	bool is_topology_loaded[NUM_TOP];
};

// This will merge meshes from each face to one mesh with no redandunt vertices
// on share edges of faces.
class MeshMerger
{
public:
	// constructor
	MeshMerger(TopoDS_Shape *brep_):brep(brep_),global_index_vertex(0), 
		IsScanDone(false), numFace(0){}
	~MeshMerger();
	
	// merge the mesh from each face
	bool scanFaces();

	inline CrtUInt getNumFaces() {return numFace;}

	CrtTriangles * TriangleFace(CrtGeometry *, const CrtUInt);

	void InitCrtGeometry(CrtGeometry *geo);

	// clear all vector storage:
	void clear();

protected:
	// get vertex information
	// PRE: pt is local vertices coord
	// POST: return the global coordinate
	int UpdateGlobalVertices(const gp_Pnt &pt, const TopLoc_Location &);

	// PRE: fn is local normal coord and may not be normalized
	// 3 int are global indices for this triangle
	bool UpdateGlobalTriangles(const gp_Vec &n, const TopLoc_Location &, 
		const int, const int, const int);

	struct tri
	{
		CrtVec3i index;
		CrtVec3f normal;
		tri():index(),normal()
		{;}
		tri(int i1, int i2, int i3, float nx, float ny, float nz)
		{
			index.x=i1;index.y=i2;index.z=i3;
			normal.x=nx;normal.y=ny;normal.z=nz;
		}
	};

private:
	TopoDS_Shape *brep;

	// decide whether we can get any information from mesh merger:
	bool IsScanDone;

	// current number of faces
	CrtUInt numFace;
	vector <CrtUInt> fs_vec; // first triangle index at each face
	
	// pair of value: vertex -> index: for merge 
	std::map <CrtVec3f, int> vertexSearch;
	// vertex index for map
	int global_index_vertex;
	
	// vertices coordinates
	vector <CrtVec3f> global_vertices;
	// triangles informations:
	vector <tri> global_tris;

	// based on above two vector, we will have:
	// normal generation
	bool generateVertexNormal();
	// normals:
	vector <CrtVec3f> global_vnormals;
};
#if DEBUG_SHAPE_CHECKING
	void OutputVertex(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
	void OutputEdge(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
	void OutputWire(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
	void OutputFace(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
	void OutputShell(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
	void OutputSolid(const TopoDS_Shape &c, const TopAbs_ShapeEnum ToFind ,const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE);
#endif

#endif