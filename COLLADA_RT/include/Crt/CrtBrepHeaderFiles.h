#ifndef CRT_BREP_HEADER_FILES_H_
#define CRT_BREP_HEADER_FILES_H_


// Topology part:
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Compound.hxx>

// Brep builder:
#include <brepalgo.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

// Shape fix
#include <shapefix_shape.hxx>
#include <brepgprop_face.hxx>

// Geom part
#include <GeomAPI.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Parabola.hxx>
#include <Geom_Hyperbola.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_OffsetSurface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>

// Storage for bspline:
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <tcolstd_array1ofinteger.hxx>
#include <tcolStd_array1Ofreal.hxx>
#include <tcolgp_array2ofpnt.hxx>
#include <tcolStd_array2Ofreal.hxx>

// mesh triangulation
#include <BRepMesh.hxx>
#include <TopExp_Explorer.hxx>
#include <TopLoc_Location.hxx>
#include <Poly_Triangle.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>

// include dom header files
#include "dae.h"
#include "dom/domConstants.h"
#include "dom/domCOLLADA.h"
#include <dae/daeSIDResolver.h>

#endif

