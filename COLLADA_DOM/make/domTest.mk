include make/common.mk

src := test/domTest.cpp test/integrationExample.cpp
targets := $(outPath)domTest$(exeSuffix)

# DOM defs
ifneq ($(os),mac)
libSuffix := $(if $(findstring ps3,$(os)),.a,.so)
domName := $(outPath)libcollada$(colladaVersionNoDots)dom$(debugSuffix)$(libSuffix)
libOpts += $(domName)
ifeq ($(os),linux)
sharedLibSearchPaths += $(abspath $(outPath))
endif
else ifeq ($(os),mac)
domName := $(outPath)Collada$(colladaVersionNoDots)Dom$(debugSuffix).framework
# On Mac we use the framework for linking
libOpts += -F$(dir $(domName)) -framework $(notdir $(basename $(domName)))
endif
includeOpts += -Iinclude -Iinclude/$(colladaVersion)
dependentLibs += $(domName)

# PCRE defs
ifeq ($(os),ps3)
pcreLibPath := ../external-libs/pcre/lib/$(os)/
libOpts += -L$(pcreLibPath) -lpcrecpp -lpcre
endif

# TinyXml defs
ifneq ($(findstring tinyxml,$(xmlparsers)),)
# Notify domTest.cpp if we're supposed to do TinyXml tests
ccFlags += -DTINYXML
ifeq ($(os),ps3)
libOpts += ../external-libs/tinyxml/lib/$(os)/libtinyxml.a
endif
endif

# Boost defs
ifneq ($(os),linux)
includeOpts += -I../external-libs/boost
libOpts += -L../external-libs/boost/lib/$(os)
endif
ifeq ($(os),ps3)
# PS3 doesn't support C++ locales, so tell boost not to use them
ccFlags += -DBOOST_NO_STD_LOCALE
endif
libOpts += -lboost_filesystem

ifeq ($(os),ps3)
# On PS3 we need to make a .self from the .elf
postCreateExeCommand := make_fself $(targets) $(targets:.elf=.self)
endif

include make/rules.mk