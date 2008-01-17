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

# file: Set this to the name of a source file (eg 'dae.cpp') to build just that file
file :=

# If you want to change the default values of the above params, you can either modify them
# directly by changing the text above or put the variables assignments in make/customSettings.mk
-include make/customSettings.mk

# Initialize the build variables
define setBuildVar
$(1)s := $(sort $(subst all,$(2),$($(1))))
ifneq ($$(filter-out $(2),$$($(1)s)),)
$$(error Invalid setting: $(1)=$($(1)))
endif
endef

$(eval $(call setBuildVar,project,dom domTest))
$(eval $(call setBuildVar,platform,linux ps3))
$(eval $(call setBuildVar,colladaVersion,1.4))
$(eval $(call setBuildVar,conf,debug release))
$(eval $(call setBuildVar,parser,libxml tinyxml))

quiet := @
comma := ,
soMajorVersion := 2
soMinorVersion := 0

# We don't want make to automatically delete our intermediate (eg .o) files
.SECONDARY:

# Have make automatically delete a target if there's an error in one of the rule commands
.DELETE_ON_ERROR:

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

buildObj := $(filter %$(file:.cpp=.o),$(filter %.o,$(allOutputFiles)))

.DEFAULT_GOAL := all
.PHONY: all
ifeq ($(file),)
# Do a normal build of all targets
all: $(allTargets)
else ifneq ($(buildObj),)
# Just build the source files the user requested
all: $(buildObj)
else
$(error Invalid source file - $(file))
endif

allOutputPaths := $(sort $(dir $(allOutputFiles)))
$(allOutputPaths):
	$(quiet)if [ ! -d $@ ] ; then mkdir -p $@; fi;


##############################################
# clean
#
.PHONY: clean
clean:
	@echo Removing build files.
# Delete all the output files
	$(quiet)rm -f $(allOutputFiles)
# Delete each empty output folder
	$(quiet)for path in $(allOutputPaths); do \
		if [ -d $$path ] && [ `find $$path -type f | wc -l` -eq 0 ]; then rm -r $$path ; fi \
	done;
# Delete the build folder if it's empty
	$(quiet)if [ -d build ] && [ `find build -type f | wc -l` -eq 0 ] ; then rm -r build ; fi


##############################################
# test target for running the automated tests.
#
# Note: I originally had a separate target for each test, one reason being so that each
# test suite could be run in parallel. However when running in parallel I'd get weird errors where
# some of the tests would fail and some would succeed, with error messages like this:
#   I/O error : No such file or directory
#   I/O error : No such file or directory
#   error : xmlNewTextWriterFilename : out of memory!
# To work around this, I changed to using a single target with a shell loop to run each test program.
# This way the tests are forced to run serially.
domTestExes := $(filter %domTest,$(allTargets))
.PHONY: test
test: $(domTestExes)
	@for testExe in $(domTestExes); do \
		echo $$testExe -all; \
		$$testExe -all; \
	done


##############################################
# install/uninstall
#
prefix := /usr/local
-include make/installPrefix.mk

.PHONY: uninstall
ifneq ($(installPrefix),)
uninstall:
	$(quiet)rm -rf $(installPrefix)/include/collada
	$(quiet)rm -f  $(installPrefix)/lib/libcollada*dom*
else ifneq ($(findstring uninstall,$(MAKECMDGOALS)),)
$(error Can't uninstall because we don't know what path we installed to (missing make/installPrefix.mk file)).
else
uninstall:
endif

.PHONY: install
install: uninstall
# Write the install prefix to the file make/installPrefix.mk so we can retrieve it for uninstalling.
# A better way to do this would be to have a configure script.
	$(quiet)echo 'installPrefix := $(prefix)' > make/installPrefix.mk
# Install headers
	$(quiet)cp -r include $(prefix)/include/collada
# Install linux-1.4 libs
	$(quiet)cp build/linux-1.4/libcollada*dom* $(prefix)/lib
# Install linux-1.4-d libs
	$(quiet)cp build/linux-1.4-d/libcollada*dom* $(prefix)/lib
