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

#ifndef _BRepLib_MakeEdge_HeaderFile
#define _BRepLib_MakeEdge_HeaderFile

#ifndef _BRepLib_EdgeError_HeaderFile
#include <BRepLib_EdgeError.hxx>
#endif
#ifndef _TopoDS_Vertex_HeaderFile
#include <TopoDS_Vertex.hxx>
#endif
#ifndef _BRepLib_MakeShape_HeaderFile
#include <BRepLib_MakeShape.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_Geom_Curve_HeaderFile
#include <Handle_Geom_Curve.hxx>
#endif
#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
class StdFail_NotDone;
class TopoDS_Vertex;
class gp_Pnt;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;
class TopoDS_Edge;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//! Provides methods to build edges. <br>
//! <br>
//!          The   methods have  the  following   syntax, where <br>
//!          TheCurve is one of Lin, Circ, ... <br>
//! <br>
//!          Create(C : TheCurve) <br>
//! <br>
//!            Makes an edge on  the whole curve.  Add vertices <br>
//!            on finite curves. <br>
//! <br>
//!          Create(C : TheCurve; p1,p2 : Real) <br>
//! <br>
//!            Make an edge  on the curve between parameters p1 <br>
//!            and p2. if p2 < p1 the edge will be REVERSED. If <br>
//!            p1  or p2 is infinite the  curve will be open in <br>
//!            that  direction. Vertices are created for finite <br>
//!            values of p1 and p2. <br>
//! <br>
//!          Create(C : TheCurve; P1, P2 : Pnt from gp) <br>
//! <br>
//!            Make an edge on the curve  between the points P1 <br>
//!            and P2. The  points are projected on   the curve <br>
//!            and the   previous method is  used. An  error is <br>
//!            raised if the points are not on the curve. <br>
//! <br>
//!          Create(C : TheCurve; V1, V2 : Vertex from TopoDS) <br>
//! <br>
//!            Make an edge  on the curve  between the vertices <br>
//!            V1 and V2. Same as the  previous but no vertices <br>
//!            are created. If a vertex is  Null the curve will <br>
//!            be open in this direction. <br>
class BRepLib_MakeEdge  : public BRepLib_MakeShape {

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


Standard_EXPORT BRepLib_MakeEdge();


Standard_EXPORT BRepLib_MakeEdge(const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Lin& L);


Standard_EXPORT BRepLib_MakeEdge(const gp_Lin& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Lin& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Lin& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Circ& L);


Standard_EXPORT BRepLib_MakeEdge(const gp_Circ& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Circ& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Circ& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Elips& L);


Standard_EXPORT BRepLib_MakeEdge(const gp_Elips& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Elips& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Elips& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Hypr& L);


Standard_EXPORT BRepLib_MakeEdge(const gp_Hypr& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Hypr& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Hypr& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Parab& L);


Standard_EXPORT BRepLib_MakeEdge(const gp_Parab& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Parab& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const gp_Parab& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L,const gp_Pnt& P1,const gp_Pnt& P2,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom_Curve)& L,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S,const gp_Pnt& P1,const gp_Pnt& P2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S,const gp_Pnt& P1,const gp_Pnt& P2,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT BRepLib_MakeEdge(const Handle(Geom2d_Curve)& L,const Handle(Geom_Surface)& S,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2,const Standard_Real p1,const Standard_Real p2);


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C) ;


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C,const Standard_Real p1,const Standard_Real p2) ;


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C,const gp_Pnt& P1,const gp_Pnt& P2) ;


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2) ;


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C,const gp_Pnt& P1,const gp_Pnt& P2,const Standard_Real p1,const Standard_Real p2) ;


Standard_EXPORT   void Init(const Handle(Geom_Curve)& C,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2,const Standard_Real p1,const Standard_Real p2) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S,const Standard_Real p1,const Standard_Real p2) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S,const gp_Pnt& P1,const gp_Pnt& P2) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S,const gp_Pnt& P1,const gp_Pnt& P2,const Standard_Real p1,const Standard_Real p2) ;


Standard_EXPORT   void Init(const Handle(Geom2d_Curve)& C,const Handle(Geom_Surface)& S,const TopoDS_Vertex& V1,const TopoDS_Vertex& V2,const Standard_Real p1,const Standard_Real p2) ;

//! Returns the error description when NotDone. <br>
Standard_EXPORT   BRepLib_EdgeError Error() const;


Standard_EXPORT  const TopoDS_Edge& Edge() const;
Standard_EXPORT operator TopoDS_Edge() const;

//! Returns the first vertex of the edge. May be Null. <br>
//! <br>
Standard_EXPORT  const TopoDS_Vertex& Vertex1() const;

//! Returns the second vertex of the edge. May be Null. <br>
//! <br>
Standard_EXPORT  const TopoDS_Vertex& Vertex2() const;





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
BRepLib_EdgeError myError;
TopoDS_Vertex myVertex1;
TopoDS_Vertex myVertex2;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
