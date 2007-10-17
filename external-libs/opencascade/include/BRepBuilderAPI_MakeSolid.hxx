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

#ifndef _BRepBuilderAPI_MakeSolid_HeaderFile
#define _BRepBuilderAPI_MakeSolid_HeaderFile

#ifndef _BRepLib_MakeSolid_HeaderFile
#include <BRepLib_MakeSolid.hxx>
#endif
#ifndef _BRepBuilderAPI_MakeShape_HeaderFile
#include <BRepBuilderAPI_MakeShape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class StdFail_NotDone;
class TopoDS_CompSolid;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Shape;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//! Describes functions to build a solid from shells. <br>
//! A solid is made of one shell, or a series of shells, which <br>
//! do not intersect each other. One of these shells <br>
//! constitutes the outside skin of the solid. It may be closed <br>
//! (a finite solid) or open (an infinite solid). Other shells <br>
//! form hollows (cavities) in these previous ones. Each <br>
//! must bound a closed volume. <br>
//! A MakeSolid object provides a framework for: <br>
//! -   defining and implementing the construction of a solid, and <br>
//! -   consulting the result. <br>
class BRepBuilderAPI_MakeSolid  : public BRepBuilderAPI_MakeShape {

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

//! Initializes the construction of a solid. An empty solid is <br>
//! considered to cover the whole space. The Add function <br>
//! is used to define shells to bound it. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid();

//! Make a solid from a CompSolid. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_CompSolid& S);

//! Make a solid from a shell. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S);

//! Make a solid from two shells. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1,const TopoDS_Shell& S2);

//! Make a solid from three shells. <br>//! Constructs a solid <br>
//! -   covering the whole space, or <br>
//! -   from shell S, or <br>
//! -   from two shells S1 and S2, or <br>
//! -   from three shells S1, S2 and S3, or <br>
//! Warning <br>
//! No check is done to verify the conditions of coherence <br>
//! of the resulting solid. In particular, S1, S2 (and S3) must <br>
//! not intersect each other. <br>
//! Besides, after all shells have been added using the Add <br>
//! function, one of these shells should constitute the outside <br>
//! skin of the solid; it may be closed (a finite solid) or open <br>
//! (an infinite solid). Other shells form hollows (cavities) in <br>
//! these previous ones. Each must bound a closed volume. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1,const TopoDS_Shell& S2,const TopoDS_Shell& S3);

//! Make a solid from a solid. Usefull for adding later. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So);

//! Add a shell to a solid. <br>
//! Constructs a solid: <br>
//! -   from the solid So, to which shells can be added, or <br>
//! -   by adding the shell S to the solid So. <br>
//!   Warning <br>
//! No check is done to verify the conditions of coherence <br>
//! of the resulting solid. In particular S must not intersect the solid S0. <br>
//! Besides, after all shells have been added using the Add <br>
//! function, one of these shells should constitute the outside <br>
//! skin of the solid. It may be closed (a finite solid) or open <br>
//! (an infinite solid). Other shells form hollows (cavities) in <br>
//! the previous ones. Each must bound a closed volume. <br>
Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So,const TopoDS_Shell& S);

//! Adds the shell to the current solid. <br>
//!	Warning <br>
//! No check is done to verify the conditions of coherence <br>
//! of the resulting solid. In particular, S must not intersect <br>
//! other shells of the solid under construction. <br>
//! Besides, after all shells have been added, one of <br>
//! these shells should constitute the outside skin of the <br>
//! solid. It may be closed (a finite solid) or open (an <br>
//! infinite solid). Other shells form hollows (cavities) in <br>
//! these previous ones. Each must bound a closed volume. <br>
Standard_EXPORT   void Add(const TopoDS_Shell& S) ;

//! Returns true if the solid is built. <br>
//! For this class, a solid under construction is always valid. <br>
//! If no shell has been added, it could be a whole-space <br>
//! solid. However, no check was done to verify the <br>
//! conditions of coherence of the resulting solid. <br>
Standard_EXPORT virtual  Standard_Boolean IsDone() const;

//! Returns the new Solid. <br>
//! <br>
Standard_EXPORT  const TopoDS_Solid& Solid() const;
Standard_EXPORT operator TopoDS_Solid() const;


Standard_EXPORT virtual  Standard_Boolean IsDeleted(const TopoDS_Shape& S) ;





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
BRepLib_MakeSolid myMakeSolid;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
