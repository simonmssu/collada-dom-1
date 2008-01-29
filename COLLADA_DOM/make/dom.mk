include make/common.mk

src := $(wildcard src/dae/*.cpp)

src += src/modules/stdErrPlugin/stdErrPlugin.cpp \
       src/modules/STLDatabase/daeSTLDatabase.cpp \
       src/modules/LIBXMLPlugin/daeLIBXMLPlugin.cpp \

src += $(wildcard src/$(colladaVersion)/dom/*.cpp)

includeSearchPaths := include include/$(colladaVersion)

ifneq ($(os),ps3)
# We're building a shared lib, so make sure to generate position independent code
ccFlags += -fPIC
endif

ifneq ($(findstring libxml,$(xmlparsers)),)
ccFlags += -DDOM_INCLUDE_LIBXML
includeSearchPaths += /usr/include/libxml2
libs += -lxml2
endif

ifneq ($(findstring tinyxml,$(xmlparsers)),)
ccFlags += -DDOM_INCLUDE_TINYXML
includeSearchPaths += ../external-libs/tinyxml/
libs += ../external-libs/tinyxml/lib/$(os)/libtinyxml.a
endif

# On Mac and PS3 we need to be told where to find pcre
ifneq ($(os),linux)
includeSearchPaths += ../external-libs/pcre
libSearchPaths += ../external-libs/pcre/lib/$(os)
endif

libs += -lpcre -lpcrecpp

libName := libcollada$(colladaVersionNoDots)dom$(debugSuffix)

targets :=
ifeq ($(os),linux)
# On Linux we build a static lib and a shared lib
targets += $(addprefix $(outPath),$(libName).a)
targets += $(addprefix $(outPath),$(libName).so)
else ifeq ($(os),mac)
# On Mac we build a dylib
targets += $(addprefix $(outPath),$(libName).dylib)
else ifeq ($(os),ps3)
# On PS3 we build a static lib, since PS3 doesn't support shared libs
targets += $(addprefix $(outPath),$(libName).a)
endif

include make/rules.mk