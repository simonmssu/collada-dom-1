// File generated by CPPExt (Exception)
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

#ifndef _Standard_OutOfRange_HeaderFile
#define _Standard_OutOfRange_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_Standard_OutOfRange_HeaderFile
#include <Handle_Standard_OutOfRange.hxx>
#endif

#ifndef _Standard_SStream_HeaderFile
#include <Standard_SStream.hxx>
#endif


#ifndef _Standard_RangeError_HeaderFile
#include <Standard_RangeError.hxx>
#endif


#if !defined No_Exception && !defined No_Standard_OutOfRange
#define Standard_OutOfRange_Raise_if(CONDITION,MESSAGE) \
  if (CONDITION) Standard_OutOfRange::Raise(MESSAGE);
#else
#define Standard_OutOfRange_Raise_if(CONDITION,MESSAGE)
#endif

class Standard_OutOfRange : public Standard_RangeError {

#ifndef NO_CXX_EXCEPTION
 Standard_EXPORT virtual void Throw() const;
#endif
public:
 Standard_EXPORT Standard_OutOfRange():Standard_RangeError(){}
 Standard_EXPORT Standard_OutOfRange(const Standard_CString AString):Standard_RangeError(AString){}
 Standard_EXPORT static void Raise(const Standard_CString aMessage = "");
 Standard_EXPORT static void Raise(Standard_SStream& aReason);
 Standard_EXPORT static Handle(Standard_OutOfRange) NewInstance(const Standard_CString aMessage); 

// Standard_EXPORT ~Standard_OutOfRange();

 // Type methods
 //
 Standard_EXPORT friend Handle_Standard_Type& Standard_OutOfRange_Type_();
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;			
// Standard_EXPORT Standard_Boolean             IsKind(const Handle(Standard_Type)&) const;
};

#endif
