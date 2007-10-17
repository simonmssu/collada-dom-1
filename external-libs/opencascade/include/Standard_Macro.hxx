#ifndef _Standard_Macro_HeaderFile
# define _Standard_Macro_HeaderFile

# define	  Handle(ClassName)  Handle_##ClassName
# define	  Oid(ClassName)     Oid_##ClassName

# define   STANDARD_TYPE(aType)   aType##_Type_()

# if defined(WNT) && !defined(HAVE_NO_DLL)

#  ifndef Standard_EXPORT
#   define Standard_EXPORT __declspec( dllexport )
// For global variables :
#   define Standard_EXPORTEXTERN __declspec( dllexport ) extern
#   define Standard_EXPORTEXTERNC extern "C" __declspec( dllexport )
#  endif  /* Standard_EXPORT */

#  ifndef Standard_IMPORT
#   define Standard_IMPORT __declspec( dllimport ) extern
#   define Standard_IMPORTC extern "C" __declspec( dllimport )
#  endif  /* Standard_IMPORT */

# else  /* WNT */

#  ifndef Standard_EXPORT
#   define Standard_EXPORT
// For global variables :
#   define Standard_EXPORTEXTERN extern
#   define Standard_EXPORTEXTERNC extern "C"
#  endif  /* Standard_EXPORT */

#  ifndef Standard_IMPORT
#   define Standard_IMPORT extern
#   define Standard_IMPORTC extern "C"
#  endif  /* Standard_IMPORT */

# endif  /* WNT */

# ifndef __Standard_API
//#  ifdef WNT
#   if !defined(WNT) || defined(__Standard_DLL) || defined(__FSD_DLL) || defined(__MMgt_DLL) || defined(__OSD_DLL) || defined(__Plugin_DLL) || defined(__Quantity_DLL) || defined(__Resource_DLL) || defined(__SortTools_DLL) || defined(__StdFail_DLL) || defined(__Storage_DLL) || defined(__TColStd_DLL) || defined(__TCollection_DLL) || defined(__TShort_DLL) || defined(__Units_DLL) || defined(__UnitsAPI_DLL) || defined(__Dico_DLL)
#    define __Standard_API Standard_EXPORT
#    define __Standard_APIEXTERN Standard_EXPORTEXTERN
#   else
#    define __Standard_API Standard_IMPORT
#    define __Standard_APIEXTERN Standard_IMPORT
#   endif  // __Standard_DLL
//#  else
//#   define __Standard_API
//#  endif  // WNT
# endif  // __Standard_API

// Define _OCC64 variable (unless already defined) if platform is known to be 64-bit
#ifndef _OCC64
#if defined (__alpha) || defined(DECOSF1) || defined(_WIN64)
#define _OCC64 1
#endif
#endif

#endif  
