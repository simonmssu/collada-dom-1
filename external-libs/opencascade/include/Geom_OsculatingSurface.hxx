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

#ifndef _Geom_OsculatingSurface_HeaderFile
#define _Geom_OsculatingSurface_HeaderFile

#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_Geom_HSequenceOfBSplineSurface_HeaderFile
#include <Handle_Geom_HSequenceOfBSplineSurface.hxx>
#endif
#ifndef _Handle_TColStd_HSequenceOfInteger_HeaderFile
#include <Handle_TColStd_HSequenceOfInteger.hxx>
#endif
#ifndef _TColStd_Array1OfBoolean_HeaderFile
#include <TColStd_Array1OfBoolean.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Geom_BSplineSurface_HeaderFile
#include <Handle_Geom_BSplineSurface.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _GeomAbs_IsoType_HeaderFile
#include <GeomAbs_IsoType.hxx>
#endif
class Geom_Surface;
class Geom_HSequenceOfBSplineSurface;
class TColStd_HSequenceOfInteger;
class Geom_BSplineSurface;
class Geom_SequenceOfBSplineSurface;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif


class Geom_OsculatingSurface  {

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


Standard_EXPORT Geom_OsculatingSurface();

//! detects if the  surface has punctual U  or  V <br>
//!  isoparametric  curve along on  the bounds of the surface <br>
//!  relativly to the tolerance Tol and Builds the corresponding <br>
//!  osculating surfaces. <br>
Standard_EXPORT Geom_OsculatingSurface(const Handle(Geom_Surface)& BS,const Standard_Real Tol);


Standard_EXPORT   void Init(const Handle(Geom_Surface)& BS,const Standard_Real Tol) ;


Standard_EXPORT   Handle_Geom_Surface BasisSurface() const;


Standard_EXPORT   Standard_Real Tolerance() const;

//! if Standard_True, L is the local osculating surface <br>
//!          along U at the point U,V. <br>
Standard_EXPORT   Standard_Boolean UOscSurf(const Standard_Real U,const Standard_Real V,Standard_Boolean& t,Handle(Geom_BSplineSurface)& L) const;

//! if Standard_True, L is the local osculating surface <br>
//!          along V at the point U,V. <br>
Standard_EXPORT   Standard_Boolean VOscSurf(const Standard_Real U,const Standard_Real V,Standard_Boolean& t,Handle(Geom_BSplineSurface)& L) const;





protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 

//! returns False if the osculating surface can't be built <br>
//! <br>
Standard_EXPORT   Standard_Boolean BuildOsculatingSurface(const Standard_Real Param,const Standard_Integer UKnot,const Standard_Integer VKnot,const Handle(Geom_BSplineSurface)& BS,Handle(Geom_BSplineSurface)& L) const;

//! returns    True    if  the    isoparametric     is <br>
//!          quasi-punctual <br>
Standard_EXPORT   Standard_Boolean IsQPunctual(const Handle(Geom_Surface)& S,const Standard_Real Param,const GeomAbs_IsoType IT,const Standard_Real TolMin,const Standard_Real TolMax) const;


Standard_EXPORT   Standard_Boolean HasOscSurf() const;


Standard_EXPORT   Standard_Boolean IsAlongU() const;


Standard_EXPORT   Standard_Boolean IsAlongV() const;


Standard_EXPORT   void ClearOsculFlags() ;


Standard_EXPORT  const Geom_SequenceOfBSplineSurface& GetSeqOfL1() const;


Standard_EXPORT  const Geom_SequenceOfBSplineSurface& GetSeqOfL2() const;


 // Fields PRIVATE
 //
Handle_Geom_Surface myBasisSurf;
Standard_Real myTol;
Handle_Geom_HSequenceOfBSplineSurface myOsculSurf1;
Handle_Geom_HSequenceOfBSplineSurface myOsculSurf2;
Handle_TColStd_HSequenceOfInteger myKdeg;
TColStd_Array1OfBoolean myAlong;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif