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

#ifndef _Handle_ShapeFix_Shell_HeaderFile
#define _Handle_ShapeFix_Shell_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_ShapeFix_Root_HeaderFile
#include <Handle_ShapeFix_Root.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(ShapeFix_Root);
class ShapeFix_Shell;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(ShapeFix_Shell);

class Handle(ShapeFix_Shell) : public Handle(ShapeFix_Root) {
  public:
    Handle(ShapeFix_Shell)():Handle(ShapeFix_Root)() {} 
    Handle(ShapeFix_Shell)(const Handle(ShapeFix_Shell)& aHandle) : Handle(ShapeFix_Root)(aHandle) 
     {
     }

    Handle(ShapeFix_Shell)(const ShapeFix_Shell* anItem) : Handle(ShapeFix_Root)((ShapeFix_Root *)anItem) 
     {
     }

    Handle(ShapeFix_Shell)& operator=(const Handle(ShapeFix_Shell)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(ShapeFix_Shell)& operator=(const ShapeFix_Shell* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    ShapeFix_Shell* operator->() const
     {
      return (ShapeFix_Shell *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(ShapeFix_Shell)();
 
   Standard_EXPORT static const Handle(ShapeFix_Shell) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif
