#ifndef _Standard_Stream_HeaderFile
#define _Standard_Stream_HeaderFile

#if defined(_MSC_VER) && !defined(WNT)
#error "Wrong compiler options has been detected. Add /DWNT option for proper compilation!!!!!"
#endif

#ifndef WNT
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef HAVE_IOSTREAM
# include <iostream>
using namespace std;
#elif defined (HAVE_IOSTREAM_H)
#include <iostream.h>
#else
#error "check config.h file or compilation options: either HAVE_IOSTREAM or HAVE_IOSTREAM_H should be defined"
#endif

#ifdef HAVE_IOMANIP
# include <iomanip>
#elif defined (HAVE_IOMANIP_H)
#include <iomanip.h>
#endif

#ifdef HAVE_FSTREAM
# include <fstream>
#elif defined (HAVE_FSTREAM_H)
#include <fstream.h>
#endif
#endif

#ifdef WNT
// Macro USE_OLD_STREAMS may be defined externally to command 
// using old streams on Windows NT; otherwise new streams are used
#ifndef USE_OLD_STREAMS
  #include <iostream>
  #include <iomanip>
  #include <fstream>
  using namespace std;
#else
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
#endif /* USE_OLD_STREAMS */
#endif

#endif /* _Standard_Stream_HeaderFile */
