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

#ifndef _BRepBuilderAPI_Command_HeaderFile
#define _BRepBuilderAPI_Command_HeaderFile

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class StdFail_NotDone;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//! Root class for all commands in BRepBuilderAPI. <br>
//! <br>
//!          Provides : <br>
//! <br>
//!          * Managements of the notDone flag. <br>
//! <br>
//!          * Catching of exceptions (not implemented). <br>
//! <br>
//!          * Logging (not implemented). <br>
class BRepBuilderAPI_Command  {

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


Standard_EXPORT virtual  void Delete() ;
Standard_EXPORT virtual ~BRepBuilderAPI_Command(){Delete() ; }


Standard_EXPORT virtual  Standard_Boolean IsDone() const;

//! Raises NotDone if done is false. <br>
Standard_EXPORT   void Check() const;





protected:

 // Methods PROTECTED
 // 

//! Set done to False. <br>
Standard_EXPORT BRepBuilderAPI_Command();

//! Set done to true. <br>
Standard_EXPORT   void Done() ;

//! Set done to false. <br>
Standard_EXPORT   void NotDone() ;


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


 // Fields PRIVATE
 //
Standard_Boolean myDone;


};





// other Inline functions and methods (like "C++: function call" methods)
//


#endif
