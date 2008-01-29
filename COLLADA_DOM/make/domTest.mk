include make/common.mk

src := test/domTest.cpp test/integrationExample.cpp
domName := collada$(colladaVersionNoDots)dom$(debugSuffix)
targets := $(outPath)domTest$(exeSuffix)

libSuffix := $(if $(findstring linux,$(os)),.so,.dylib)
libSuffix := $(if $(findstring ps3,$(os)),.a,$(libSuffix))

# Set include search paths
includeSearchPaths += include include/dae include/$(colladaVersion)
ifneq ($(os),linux)
includeSearchPaths += ../external-libs/pcre
includeSearchPaths += ../external-libs/boost
ifneq ($(findstring tinyxml,$(xmlparsers)),)
includeSearchPaths += ../external-libs/tinyxml
endif
endif

# Set lib search paths
libSearchPaths += $(outPath)
ifneq ($(os),linux)
libSearchPaths += ../external-libs/pcre/lib/$(os)
libSearchPaths += ../external-libs/boost/lib/$(os)
ifneq ($(findstring tinyxml,$(xmlparsers)),)
libSearchPaths += ../external-libs/tinyxml/lib/$(os)
endif
endif

# Set libs
libs += -l$(domName) -lboost_filesystem
ifeq ($(os),ps3)
libs += -lpcrecpp -lpcre
endif
ifneq ($(findstring tinyxml,$(xmlparsers)),)
libs += -ltinyxml
endif

# Set dependent libs, so the exe gets rebuilt if any libs change
dependentLibs += $(outPath)lib$(domName)$(libSuffix)
ifneq ($(os),linux)
dependentLibs += ../external-libs/pcre/lib/$(os)/libpcre.a
dependentLibs += ../external-libs/pcre/lib/$(os)/libpcrecpp.a
dependentLibs += ../external-libs/boost/lib/$(os)/libboost_filesystem.a
endif
ifneq ($(findstring tinyxml,$(xmlparsers)),)
dependentLibs += ../external-libs/tinyxml/lib/$(os)/libtinyxml.a
endif

ifeq ($(os),ps3)
# PS3 doesn't support C++ locales, so tell boost not to use them
ccFlags += -DBOOST_NO_STD_LOCALE
# On PS3 we need to make a .self from the .elf
postCreateExeCommand := make_fself $(targets) $(targets:.elf=.self)
endif

ifeq ($(os),linux)
sharedLibSearchPaths += $(abspath $(outPath))
else ifeq ($(os),mac)
postCreateExeCommand := install_name_tool -change $(outPath)lib$(domName).dylib \
$(abspath $(outPath))/lib$(domName).dylib $(targets)
endif

# Are we doing TinyXML tests?
# Notify domTest.cpp if we're supposed to do TinyXml tests
ifneq ($(findstring tinyxml,$(xmlparsers)),)
ccFlags += -DTINYXML
endif

include make/rules.mk