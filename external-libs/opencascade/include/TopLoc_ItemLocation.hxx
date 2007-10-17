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

#ifndef _TopLoc_ItemLocation_HeaderFile
#define _TopLoc_ItemLocation_HeaderFile

#ifndef _Handle_TopLoc_Datum3D_HeaderFile
#include <Handle_TopLoc_Datum3D.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _TopLoc_TrsfPtr_HeaderFile
#include <TopLoc_TrsfPtr.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class TopLoc_Datum3D;
class TopLoc_Location;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//! An ItemLocation is an elementary coordinate system <br>
//!          in a Location. <br>
//! <br>
//!          The  ItemLocation     contains : <br>
//! <br>
//!          * The elementary Datum. <br>
//! <br>
//!          * The exponent of the elementary Datum. <br>
//! <br>
//!          * The transformation associated to the composition. <br>
//! <br>
class TopLoc_ItemLocation  {

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

//! Sets the elementary Datum to <D> <br>
//!          Sets the exponent to <P> <br>
Standard_EXPORT TopLoc_ItemLocation(const Handle(TopLoc_Datum3D)& D,const Standard_Integer P,const Standard_Boolean fromTrsf = Standard_False);


Standard_EXPORT TopLoc_ItemLocation(const TopLoc_ItemLocation& anOther);


Standard_EXPORT   TopLoc_ItemLocation& Assign(const TopLoc_ItemLocation& anOther) ;
  TopLoc_ItemLocation& operator=(const TopLoc_ItemLocation& anOther) 
{
  return Assign(anOther);
}



Standard_EXPORT   void Destroy() ;
~TopLoc_ItemLocation()
{
  Destroy();
}



friend class TopLoc_Location;



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
Handle_TopLoc_Datum3D myDatum;
Standard_Integer myPower;
TopLoc_TrsfPtr myTrsf;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
