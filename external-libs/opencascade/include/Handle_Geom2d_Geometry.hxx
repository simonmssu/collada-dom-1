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

#ifndef _Handle_Geom2d_Geometry_HeaderFile
#define _Handle_Geom2d_Geometry_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_MMgt_TShared_HeaderFile
#include <Handle_MMgt_TShared.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(MMgt_TShared);
class Geom2d_Geometry;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(Geom2d_Geometry);

class Handle(Geom2d_Geometry) : public Handle(MMgt_TShared) {
  public:
    Handle(Geom2d_Geometry)():Handle(MMgt_TShared)() {} 
    Handle(Geom2d_Geometry)(const Handle(Geom2d_Geometry)& aHandle) : Handle(MMgt_TShared)(aHandle) 
     {
     }

    Handle(Geom2d_Geometry)(const Geom2d_Geometry* anItem) : Handle(MMgt_TShared)((MMgt_TShared *)anItem) 
     {
     }

    Handle(Geom2d_Geometry)& operator=(const Handle(Geom2d_Geometry)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(Geom2d_Geometry)& operator=(const Geom2d_Geometry* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    Geom2d_Geometry* operator->() const
     {
      return (Geom2d_Geometry *)ControlAccess();
     }

//   Standard_EXPORT ~Handle(Geom2d_Geometry)();
 
   Standard_EXPORT static const Handle(Geom2d_Geometry) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif
