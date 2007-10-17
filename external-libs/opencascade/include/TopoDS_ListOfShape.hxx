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

#ifndef _TopoDS_ListOfShape_HeaderFile
#define _TopoDS_ListOfShape_HeaderFile

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Handle_TopoDS_ListNodeOfListOfShape_HeaderFile
#include <Handle_TopoDS_ListNodeOfListOfShape.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class TopoDS_ListIteratorOfListOfShape;
class TopoDS_Shape;
class TopoDS_ListNodeOfListOfShape;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif


class TopoDS_ListOfShape  {

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


Standard_EXPORT TopoDS_ListOfShape();


Standard_EXPORT   void Assign(const TopoDS_ListOfShape& Other) ;
  void operator=(const TopoDS_ListOfShape& Other) 
{
  Assign(Other);
}



Standard_EXPORT   Standard_Integer Extent() const;


Standard_EXPORT   void Clear() ;
~TopoDS_ListOfShape()
{
  Clear();
}


  Standard_Boolean IsEmpty() const;


Standard_EXPORT   void Prepend(const TopoDS_Shape& I) ;


Standard_EXPORT   void Prepend(const TopoDS_Shape& I,TopoDS_ListIteratorOfListOfShape& theIt) ;


Standard_EXPORT   void Prepend(TopoDS_ListOfShape& Other) ;


Standard_EXPORT   void Append(const TopoDS_Shape& I) ;


Standard_EXPORT   void Append(const TopoDS_Shape& I,TopoDS_ListIteratorOfListOfShape& theIt) ;


Standard_EXPORT   void Append(TopoDS_ListOfShape& Other) ;


Standard_EXPORT   TopoDS_Shape& First() const;


Standard_EXPORT   TopoDS_Shape& Last() const;


Standard_EXPORT   void RemoveFirst() ;


Standard_EXPORT   void Remove(TopoDS_ListIteratorOfListOfShape& It) ;


Standard_EXPORT   void InsertBefore(const TopoDS_Shape& I,TopoDS_ListIteratorOfListOfShape& It) ;


Standard_EXPORT   void InsertBefore(TopoDS_ListOfShape& Other,TopoDS_ListIteratorOfListOfShape& It) ;


Standard_EXPORT   void InsertAfter(const TopoDS_Shape& I,TopoDS_ListIteratorOfListOfShape& It) ;


Standard_EXPORT   void InsertAfter(TopoDS_ListOfShape& Other,TopoDS_ListIteratorOfListOfShape& It) ;


friend class TopoDS_ListIteratorOfListOfShape;



protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


Standard_EXPORT TopoDS_ListOfShape(const TopoDS_ListOfShape& Other);


 // Fields PRIVATE
 //
Standard_Address myFirst;
Standard_Address myLast;


};

#define Item TopoDS_Shape
#define Item_hxx <TopoDS_Shape.hxx>
#define TCollection_ListNode TopoDS_ListNodeOfListOfShape
#define TCollection_ListNode_hxx <TopoDS_ListNodeOfListOfShape.hxx>
#define TCollection_ListIterator TopoDS_ListIteratorOfListOfShape
#define TCollection_ListIterator_hxx <TopoDS_ListIteratorOfListOfShape.hxx>
#define Handle_TCollection_ListNode Handle_TopoDS_ListNodeOfListOfShape
#define TCollection_ListNode_Type_() TopoDS_ListNodeOfListOfShape_Type_()
#define TCollection_List TopoDS_ListOfShape
#define TCollection_List_hxx <TopoDS_ListOfShape.hxx>

#include <TCollection_List.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx


// other Inline functions and methods (like "C++: function call" methods)
//


#endif
