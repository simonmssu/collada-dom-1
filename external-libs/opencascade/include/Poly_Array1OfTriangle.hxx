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

#ifndef _Poly_Array1OfTriangle_HeaderFile
#define _Poly_Array1OfTriangle_HeaderFile

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class Poly_Triangle;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif


class Poly_Array1OfTriangle  {

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


Standard_EXPORT Poly_Array1OfTriangle(const Standard_Integer Low,const Standard_Integer Up);


Standard_EXPORT Poly_Array1OfTriangle(const Poly_Triangle& Item,const Standard_Integer Low,const Standard_Integer Up);


Standard_EXPORT   void Init(const Poly_Triangle& V) ;


Standard_EXPORT   void Destroy() ;
~Poly_Array1OfTriangle()
{
  Destroy();
}


  Standard_Boolean IsAllocated() const;


Standard_EXPORT  const Poly_Array1OfTriangle& Assign(const Poly_Array1OfTriangle& Other) ;
 const Poly_Array1OfTriangle& operator =(const Poly_Array1OfTriangle& Other) 
{
  return Assign(Other);
}


  Standard_Integer Length() const;

  Standard_Integer Lower() const;

  Standard_Integer Upper() const;

  void SetValue(const Standard_Integer Index,const Poly_Triangle& Value) ;

 const Poly_Triangle& Value(const Standard_Integer Index) const;
 const Poly_Triangle& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}


  Poly_Triangle& ChangeValue(const Standard_Integer Index) ;
  Poly_Triangle& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}






protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


Standard_EXPORT Poly_Array1OfTriangle(const Poly_Array1OfTriangle& AnArray);


 // Fields PRIVATE
 //
Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Poly_Triangle
#define Array1Item_hxx <Poly_Triangle.hxx>
#define TCollection_Array1 Poly_Array1OfTriangle
#define TCollection_Array1_hxx <Poly_Array1OfTriangle.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)
//


#endif
