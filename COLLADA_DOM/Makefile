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

# project: 'dom', 'domTest', or 'all'
project := all

# platform: 'linux', 'ps3', or 'all'
platform := linux

# Build configuration: 'release', 'debug', or 'all'
conf := release

# Collada version: No other versions supported for now
colladaVersion := 1.4

# parser: 'libxml', 'tinyxml', or 'all'.
parser := libxml

# Set projects variable based on project setting
projects := $(subst all,dom domTest,$(project))
ifneq ($(filter-out dom domTest,$(projects)),)
$(error Invalid setting: project=$(project))
endif

# Set platforms variable based on platform setting
platforms := $(subst all,linux ps3,$(platform))
ifneq ($(filter-out linux ps3,$(platforms)),)
$(error Invalid setting: platform=$(platform))
endif

# Set the colladaVersions variable based on colladaVersion setting
colladaVersions := $(subst all,1.4,$(colladaVersion))
ifneq ($(filter-out 1.4,$(colladaVersions)),)
$(error Invalid setting: colladaVersions=$(colladaVersion))
endif

# Set confs variable based on conf setting
confs := $(subst all,debug release,$(conf))
ifneq ($(filter-out debug release,$(confs)),)
$(error Invalid setting: conf=$(conf))
endif

# Set parsers variable based on parser setting
parsers := $(subst all,libxml tinyxml,$(parser))
ifneq ($(filter-out libxml tinyxml,$(parsers)),)
$(error Invalid setting: parser=$(parser))
endif

quiet := @
comma := ,
soMajorVersion := 2
soMinorVersion := 0

rm := rm -f

# We don't want make to automatically delete our intermediate (eg .o) files
.SECONDARY:

allOutputFiles :=
allTargets :=

define includeConfig
override project := $(1)
override platform := $(2)
override colladaVersion := $(3)
override conf := $(4)
include make/$(1).mk
allOutputFiles += $$(outputFiles)
allTargets += $$(targets)
endef

$(foreach _project,$(projects),\
$(foreach _platform,$(platforms),\
$(foreach _colladaVersion,$(colladaVersions),\
$(foreach _conf,$(confs),\
$(eval $(call includeConfig,$(_project),$(_platform),$(_colladaVersion),$(_conf)))))))

.DEFAULT_GOAL := all
all: createOutputPaths $(allTargets)
	@echo done

allOutputPaths := $(sort $(dir $(allOutputFiles)))
createOutputPaths:
	@for d in $(allOutputPaths); do \
		if [ ! -d $dd ] ; then \
			mkdir -p $$d ; \
		fi; \
	done;

clean:
	$(quiet)rm -f $(allOutputFiles)
