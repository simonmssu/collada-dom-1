// File generated by CPPExt (Transient)
//
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

#ifndef _Geom_ElementarySurface_HeaderFile
#define _Geom_ElementarySurface_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_Geom_ElementarySurface_HeaderFile
#include <Handle_Geom_ElementarySurface.hxx>
#endif

#ifndef _gp_Ax3_HeaderFile
#include <gp_Ax3.hxx>
#endif
#ifndef _Geom_Surface_HeaderFile
#include <Geom_Surface.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_ConstructionError;
class gp_Ax1;
class gp_Pnt;
class gp_Ax3;


//! Describes the common behavior of surfaces which <br>
//! have a simple parametric equation in a local <br>
//! coordinate system. The Geom package provides <br>
//! several implementations of concrete elementary surfaces: <br>
//! - the plane, and <br>
//! - four simple surfaces of revolution: the cylinder, the <br>
//!   cone, the sphere and the torus. <br>
//! An elementary surface inherits the common behavior <br>
//! of Geom_Surface surfaces. Furthermore, it is located <br>
//! in 3D space by a coordinate system (a gp_Ax3 <br>
//! object) which is also its local coordinate system. <br>
//! Any elementary surface is oriented, i.e. the normal <br>
//! vector is always defined, and gives the same <br>
//! orientation to the surface, at any point on the surface. <br>
//! In topology this property is referred to as the "outside <br>
//! region of the surface". This orientation is related to <br>
//! the two parametric directions of the surface. <br>
//! Rotation of a surface around the "main Axis" of its <br>
//! coordinate system, in the trigonometric sense given <br>
//! by the "X Direction" and the "Y Direction" of the <br>
//! coordinate system, defines the u parametric direction <br>
//! of that elementary surface of revolution. This is the <br>
//! default construction mode. <br>
//! It is also possible, however, to change the orientation <br>
//! of a surface by reversing one of the two parametric <br>
//! directions: use the UReverse or VReverse functions <br>
//! to change the orientation of the normal at any point on the surface. <br>
//! Warning <br>
//! The local coordinate system of an elementary surface <br>
//! is not necessarily direct: <br>
//! - if it is direct, the trigonometric sense defined by its <br>
//! "main Direction" is the same as the trigonometric <br>
//!  sense defined by its two vectors "X Direction" and "Y Direction": <br>
//!   "main Direction" = "X Direction" ^ "Y Direction" <br>
//! - if it is indirect, the two definitions of trigonometric <br>
//!   sense are opposite: <br>
//! "main Direction" = - "X Direction" ^ "Y Direction" <br>
class Geom_ElementarySurface : public Geom_Surface {

public:
 // Methods PUBLIC
 // 


//!  Changes the main axis (ZAxis) of the elementary surface. <br>
//!  Raised if the direction of A1 is parallel to the XAxis of the <br>
//!  coordinate system of the surface. <br>
Standard_EXPORT   void SetAxis(const gp_Ax1& A1) ;


//!  Changes the location of the local coordinates system of the <br>
//!  surface. <br>
Standard_EXPORT   void SetLocation(const gp_Pnt& Loc) ;


//!  Changes the local coordinates system of the surface. <br>
Standard_EXPORT   void SetPosition(const gp_Ax3& A3) ;


//!  Returns the main axis of the surface (ZAxis). <br>
Standard_EXPORT   gp_Ax1 Axis() const;


//!  Returns the location point of the local coordinate system of the <br>
//!  surface. <br>
Standard_EXPORT   gp_Pnt Location() const;

//! Returns the local coordinates system of the surface. <br>
Standard_EXPORT  const gp_Ax3& Position() const;


//!  Reverses the U parametric direction of the surface. <br>
Standard_EXPORT virtual  void UReverse() ;

//! Return the  parameter on the  Ureversed surface for <br>
//!          the point of parameter U on <me>. <br>
//! <br>
//!          me->UReversed()->Value(me->UReversedParameter(U),V) <br>
//!            is the same point as <br>
//!          me->Value(U,V) <br>
Standard_EXPORT virtual  Standard_Real UReversedParameter(const Standard_Real U) const = 0;


//!  Reverses the V parametric direction of the surface. <br>
Standard_EXPORT virtual  void VReverse() ;

//! Return the  parameter on the  Vreversed surface for <br>
//!          the point of parameter V on <me>. <br>
//! <br>
//!          me->VReversed()->Value(U,me->VReversedParameter(V)) <br>
//!            is the same point as <br>
//!          me->Value(U,V) <br>
Standard_EXPORT virtual  Standard_Real VReversedParameter(const Standard_Real V) const = 0;

//! Returns GeomAbs_CN, the global continuity of any elementary surface. <br>
Standard_EXPORT   GeomAbs_Shape Continuity() const;

//! Returns True. <br>
Standard_EXPORT   Standard_Boolean IsCNu(const Standard_Integer N) const;

//! Returns True. <br>
Standard_EXPORT   Standard_Boolean IsCNv(const Standard_Integer N) const;
//Standard_EXPORT ~Geom_ElementarySurface();




 // Type management
 //
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;
 //Standard_EXPORT Standard_Boolean	       IsKind(const Handle(Standard_Type)&) const;

protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //
gp_Ax3 pos;


private: 

 // Methods PRIVATE
 // 


 // Fields PRIVATE
 //


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
