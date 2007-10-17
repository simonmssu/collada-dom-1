#ifndef _Standard_SStream_HeaderFile
#define _Standard_SStream_HeaderFile

#if defined(_MSC_VER) && !defined(WNT)
  #error "Wrong compiler options has been detected. Add /DWNT option for proper compilation!!!!!"
#endif

#ifndef WNT

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_IOSTREAM
  #include <iostream>
  #include <sstream>
  using namespace std;
  #define USE_STL_STREAM
#elif defined (HAVE_IOSTREAM_H)
  #include <iostream.h>
  #include <strstream.h>
#else
  #error "check config.h file or compilation options: either HAVE_IOSTREAM or HAVE_IOSTREAM_H should be defined"
#endif /* HAVE_IOSTREAM */

#else  /* WNT */

// Macro USE_OLD_STREAMS may be defined externally to command 
// using old streams on Windows NT; otherwise new streams are used
#ifndef USE_OLD_STREAMS
  #include <iostream>
  #include <sstream>
  using namespace std;
  #define USE_STL_STREAM
#else /* USE_OLD_STREAMS */
  #include <iostream.h>
  #include <strstrea.h>
  #ifdef USE_STL_STREAM
  #undef USE_STL_STREAM
  #endif
#endif /* USE_OLD_STREAMS */

#endif /* WNT */

#include <Standard_Macro.hxx>
#ifdef USE_STL_STREAM
  #define GetSString(SStream) (char*)SStream.rdbuf()->str().c_str()
#else
  #define GetSString(SStream) (char*)SStream.rdbuf()->str()
#endif

class Handle_Standard_Type;

__Standard_API Handle_Standard_Type& Standard_SStream_Type_();
#ifdef USE_STL_STREAM
class Standard_SStream : public stringstream {
#else
class Standard_SStream : public strstream {
#endif
  public:
    Standard_EXPORT Standard_SStream();
    Standard_EXPORT Standard_SStream(ostream& );
    Standard_EXPORT ~Standard_SStream();
};

#endif
