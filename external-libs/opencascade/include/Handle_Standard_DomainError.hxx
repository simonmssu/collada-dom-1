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

#ifndef _Handle_Standard_DomainError_HeaderFile
#define _Handle_Standard_DomainError_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_Standard_Failure_HeaderFile
#include <Handle_Standard_Failure.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(Standard_Failure);
class Standard_DomainError;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(Standard_DomainError);

class Handle(Standard_DomainError) : public Handle(Standard_Failure) {
  public:
    Handle(Standard_DomainError)():Handle(Standard_Failure)() {} 
    Handle(Standard_DomainError)(const Handle(Standard_DomainError)& aHandle) : Handle(Standard_Failure)(aHandle) 
     {
     }

    Handle(Standard_DomainError)(const Standard_DomainError* anItem) : Handle(Standard_Failure)((Standard_Failure *)anItem) 
     {
     }

    Handle(Standard_DomainError)& operator=(const Handle(Standard_DomainError)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(Standard_DomainError)& operator=(const Standard_DomainError* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    Standard_DomainError* operator->() const
     {
      return (Standard_DomainError *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(Standard_DomainError)();
 
   Standard_EXPORT static const Handle(Standard_DomainError) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif
