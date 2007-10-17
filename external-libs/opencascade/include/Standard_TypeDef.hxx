// File:      Standard_TypeDef.hxx
// Copyright: Open Cascade 2006

#ifndef _Standard_TypeDef_HeaderFile
#define _Standard_TypeDef_HeaderFile

#include <stddef.h>

typedef int Standard_Integer;
typedef double Standard_Real;
typedef unsigned int Standard_Boolean;
typedef float Standard_ShortReal;
typedef char  Standard_Character;
typedef short Standard_ExtCharacter;
typedef unsigned char  Standard_Byte;
typedef char* Standard_CString;
typedef void* Standard_Address;
typedef short* Standard_ExtString;
typedef size_t Standard_Size;

#define Standard_False (Standard_Boolean) 0
#define Standard_True  (Standard_Boolean) 1

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

//#ifndef _Standard_Stream_HeaderFile
//#include <Standard_Stream.hxx>
//#endif

class Standard_Stream;
__Standard_API void ShallowDump(const Standard_Boolean, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_CString, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_Character, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_ExtCharacter, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_ExtString, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_Integer, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_Address, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_Real, Standard_Stream& );
__Standard_API void ShallowDump(const Standard_ShortReal, Standard_Stream& );

#endif

