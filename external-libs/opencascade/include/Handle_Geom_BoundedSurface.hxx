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

#ifndef _Handle_Geom_BoundedSurface_HeaderFile
#define _Handle_Geom_BoundedSurface_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(Geom_Surface);
class Geom_BoundedSurface;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(Geom_BoundedSurface);

class Handle(Geom_BoundedSurface) : public Handle(Geom_Surface) {
  public:
    Handle(Geom_BoundedSurface)():Handle(Geom_Surface)() {} 
    Handle(Geom_BoundedSurface)(const Handle(Geom_BoundedSurface)& aHandle) : Handle(Geom_Surface)(aHandle) 
     {
     }

    Handle(Geom_BoundedSurface)(const Geom_BoundedSurface* anItem) : Handle(Geom_Surface)((Geom_Surface *)anItem) 
     {
     }

    Handle(Geom_BoundedSurface)& operator=(const Handle(Geom_BoundedSurface)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(Geom_BoundedSurface)& operator=(const Geom_BoundedSurface* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    Geom_BoundedSurface* operator->() const
     {
      return (Geom_BoundedSurface *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(Geom_BoundedSurface)();
 
   Standard_EXPORT static const Handle(Geom_BoundedSurface) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif