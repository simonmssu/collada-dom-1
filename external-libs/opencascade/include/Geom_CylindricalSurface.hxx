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

#ifndef _Geom_CylindricalSurface_HeaderFile
#define _Geom_CylindricalSurface_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_Geom_CylindricalSurface_HeaderFile
#include <Handle_Geom_CylindricalSurface.hxx>
#endif

#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Geom_ElementarySurface_HeaderFile
#include <Geom_ElementarySurface.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Geom_Curve_HeaderFile
#include <Handle_Geom_Curve.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Geom_Geometry_HeaderFile
#include <Handle_Geom_Geometry.hxx>
#endif
class Standard_ConstructionError;
class Standard_RangeError;
class gp_Ax3;
class gp_Cylinder;
class gp_Trsf;
class gp_GTrsf2d;
class Geom_Curve;
class gp_Pnt;
class gp_Vec;
class Geom_Geometry;


//! This class defines the infinite cylindrical surface. <br>
//! <br>
//!  The local coordinate system of the CylindricalSurface is defined <br>
//!  with an axis placement (see class ElementarySurface). <br>
//! <br>
//!  The "ZAxis" is the symmetry axis of the CylindricalSurface, <br>
//!  it gives the direction of increasing parametric value V. <br>
//! <br>
//!  The parametrization range is : <br>
//!       U [0, 2*PI],  V ]- infinite, + infinite[ <br>
//! <br>
//!  The "XAxis" and the "YAxis" define the placement plane of the <br>
//!  surface (Z = 0, and parametric value V = 0)  perpendicular to <br>
//!  the symmetry axis. The "XAxis" defines the origin of the <br>
//!  parameter U = 0.  The trigonometric sense gives the positive <br>
//!  orientation for the parameter U. <br>
//! <br>
//!  When you create a CylindricalSurface the U and V directions of <br>
//!  parametrization are such that at each point of the surface the <br>
//!  normal is oriented towards the "outside region". <br>
//! <br>
//!  The methods UReverse VReverse change the orientation of the <br>
//!  surface. <br>
class Geom_CylindricalSurface : public Geom_ElementarySurface {

public:
 // Methods PUBLIC
 // 


//!  A3 defines the local coordinate system of the cylindrical surface. <br>
//!  The "ZDirection" of A3 defines the direction of the surface's <br>
//!  axis of symmetry. <br>
//!  At the creation the parametrization of the surface is defined <br>
//!  such that the normal Vector (N = D1U ^ D1V) is oriented towards <br>
//!  the "outside region" of the surface. <br>
//! Warnings : <br>
//!  It is not forbidden to create a cylindrical surface with <br>
//!  Radius = 0.0 <br>//! Raised if Radius < 0.0 <br>
Standard_EXPORT Geom_CylindricalSurface(const gp_Ax3& A3,const Standard_Real Radius);


//!  Creates a CylindricalSurface from a non transient Cylinder <br>
//!  from package gp. <br>
Standard_EXPORT Geom_CylindricalSurface(const gp_Cylinder& C);


//!  Set <me> so that <me> has the same geometric properties as C. <br>
Standard_EXPORT   void SetCylinder(const gp_Cylinder& C) ;

//! Changes the radius of the cylinder. <br>//! Raised if R < 0.0 <br>
Standard_EXPORT   void SetRadius(const Standard_Real R) ;


//!  returns a non transient cylinder with the same geometric <br>
//!  properties as <me>. <br>
Standard_EXPORT   gp_Cylinder Cylinder() const;

//! Return the  parameter on the  Ureversed surface for <br>
//!          the point of parameter U on <me>. <br>
//!          Return 2.PI - U. <br>
Standard_EXPORT   Standard_Real UReversedParameter(const Standard_Real U) const;

//! Return the  parameter on the  Vreversed surface for <br>
//!          the point of parameter V on <me>. <br>
//!          Return -V <br>
Standard_EXPORT   Standard_Real VReversedParameter(const Standard_Real V) const;

//! Computes the  parameters on the  transformed  surface for <br>
//! the transform of the point of parameters U,V on <me>. <br>
//!          me->Transformed(T)->Value(U',V') <br>
//!          is the same point as <br>
//!          me->Value(U,V).Transformed(T) <br>
//!   Where U',V' are the new values of U,V after calling <br>
//!          me->TranformParameters(U,V,T) <br>
//!          This methods multiplies V by T.ScaleFactor() <br>
Standard_EXPORT virtual  void TransformParameters(Standard_Real& U,Standard_Real& V,const gp_Trsf& T) const;

//! Returns a 2d transformation  used to find the  new <br>
//!          parameters of a point on the transformed surface. <br>
//!          me->Transformed(T)->Value(U',V') <br>
//!          is the same point as <br>
//!          me->Value(U,V).Transformed(T) <br>
//!  Where U',V' are  obtained by transforming U,V with <br>
//!          th 2d transformation returned by <br>
//!          me->ParametricTransformation(T) <br>
//!    This  methods  returns  a scale  centered  on  the <br>
//!          U axis with T.ScaleFactor <br>
Standard_EXPORT virtual  gp_GTrsf2d ParametricTransformation(const gp_Trsf& T) const;


//!  The CylindricalSurface is infinite in the V direction so <br>
//!  V1 = Realfirst, V2 = RealLast from package Standard. <br>
//!  U1 = 0 and U2 = 2*PI. <br>
Standard_EXPORT   void Bounds(Standard_Real& U1,Standard_Real& U2,Standard_Real& V1,Standard_Real& V2) const;


//!  Returns the coefficients of the implicit equation of the quadric <br>
//!  in the absolute cartesian coordinate system : <br>
//!  These coefficients are normalized. <br>
//!  A1.X**2 + A2.Y**2 + A3.Z**2 + 2.(B1.X.Y + B2.X.Z + B3.Y.Z) + <br>
//!  2.(C1.X + C2.Y + C3.Z) + D = 0.0 <br>
Standard_EXPORT   void Coefficients(Standard_Real& A1,Standard_Real& A2,Standard_Real& A3,Standard_Real& B1,Standard_Real& B2,Standard_Real& B3,Standard_Real& C1,Standard_Real& C2,Standard_Real& C3,Standard_Real& D) const;

//! Returns the radius of this cylinder. <br>
Standard_EXPORT   Standard_Real Radius() const;

//! Returns True. <br>
Standard_EXPORT   Standard_Boolean IsUClosed() const;

//! Returns False. <br>
Standard_EXPORT   Standard_Boolean IsVClosed() const;

//! Returns True. <br>
Standard_EXPORT   Standard_Boolean IsUPeriodic() const;

//! Returns False. <br>
Standard_EXPORT   Standard_Boolean IsVPeriodic() const;


//!  The UIso curve is a Line. The location point of this line is <br>
//!  on the placement plane (XAxis, YAxis) of the surface. <br>
//!  This line is parallel to the axis of symmetry of the surface. <br>
Standard_EXPORT   Handle_Geom_Curve UIso(const Standard_Real U) const;


//!  The VIso curve is a circle. The start point of this circle <br>
//!  (U = 0) is defined with the "XAxis" of the surface. <br>
//!  The center of the circle is on the symmetry axis. <br>
Standard_EXPORT   Handle_Geom_Curve VIso(const Standard_Real V) const;


//!  Computes the  point P (U, V) on the surface. <br>
//!  P (U, V) = Loc + Radius * (cos (U) * XDir + sin (U) * YDir) + <br>
//!             V * ZDir <br>
//!  where Loc is the origin of the placement plane (XAxis, YAxis) <br>
//!  XDir is the direction of the XAxis and YDir the direction of <br>
//!  the YAxis. <br>
Standard_EXPORT   void D0(const Standard_Real U,const Standard_Real V,gp_Pnt& P) const;


//!  Computes the current point and the first derivatives in the <br>
//!  directions U and V. <br>
Standard_EXPORT   void D1(const Standard_Real U,const Standard_Real V,gp_Pnt& P,gp_Vec& D1U,gp_Vec& D1V) const;


//!  Computes the current point, the first and the second derivatives <br>
//!  in the directions U and V. <br>
Standard_EXPORT   void D2(const Standard_Real U,const Standard_Real V,gp_Pnt& P,gp_Vec& D1U,gp_Vec& D1V,gp_Vec& D2U,gp_Vec& D2V,gp_Vec& D2UV) const;


//!  Computes the current point, the first, the second and the <br>
//!  third   derivatives in the directions U and V. <br>
Standard_EXPORT   void D3(const Standard_Real U,const Standard_Real V,gp_Pnt& P,gp_Vec& D1U,gp_Vec& D1V,gp_Vec& D2U,gp_Vec& D2V,gp_Vec& D2UV,gp_Vec& D3U,gp_Vec& D3V,gp_Vec& D3UUV,gp_Vec& D3UVV) const;


//!  Computes the derivative of order Nu in the direction u and Nv <br>
//!  in the direction v. <br>//! Raised if Nu + Nv < 1 or Nu < 0 or Nv < 0. <br>
Standard_EXPORT   gp_Vec DN(const Standard_Real U,const Standard_Real V,const Standard_Integer Nu,const Standard_Integer Nv) const;

//!  Applies the transformation T to this cylinder. <br>
Standard_EXPORT   void Transform(const gp_Trsf& T) ;

//!  Creates a new object which is a copy of this cylinder. <br>
Standard_EXPORT   Handle_Geom_Geometry Copy() const;
//Standard_EXPORT ~Geom_CylindricalSurface();




 // Type management
 //
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;
 //Standard_EXPORT Standard_Boolean	       IsKind(const Handle(Standard_Type)&) const;

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
Standard_Real radius;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif