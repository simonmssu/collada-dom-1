// File generated by CPPExt (Storable)
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

#ifndef _gp_Ax2d_HeaderFile
#define _gp_Ax2d_HeaderFile

#ifndef _gp_Pnt2d_HeaderFile
#include <gp_Pnt2d.hxx>
#endif
#ifndef _gp_Dir2d_HeaderFile
#include <gp_Dir2d.hxx>
#endif
#ifndef _Standard_Storable_HeaderFile
#include <Standard_Storable.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_PrimitiveTypes_HeaderFile
#include <Standard_PrimitiveTypes.hxx>
#endif
class gp_Pnt2d;
class gp_Dir2d;
class gp_Trsf2d;
class gp_Vec2d;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

Standard_EXPORT Handle_Standard_Type& gp_Ax2d_Type_();


//! Describes an axis in the plane (2D space). <br>
//! An axis is defined by: <br>
//! -   its origin (also referred to as its "Location point"),   and <br>
//! -   its unit vector (referred to as its "Direction"). <br>
//! An axis implicitly defines a direct, right-handed <br>
//! coordinate system in 2D space by: <br>
//! -   its origin, <br>
//! - its "Direction" (giving the "X Direction" of the coordinate system), and <br>
//! -   the unit vector normal to "Direction" (positive angle <br>
//!   measured in the trigonometric sense). <br>
//! An axis is used: <br>
//! -   to describe 2D geometric entities (for example, the <br>
//!   axis which defines angular coordinates on a circle). <br>
//!   It serves for the same purpose as the STEP function <br>
//!   "axis placement one axis", or <br>
//! -   to define geometric transformations (axis of <br>
//!   symmetry, axis of rotation, and so on). <br>
//! Note: to define a left-handed 2D coordinate system, use gp_Ax22d. <br>
class gp_Ax2d  {

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
//! Creates an indefinite Ax2d <br>
gp_Ax2d();

//!  Creates an Ax2d. <P> is the "Location" point of <br>
//!  the axis placement and V is the "Direction" of <br>
//!  the axis placement. <br>
gp_Ax2d(const gp_Pnt2d& P,const gp_Dir2d& V);
//!  Changes the "Location" point (origin) of <me>. <br>
  void SetLocation(const gp_Pnt2d& Locat) ;
//! Changes the direction of <me>. <br>
  void SetDirection(const gp_Dir2d& V) ;
//! Returns the origin of <me>. <br>
 const gp_Pnt2d& Location() const;
//! Returns the direction of <me>. <br>
 const gp_Dir2d& Direction() const;


//!  Returns True if  : <br>
//!  . the angle between <me> and <Other> is lower or equal <br>
//!    to <AngularTolerance> and <br>
//!  . the distance between <me>.Location() and <Other> is lower <br>
//!    or equal to <LinearTolerance> and <br>
//!  . the distance between <Other>.Location() and <me> is lower <br>
//!    or equal to LinearTolerance. <br>
Standard_EXPORT   Standard_Boolean IsCoaxial(const gp_Ax2d& Other,const Standard_Real AngularTolerance,const Standard_Real LinearTolerance) const;
//! Returns true if this axis and the axis Other are normal to <br>
//! each other. That is, if the angle between the two axes is equal to Pi/2 or -Pi/2. <br>
//! Note: the tolerance criterion is given by AngularTolerance. <br>
  Standard_Boolean IsNormal(const gp_Ax2d& Other,const Standard_Real AngularTolerance) const;
//! Returns true if this axis and the axis Other are parallel, <br>
//! and have opposite orientations. That is, if the angle <br>
//! between the two axes is equal to Pi or -Pi. <br>
//! Note: the tolerance criterion is given by AngularTolerance. <br>
  Standard_Boolean IsOpposite(const gp_Ax2d& Other,const Standard_Real AngularTolerance) const;
//!  Returns true if this axis and the axis Other are parallel, <br>
//! and have either the same or opposite orientations. That <br>
//! is, if the angle between the two axes is equal to 0, Pi or -Pi. <br>
//! Note: the tolerance criterion is given by AngularTolerance. <br>
  Standard_Boolean IsParallel(const gp_Ax2d& Other,const Standard_Real AngularTolerance) const;

//! Computes the angle, in radians, between this axis and <br>
//! the axis Other. The value of the angle is between -Pi and Pi. <br>
  Standard_Real Angle(const gp_Ax2d& Other) const;
//! Reverses the direction of <me> and assigns the result to this axis. <br>
  void Reverse() ;

//!  Computes a new axis placement with a direction opposite to <br>
//!  the direction of <me>. <br>
  gp_Ax2d Reversed() const;


Standard_EXPORT   void Mirror(const gp_Pnt2d& P) ;


//!  Performs the symmetrical transformation of an axis <br>
//!  placement with respect to the point P which is the <br>
//!  center of the symmetry. <br>
Standard_EXPORT   gp_Ax2d Mirrored(const gp_Pnt2d& P) const;


Standard_EXPORT   void Mirror(const gp_Ax2d& A) ;


//!  Performs the symmetrical transformation of an axis <br>
//!  placement with respect to an axis placement which <br>
//!  is the axis of the symmetry. <br>
Standard_EXPORT   gp_Ax2d Mirrored(const gp_Ax2d& A) const;

  void Rotate(const gp_Pnt2d& P,const Standard_Real Ang) ;

//!  Rotates an axis placement. <P> is the center of the <br>
//!  rotation . Ang is the angular value of the rotation <br>
//!  in radians. <br>
  gp_Ax2d Rotated(const gp_Pnt2d& P,const Standard_Real Ang) const;


Standard_EXPORT   void Scale(const gp_Pnt2d& P,const Standard_Real S) ;

//!  Applies a scaling transformation on the axis placement. <br>
//!  The "Location" point of the axisplacement is modified. <br>
//!  The "Direction" is reversed if the scale is negative. <br>
  gp_Ax2d Scaled(const gp_Pnt2d& P,const Standard_Real S) const;

  void Transform(const gp_Trsf2d& T) ;
//!  Transforms an axis placement with a Trsf. <br>
  gp_Ax2d Transformed(const gp_Trsf2d& T) const;

  void Translate(const gp_Vec2d& V) ;

//!  Translates an axis placement in the direction of the vector <br>
//!  <V>. The magnitude of the translation is the vector's magnitude. <br>
  gp_Ax2d Translated(const gp_Vec2d& V) const;

  void Translate(const gp_Pnt2d& P1,const gp_Pnt2d& P2) ;

//!  Translates an axis placement from the point <P1> to the <br>
//!  point <P2>. <br>
  gp_Ax2d Translated(const gp_Pnt2d& P1,const gp_Pnt2d& P2) const;
    const gp_Pnt2d& _CSFDB_Getgp_Ax2dloc() const { return loc; }
    const gp_Dir2d& _CSFDB_Getgp_Ax2dvdir() const { return vdir; }




 // Type management
 //
 Standard_EXPORT friend Handle_Standard_Type& gp_Ax2d_Type_();

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
gp_Pnt2d loc;
gp_Dir2d vdir;


};


#include <gp_Ax2d.lxx>



// other Inline functions and methods (like "C++: function call" methods)
//


#endif