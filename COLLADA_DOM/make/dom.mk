include make/configVars.mk

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

# On PS3, we need to be told where to find pcre
ifeq ($(os),ps3)
includeSearchPaths += ../external-libs/pcre
libSearchPaths += ../external-libs/pcre/lib/$(os)
endif

libs += -lpcre -lpcrecpp

libName := libcollada$(colladaVersionNoDots)dom$(debugSuffix)
targets := $(addprefix $(outPath),$(libName).a)
# Don't build the shared lib on PS3, since PS3 doesn't support shared libs.
ifneq ($(os),ps3)
targets += $(addprefix $(outPath),$(libName).so)
endif

include make/rules.mk