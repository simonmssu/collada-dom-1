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

LIB_PREFIX      := libcollada$(colladaVersionNoDots)
LIB_SUFFIX      := .a
LIB_DYN_SUFFIX  = .so
EXE_SUFFIX		:= 
OBJ_SUFFIX      := .o

ifdef ps3
CC  = ppu-lv2-gcc
CXX = ppu-lv2-g++
LD  = ppu-lv2-g++
AR  = ppu-lv2-ar rcs
EXE_SUFFIX := .elf
else
CC  = gcc
CXX = g++
LD  = g++
AR  = ar rcs
endif

LCOUT = 
EXEOUT = -o 
CCOUT = -o
LCQUIET = 
CCQUIET = 
CCOPT = -fPIC
CCINC = -I
LDOUT = -o
LDOPT = -shared

# If you're trying to figure out what this -MM thing is for, see this: 
#   http://www.cs.berkeley.edu/~smcpeak/autodepend/autodepend.html
PRINT_DEPENDENCIES_OPTION := -MM

DEBUG_OPTION := -g
PROFILE_OPTION := -pg

RELEASE_CCOPT = -O2 -D"NDEBUG"
DEBUG_CCOPT = -g -D"_DEBUG" -Wall
LIB_CCOPT =

EXE_DBG_LCOPT = -g
EXE_REL_LCOPT = 

RM  = rm 

USE_SHELL=1