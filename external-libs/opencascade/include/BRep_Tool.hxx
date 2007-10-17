// File generated by CPPExt (Value)
//
//                     Copyright (C) 1991 - 2000 by  
//                      Matra Datavision SA.  All rights reserved.
//  
//                     Copyright (C) 2001 - 2004 by
//                     Open CASCADE SA.  All rights reserved.
// 
// This file is part of the Open CASCADE Technology software.
//
// This software may be distributed and/or modified under the terms and
// conditions of the Open CASCADE Public License as defined by Open CASCADE SA
// and appearing in the file LICENSE included in the packaging of this file.
//  
// This software is distributed on an "AS IS" basis, without warranty of any
// kind, and Open CASCADE SA hereby disclaims all such warranties,
// including without limitation, any warranties of merchantability, fitness
// for a particular purpose or non-infringement. Please see the License for
// the specific terms and conditions governing rights and limitations under the
// License.

#ifndef _BRep_Tool_HeaderFile
#define _BRep_Tool_HeaderFile

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _Handle_Poly_Triangulation_HeaderFile
#include <Handle_Poly_Triangulation.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_Geom_Curve_HeaderFile
#include <Handle_Geom_Curve.hxx>
#endif
#ifndef _Handle_Poly_Polygon3D_HeaderFile
#include <Handle_Poly_Polygon3D.hxx>
#endif
#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Poly_Polygon2D_HeaderFile
#include <Handle_Poly_Polygon2D.hxx>
#endif
#ifndef _Handle_Poly_PolygonOnTriangulation_HeaderFile
#include <Handle_Poly_PolygonOnTriangulation.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
class Standard_NullObject;
class Standard_NoSuchObject;
class TopoDS_Shape;
class Geom_Surface;
class TopoDS_Face;
class TopLoc_Location;
class Poly_Triangulation;
class TopoDS_Edge;
class Geom_Curve;
class Poly_Polygon3D;
class Geom2d_Curve;
class Poly_Polygon2D;
class Poly_PolygonOnTriangulation;
class gp_Pnt2d;
class Bnd_Box2d;
class gp_Pnt;
class TopoDS_Vertex;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//! Provides class methods  to  access to the geometry <br>
//!          of BRep shapes. <br>
class BRep_Tool  {

public:

