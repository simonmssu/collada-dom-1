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

obj := $(addprefix $(objPath),$(src:.cpp=.o))
dependencyFiles := $(obj:.o=.d)
outputFiles := $(obj) $(dependencyFiles) $(targets)
outputFiles += $(foreach so,$(filter %.so,$(targets)),$(so).$(soMajorVersion) $(so).$(soMajorVersion).$(soMinorVersion))

# Parse the targets, which can contain a static lib, a shared lib, and an exe
staticLib := $(filter %.a,$(targets))
sharedLib := $(filter %.so,$(targets))
# Anything other than a .a or .so is considered an exe
exe := $(filter-out %.a,$(filter-out %.so,$(targets)))

ifneq ($(obj),)
# Pull in dependency info for *existing* .o files
-include $(dependencyFiles)

# Make has weird evaluation semantics, so we have to be careful to capture the state of
# any values we use in rule commands. This is the reason for all the target-specific variable
# values.
$(obj): cc := $(cc)
$(obj): ccFlags := $(ccFlags)
$(obj): includeSearchPaths := $(addprefix -I,$(includeSearchPaths))

# We're going to automatically generate make rules for our header dependencies.
# See this for more info: http://www.cs.berkeley.edu/~smcpeak/autodepend/autodepend.html
$(objPath)%.o: %.cpp
	@echo Compiling $< to $@
	$(quiet)$(cc) -c $< $(ccFlags) $(includeSearchPaths) -o $@
	@$(cc) -MM $< $(ccFlags) $(includeSearchPaths) > $(@:.o=.d)
	@mv -f $(@:.o=.d) $(@:.o=.d.tmp)
	@sed -e 's|.*:|$@:|' < $(@:.o=.d.tmp) > $(@:.o=.d)
	@sed -e 's/.*://' -e 's/\\$$//' < $(@:.o=.d.tmp) | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(@:.o=.d)
	@rm -f $(@:.o=.d.tmp)
endif

# Rule for static libs
ifneq ($(staticLib),)
$(staticLib): ar := $(ar)
$(staticLib): $(obj)
	@echo Creating $@
	$(quiet)$(ar) $@ $^
endif

# Rules for shared libs
ifneq ($(sharedLib),)
$(sharedLib).$(soMajorVersion).$(soMinorVersion): cc := $(cc)
$(sharedLib).$(soMajorVersion).$(soMinorVersion): ccFlags := $(ccFlags)
$(sharedLib).$(soMajorVersion).$(soMinorVersion): libs := $(libs)
$(sharedLib).$(soMajorVersion).$(soMinorVersion): libSearchPaths := $(addprefix -L,$(libSearchPaths))
$(sharedLib).$(soMajorVersion).$(soMinorVersion): $(dependentLibs) $(obj)
	@echo Linking $@
	$(quiet)$(cc) $(ccFlags) -shared -o $@ $^ $(libSearchPaths) $(libs)

$(sharedLib).$(soMajorVersion): $(sharedLib).$(soMajorVersion).$(soMinorVersion)
	$(quiet)cd $(dir $@)  &&  ln -s $(notdir $^) $(notdir $@)

$(sharedLib): $(sharedLib).$(soMajorVersion)
	$(quiet)cd $(dir $@)  &&  ln -s $(notdir $^) $(notdir $@)
endif

# Rules for exes
ifneq ($(exe),)
$(exe): cc := $(cc)
$(exe): ccFlags := $(ccFlags)
$(exe): obj := $(obj)
$(exe): libs := $(libs)
$(exe): libSearchPaths := $(addprefix -L,$(libSearchPaths))
$(exe): sharedLibSearchPathCommand := $(addprefix -Wl$(comma)-rpath$(comma),$(sharedLibSearchPaths))
$(exe): postCreateExeCommand := $(postCreateExeCommand)
$(exe): $(dependentLibs) $(obj)
	@echo Linking $@
	$(quiet)$(cc) $(ccFlags) -o $@ $(obj) $(libSearchPaths) $(libs) $(sharedLibSearchPathCommand)
	$(quiet)$(postCreateExeCommand)
endif
