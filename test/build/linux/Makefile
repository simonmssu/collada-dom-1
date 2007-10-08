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

ROOT_DIR   :=	../../..
EXECUTABLE := domTest
OUTPUT_DIR := $(ROOT_DIR)/bin

# Basic definitions
include $(ROOT_DIR)/build/makedefs.txt

LIB_PATH := $(ROOT_DIR)/lib/$(CONF_NAME)
EXE_LCOPT	+= -L$(LIB_PATH)
LIBRARIES += -lcollada_dae_shared -lcollada_dom_shared

COMMA := ,
# For some reason the -rpath linker option needs to be given an absolute path
SHARED_LIB_PATH += $(abspath $(LIB_PATH))
SHARED_LIB_COMMAND := $(addprefix -Wl$(COMMA)-rpath$(COMMA), $(SHARED_LIB_PATH))

DEP_LIBS += $(LIB_PATH)/$(LIB_PREFIX)dae_shared$(LIB_DYN_SUFFIX)
DEP_LIBS += $(LIB_PATH)/$(LIB_PREFIX)dom_shared$(LIB_DYN_SUFFIX)

# files
SRC	:= ../../domTest.cpp

INCLUDE_DIR	+= $(ROOT_DIR)/include \
               $(ROOT_DIR)/include/dae \
               $(ROOT_DIR)/include/$(COLLADA_VERSION)

# Are we doing TinyXML tests?
ifeq ($(TINYXML), 1)
CCOPT += -D"TINYXML"
endif

include $(ROOT_DIR)/build/makerules.txt