    void* operator new(size_t,void* anAddress) 
      {
        return anAddress;
      }
    void* operator new(size_t size) 
      { 
        return Standard::Allocate(size); 
      }
    void  operator delete(void *anAddress) 
      { 
        if (anAddress) Standard::Free((Standard_Address&)anAddress); 
      }
 // Methods PUBLIC
 // 

//! Returns <True>  if S if flaged Closed, if S is a <br>
//!          Solid,Shell or Compound  returns <True> is S has no free boundaries. <br>
Standard_EXPORT static  Standard_Boolean IsClosed(const TopoDS_Shape& S) ;

//! Returns the geometric surface of the face. Returns <br>
//!          in <L> the location for the surface. <br>
Standard_EXPORT static const Handle_Geom_Surface& Surface(const TopoDS_Face& F,TopLoc_Location& L) ;

//! Returns the geometric  surface of the face. It can <br>
//!          be a copy if there is a Location. <br>
//! <br>
Standard_EXPORT static  Handle_Geom_Surface Surface(const TopoDS_Face& F) ;

//! Returns  the Triangulation of  the  face. It  is a <br>
//!          null handle if there is no triangulation. <br>
//! <br>
Standard_EXPORT static const Handle_Poly_Triangulation& Triangulation(const TopoDS_Face& F,TopLoc_Location& L) ;

//! Returns the tolerance of the face. <br>
Standard_EXPORT static  Standard_Real Tolerance(const TopoDS_Face& F) ;

//! Returns the  NaturalRestriction  flag of the  face. <br>
Standard_EXPORT static  Standard_Boolean NaturalRestriction(const TopoDS_Face& F) ;

//! Returns True if <E> is a 3d curve or a curve on <br>
//!          surface. <br>
Standard_EXPORT static  Standard_Boolean IsGeometric(const TopoDS_Edge& E) ;

//! Returns the 3D curve  of the edge.  May be  a Null <br>
//!          handle. Returns in <L> the location for the curve. <br>
//!          In <First> and <Last> the parameter range. <br>
//! <br>
Standard_EXPORT static const Handle_Geom_Curve& Curve(const TopoDS_Edge& E,TopLoc_Location& L,Standard_Real& First,Standard_Real& Last) ;

//! Returns the 3D curve  of the edge. May be a Null handle. <br>
//!          In <First> and <Last> the parameter range. <br>
//!          It can be a copy if there is a Location. <br>
Standard_EXPORT static  Handle_Geom_Curve Curve(const TopoDS_Edge& E,Standard_Real& First,Standard_Real& Last) ;

//! Returns the 3D polygon of the edge. May be   a Null <br>
//!          handle. Returns in <L> the location for the polygon. <br>
//! <br>
Standard_EXPORT static const Handle_Poly_Polygon3D& Polygon3D(const TopoDS_Edge& E,TopLoc_Location& L) ;

//! Returns the curve  associated to the  edge in  the <br>
//!          parametric  space of  the  face.  Returns   a NULL <br>
//!          handle  if this curve  does not exist.  Returns in <br>
//!          <First> and <Last> the parameter range. <br>
Standard_EXPORT static  Handle_Geom2d_Curve CurveOnSurface(const TopoDS_Edge& E,const TopoDS_Face& F,Standard_Real& First,Standard_Real& Last) ;

//! Returns the  curve associated to   the edge in the <br>
//!          parametric  space of the   surface. Returns a NULL <br>
//!          handle  if this curve does  not exist.  Returns in <br>
//!          <First> and <Last> the parameter range. <br>
Standard_EXPORT static  Handle_Geom2d_Curve CurveOnSurface(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L,Standard_Real& First,Standard_Real& Last) ;

//! Returns in <C>, <S>, <L> a 2d curve, a surface and <br>
//!          a location for the edge <E>. <C> and <S>  are null <br>
//!          if the  edge has no curve on  surface.  Returns in <br>
//!          <First> and <Last> the parameter range. <br>
Standard_EXPORT static  void CurveOnSurface(const TopoDS_Edge& E,Handle(Geom2d_Curve)& C,Handle(Geom_Surface)& S,TopLoc_Location& L,Standard_Real& First,Standard_Real& Last) ;

//! Returns in <C>, <S>, <L> the 2d curve, the surface <br>
//!          and the location for the edge <E> of rank <Index>. <br>
//!          <C> and <S> are null if the index is out of range. <br>
//!          Returns in <First> and <Last> the parameter range. <br>
Standard_EXPORT static  void CurveOnSurface(const TopoDS_Edge& E,Handle(Geom2d_Curve)& C,Handle(Geom_Surface)& S,TopLoc_Location& L,Standard_Real& First,Standard_Real& Last,const Standard_Integer Index) ;

//! Returns the polygon associated to the  edge in  the <br>
//!          parametric  space of  the  face.  Returns   a NULL <br>
//!          handle  if this polygon  does not exist. <br>
Standard_EXPORT static  Handle_Poly_Polygon2D PolygonOnSurface(const TopoDS_Edge& E,const TopoDS_Face& F) ;

//! Returns the polygon associated to the  edge in  the <br>
//!          parametric  space of  the surface. Returns   a NULL <br>
//!          handle  if this polygon  does not exist. <br>
Standard_EXPORT static  Handle_Poly_Polygon2D PolygonOnSurface(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L) ;

//! Returns in <C>, <S>, <L> a 2d curve, a surface and <br>
//!          a location for the edge <E>. <C> and <S>  are null <br>
//!          if the  edge has no polygon on  surface. <br>
Standard_EXPORT static  void PolygonOnSurface(const TopoDS_Edge& E,Handle(Poly_Polygon2D)& C,Handle(Geom_Surface)& S,TopLoc_Location& L) ;

//! Returns in <C>, <S>, <L> the 2d curve, the surface <br>
//!          and the location for the edge <E> of rank <Index>. <br>
//!          <C> and <S> are null if the index is out of range. <br>
Standard_EXPORT static  void PolygonOnSurface(const TopoDS_Edge& E,Handle(Poly_Polygon2D)& C,Handle(Geom_Surface)& S,TopLoc_Location& L,const Standard_Integer Index) ;

//! Returns the polygon associated to the  edge in  the <br>
//!          parametric  space of  the  face.  Returns   a NULL <br>
//!          handle  if this polygon  does not exist. <br>
Standard_EXPORT static const Handle_Poly_PolygonOnTriangulation& PolygonOnTriangulation(const TopoDS_Edge& E,const Handle(Poly_Triangulation)& T,const TopLoc_Location& L) ;

//! Returns in <P>, <T>, <L> a polygon on triangulation, a <br>
//!          triangulation and a location for the edge <E>. <br>
//!          <P>  and  <T>  are null  if  the  edge has no <br>
//!          polygon on  triangulation. <br>
Standard_EXPORT static  void PolygonOnTriangulation(const TopoDS_Edge& E,Handle(Poly_PolygonOnTriangulation)& P,Handle(Poly_Triangulation)& T,TopLoc_Location& L) ;

//! Returns   in   <P>,  <T>,    <L> a     polygon  on <br>
//!          triangulation,   a triangulation  and a  location for <br>
//!          the edge <E> for the range index.  <C> and <S> are <br>
//!          null if the edge has no polygon on triangulation. <br>
Standard_EXPORT static  void PolygonOnTriangulation(const TopoDS_Edge& E,Handle(Poly_PolygonOnTriangulation)& P,Handle(Poly_Triangulation)& T,TopLoc_Location& L,const Standard_Integer Index) ;

//! Returns  True  if  <E>  has  two  PCurves  in  the <br>
//!          parametric space of <F>. i.e.  <F>  is on a closed <br>
//!          surface and <E> is on the closing curve. <br>
//! <br>
Standard_EXPORT static  Standard_Boolean IsClosed(const TopoDS_Edge& E,const TopoDS_Face& F) ;

//! Returns  True  if  <E>  has  two  PCurves  in  the <br>
//!          parametric space  of <S>.  i.e.   <S>  is a closed <br>
//!          surface and <E> is on the closing curve. <br>
//! <br>
Standard_EXPORT static  Standard_Boolean IsClosed(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L) ;

//! Returns  True  if <E> has two arrays of indices in <br>
//!          the triangulation <T>. <br>
Standard_EXPORT static  Standard_Boolean IsClosed(const TopoDS_Edge& E,const Handle(Poly_Triangulation)& T) ;

//! Returns the tolerance for <E>. <br>
Standard_EXPORT static  Standard_Real Tolerance(const TopoDS_Edge& E) ;

//! Returns the SameParameter flag for the edge. <br>
Standard_EXPORT static  Standard_Boolean SameParameter(const TopoDS_Edge& E) ;

//! Returns the SameRange flag for the edge. <br>
Standard_EXPORT static  Standard_Boolean SameRange(const TopoDS_Edge& E) ;

//! Returns True  if the edge is degenerated. <br>
Standard_EXPORT static  Standard_Boolean Degenerated(const TopoDS_Edge& E) ;

//! Gets the range of the 3d curve. <br>
Standard_EXPORT static  void Range(const TopoDS_Edge& E,Standard_Real& First,Standard_Real& Last) ;

//! Gets the range  of the edge  on the pcurve on  the <br>
//!          surface. <br>
Standard_EXPORT static  void Range(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L,Standard_Real& First,Standard_Real& Last) ;

//! Gets the range of the edge on the pcurve on the face. <br>
Standard_EXPORT static  void Range(const TopoDS_Edge& E,const TopoDS_Face& F,Standard_Real& First,Standard_Real& Last) ;

//! Gets the UV locations of the extremities of the edge. <br>
Standard_EXPORT static  void UVPoints(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L,gp_Pnt2d& PFirst,gp_Pnt2d& PLast) ;

//! Gets the UV locations of the extremities of the edge. <br>
Standard_EXPORT static  void UVPoints(const TopoDS_Edge& E,const TopoDS_Face& F,gp_Pnt2d& PFirst,gp_Pnt2d& PLast) ;

//! Sets the UV locations of the extremities of the edge. <br>
Standard_EXPORT static  void SetUVPoints(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L,const gp_Pnt2d& PFirst,const gp_Pnt2d& PLast) ;

//! Sets the UV locations of the extremities of the edge. <br>
Standard_EXPORT static  void SetUVPoints(const TopoDS_Edge& E,const TopoDS_Face& F,const gp_Pnt2d& PFirst,const gp_Pnt2d& PLast) ;

//! Gets the  UV box of the edge on the surface. <br>
//! <br>
Standard_EXPORT static const Bnd_Box2d& UVBox(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L) ;

//! Gets the UV box of the edge on the face. <br>
//! <br>
Standard_EXPORT static const Bnd_Box2d& UVBox(const TopoDS_Edge& E,const TopoDS_Face& F) ;

//! Gets the  UV box of the edge on the surface. <br>
//! <br>
Standard_EXPORT static  Bnd_Box2d& ChangeUVBox(const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L) ;

//! Gets the UV box of the edge on the face. <br>
//! <br>
Standard_EXPORT static  Bnd_Box2d& ChangeUVBox(const TopoDS_Edge& E,const TopoDS_Face& F) ;

//! Returns True if the edge is on the surfaces of the <br>
//!          two faces. <br>
Standard_EXPORT static  Standard_Boolean HasContinuity(const TopoDS_Edge& E,const TopoDS_Face& F1,const TopoDS_Face& F2) ;

//! Returns the continuity. <br>
Standard_EXPORT static  GeomAbs_Shape Continuity(const TopoDS_Edge& E,const TopoDS_Face& F1,const TopoDS_Face& F2) ;

//! Returns True if the edge is on the surfaces. <br>
Standard_EXPORT static  Standard_Boolean HasContinuity(const TopoDS_Edge& E,const Handle(Geom_Surface)& S1,const Handle(Geom_Surface)& S2,const TopLoc_Location& L1,const TopLoc_Location& L2) ;

//! Returns the continuity. <br>
Standard_EXPORT static  GeomAbs_Shape Continuity(const TopoDS_Edge& E,const Handle(Geom_Surface)& S1,const Handle(Geom_Surface)& S2,const TopLoc_Location& L1,const TopLoc_Location& L2) ;

//! Returns the 3d point. <br>
Standard_EXPORT static  gp_Pnt Pnt(const TopoDS_Vertex& V) ;

//! Returns the tolerance. <br>
Standard_EXPORT static  Standard_Real Tolerance(const TopoDS_Vertex& V) ;

//! Returns the parameter of <V> on <E>. <br>
Standard_EXPORT static  Standard_Real Parameter(const TopoDS_Vertex& V,const TopoDS_Edge& E) ;

//! Returns the  parameters  of   the  vertex   on the <br>
//!          pcurve of the edge on the face. <br>
Standard_EXPORT static  Standard_Real Parameter(const TopoDS_Vertex& V,const TopoDS_Edge& E,const TopoDS_Face& F) ;

//! Returns the  parameters  of   the  vertex   on the <br>
//!          pcurve of the edge on the surface. <br>
Standard_EXPORT static  Standard_Real Parameter(const TopoDS_Vertex& V,const TopoDS_Edge& E,const Handle(Geom_Surface)& S,const TopLoc_Location& L) ;

//! Returns the parameters of the vertex on the face. <br>
Standard_EXPORT static  gp_Pnt2d Parameters(const TopoDS_Vertex& V,const TopoDS_Face& F) ;





protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


 // Fields PRIVATE
 //


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
