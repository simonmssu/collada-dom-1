include make/configVars.mk

src := test/domTest.cpp test/integrationExample.cpp
domName := collada$(colladaVersionNoDots)dom$(debugSuffix)
targets := $(outPath)domTest$(exeSuffix)

ifeq ($(os),ps3)
# PS3 doesn't support shared libraries, so link against the static libs
libs += -l$(domName) -lpcrecpp -lpcre -ltinyxml -lboost_filesystem

libSearchPaths += ../external-libs/pcre/lib/$(os)
libSearchPaths += ../external-libs/tinyxml/lib/$(os)
libSearchPaths += ../external-libs/boost/lib/$(os)

# Tell the makefile what libs we depend on, so that the exe gets rebuilt if any of these
# libs changes.
dependentLibs += $(outPath)lib$(domName).a
dependentLibs += ../external-libs/pcre/lib/$(os)/libpcre.a
dependentLibs += ../external-libs/pcre/lib/$(os)/libpcrecpp.a
dependentLibs += ../external-libs/tinyxml/lib/$(os)/libtinyxml.a
dependentLibs += ../external-libs/boost/lib/$(os)/libboost_filesystem.a

includeSearchPaths += ../external-libs/pcre
includeSearchPaths += ../external-libs/tinyxml
includeSearchPaths += ../external-libs/boost

# PS3 doesn't support C++ locales, so tell boost not to use them
ccFlags += -DBOOST_NO_STD_LOCALE

# On PS3 we need to make a .self from the .elf
postCreateExeCommand := make_fself $(targets) $(targets:.elf=.self)

else

# For the Linux build, we're going to link against the shared lib
libs += -l$(domName) -lboost_filesystem

# Tell the makefile what libs we depend on, so that the exe gets rebuilt if any of these
# libs changes.
dependentLibs += $(outPath)lib$(domName).so

sharedLibSearchPaths += $(abspath $(outPath))
endif

includeSearchPaths += include include/dae include/$(colladaVersion)
libSearchPaths += $(outPath)

# Are we doing TinyXML tests?
# Notify domTest.cpp if we're supposed to do TinyXml tests
ifneq ($(findstring tinyxml,$(xmlparsers)),)
ccFlags += -DTINYXML
endif

include make/rules.mk