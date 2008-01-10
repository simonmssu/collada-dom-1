#-*-makefile-*-
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
#
# 
#
# Common Makefile definitions
#
#

include $(ROOT_DIR)/build/params.mk

#########################################################
# DOM version
export DOM_MAJOR_VERSION=2
export DOM_MINOR_VERSION=0
export DOM_VERSION=$(DOM_MAJOR_VERSION).$(DOM_MINOR_VERSION)

#########################################################
# Debug suffix
ifdef debug
DEBUG_SUFFIX := -d
endif

#########################################################
# configuration - This is a unique string that identifies the build config. It's used
#                 to generate build output paths.
CONF_NAME := $(platform)_$(colladaVersion)
ifdef debug
CONF_NAME := $(CONF_NAME)_debug
endif

#########################################################
# target name
ifneq ($(EXECUTABLE),)
OUT_NAME            := $(EXECUTABLE)
else
OUT_NAME            := $(LIBRARY)
endif

#########################################################
# create paths
INTERMEDIATE_DIR = $(ROOT_DIR)/tmp/$(CONF_NAME)/$(OUT_NAME)/

#########################################################
# platform specific definitions
include $(ROOT_DIR)/build/linuxdefs.mk

#########################################################
# Linux .so defs
ifneq ($(DOM_VERSION),)
LIB_DYN_SUFFIX_MAJOR_VERSION := $(LIB_DYN_SUFFIX).$(DOM_MAJOR_VERSION)
LIB_DYN_SUFFIX_VERSION := $(LIB_DYN_SUFFIX).$(DOM_VERSION)
else
LIB_DYN_SUFFIX_VERSION := $(LIB_DYN_SUFFIX)
endif

#########################################################
# common settings
#QUIET           := @

ifdef release
CCOPT			+= $(RELEASE_CCOPT)
EXE_LCOPT       += $(EXE_REL_LCOPT)
LIB_CCOPT       += $(EXE_REL_LCOPT)
else
CCOPT			+= $(DEBUG_CCOPT)
EXE_LCOPT       += $(EXE_DBG_LCOPT)
LIB_CCOPT       += $(EXE_DBG_LCOPT)
endif

ifeq ($(PROFILE),1)
CCOPT += $(PROFILE_OPTION)
LCOPT += $(PROFILE_OPTION)
endif

TMPDIR			= $(OUTPUT_DIR)/$(CONF_NAME)
CREATE_DIR		+= $(INTERMEDIATE_DIR) $(TMPDIR)

OUTDIR			:= $(TMPDIR)/

#########################################################
#build type specific settings

ifneq ($(LIBRARY),)

# library build settings
TARGET     := $(OUTDIR)$(LIB_PREFIX)$(LIBRARY)$(DEBUG_SUFFIX)$(LIB_SUFFIX)
TARGET_DYN := $(OUTDIR)$(LIB_PREFIX)$(LIBRARY)$(DEBUG_SUFFIX)$(LIB_DYN_SUFFIX_VERSION)
LCOPT      += $(LDOPT) $(LIB_CCOPT)
else

ifneq ($(EXECUTABLE),)

# executable build settings
TARGET := $(OUTDIR)$(EXECUTABLE)$(EXE_SUFFIX)
LCOPT  += $(EXE_LCOPT)
endif
endif
