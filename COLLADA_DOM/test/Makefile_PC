#!/usr/bin/make
# Copyright 2006 Sony Computer Entertainment Inc.
#
# Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
# file except in compliance with the License. You may obtain a copy of the License at:
# http://research.scea.com/scea_shared_source_license.html
#
# Unless required by applicable law or agreed to in writing, software distributed under the License 
# is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
# implied. See the License for the specific language governing permissions and limitations under the 
# License. 

ROOT_DIR   :=	..
EXECUTABLE := domTest
OUTPUT_DIR := $(ROOT_DIR)/bin
EXTERNAL_LIBS_DIR := $(ROOT_DIR)/../external-libs

# Basic definitions
include $(ROOT_DIR)/build/makedefs.txt

# These are used for different things. The names are stupid, I know.
LIB_DIR := $(ROOT_DIR)/lib/$(CONF_NAME)
LIB_PATH += $(ROOT_DIR)/lib/$(CONF_NAME)

ifeq ($(PLATFORM_NAME), ps3)
# PS3 doesn't support shared libraries, so link against the static libs
LIBRARIES += -lcolladadom$(DEBUG_SUFFIX) -lpcrecpp -lpcre -ltinyxml -lboost_filesystem

LIB_PATH += $(EXTERNAL_LIBS_DIR)/pcre/lib/$(PLATFORM_NAME)
LIB_PATH += $(EXTERNAL_LIBS_DIR)/tinyxml/lib/$(PLATFORM_NAME)
LIB_PATH += $(EXTERNAL_LIBS_DIR)/boost/lib/$(PLATFORM_NAME)

# Tell the makefile what libs we depend on, so that the exe gets rebuilt if any of these
# libs changes.
DEP_LIBS += $(LIB_DIR)/$(LIB_PREFIX)dom$(DEBUG_SUFFIX)$(LIB_SUFFIX)
DEP_LIBS += $(EXTERNAL_LIBS_DIR)/pcre/lib/$(PLATFORM_NAME)/libpcre.a
DEP_LIBS += $(EXTERNAL_LIBS_DIR)/pcre/lib/$(PLATFORM_NAME)/libpcrecpp.a
DEP_LIBS += $(EXTERNAL_LIBS_DIR)/tinyxml/lib/$(PLATFORM_NAME)/libtinyxml.a
DEP_LIBS += $(EXTERNAL_LIBS_DIR)/boost/lib/$(PLATFORM_NAME)/libboost_filesystem.a

INCLUDE_DIR += $(EXTERNAL_LIBS_DIR)/pcre
INCLUDE_DIR += $(EXTERNAL_LIBS_DIR)/tinyxml
INCLUDE_DIR += $(EXTERNAL_LIBS_DIR)/boost

# PS3 doesn't support C++ locales, so tell boost not to use them
CCOPT += -DBOOST_NO_STD_LOCALE

# On PS3 we need to make a .self from the .elf
POST_CREATE_EXE_COMMAND := make_fself $(TARGET) $(addsuffix .self, $(basename $(TARGET)))

else

# For the Linux build, we're going to link against the shared libs
LIBRARIES += -lcolladadom$(DEBUG_SUFFIX) -lboost_filesystem

# Embed the info about where to find the DOM shared libs directly in the executable
COMMA := ,
# For some reason the -rpath linker option needs to be given an absolute path
SHARED_LIB_PATH += $(abspath $(LIB_PATH))
SHARED_LIB_COMMAND := $(addprefix -Wl$(COMMA)-rpath$(COMMA), $(SHARED_LIB_PATH))

# Tell the makefile what libs we depend on, so that the exe gets rebuilt if any of these
# libs changes.
DEP_LIBS += $(LIB_PATH)/$(LIB_PREFIX)dom$(DEBUG_SUFFIX)$(LIB_DYN_SUFFIX)
endif

# files
SRC	:= domTest.cpp integrationExample.cpp

EXE_LCOPT	+= $(addprefix -L, $(LIB_PATH))

INCLUDE_DIR	+= $(ROOT_DIR)/include \
               $(ROOT_DIR)/include/dae \
               $(ROOT_DIR)/include/$(COLLADA_VERSION)

# Are we doing TinyXML tests?
ifeq ($(TINYXML), 1)
CCOPT += -D"TINYXML"
endif

include $(ROOT_DIR)/build/makerules.txt