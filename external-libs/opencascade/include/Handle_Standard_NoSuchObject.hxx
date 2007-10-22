// File generated by CPPExt (Transient)
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

#ifndef _Handle_Standard_NoSuchObject_HeaderFile
#define _Handle_Standard_NoSuchObject_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_Standard_DomainError_HeaderFile
#include <Handle_Standard_DomainError.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(Standard_DomainError);
class Standard_NoSuchObject;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(Standard_NoSuchObject);

class Handle(Standard_NoSuchObject) : public Handle(Standard_DomainError) {
  public:
    Handle(Standard_NoSuchObject)():Handle(Standard_DomainError)() {} 
    Handle(Standard_NoSuchObject)(const Handle(Standard_NoSuchObject)& aHandle) : Handle(Standard_DomainError)(aHandle) 
     {
     }

    Handle(Standard_NoSuchObject)(const Standard_NoSuchObject* anItem) : Handle(Standard_DomainError)((Standard_DomainError *)anItem) 
     {
     }

    Handle(Standard_NoSuchObject)& operator=(const Handle(Standard_NoSuchObject)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(Standard_NoSuchObject)& operator=(const Standard_NoSuchObject* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    Standard_NoSuchObject* operator->() const
     {
      return (Standard_NoSuchObject *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(Standard_NoSuchObject)();
 
   Standard_EXPORT static const Handle(Standard_NoSuchObject) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif