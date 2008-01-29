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

obj := $(addprefix $(objPath),$(notdir $(src:.cpp=.o)))
dependencyFiles := $(obj:.o=.d)
outputFiles := $(obj) $(dependencyFiles) $(targets)
outputFiles += $(foreach so,$(filter %.so,$(targets)),$(so).$(soMajorVersion) $(so).$(soMajorVersion).$(soMinorVersion))

# Parse the targets, which can contain a static lib, a shared lib, and an exe
staticLib := $(filter %.a,$(targets))
sharedLib := $(filter %.so,$(targets))
dylib := $(filter %.dylib,$(targets))
# Anything other than a .a, .so, or .dylib is considered an exe
exe := $(filter-out $(staticLib) $(sharedLib) $(dylib),$(targets))

# Add -L to the lib search paths
libSearchPaths := $(addprefix -L,$(libSearchPaths))

ifneq ($(obj),)
# Pull in dependency info for *existing* .o files
-include $(dependencyFiles)

# Make has weird evaluation semantics, so we have to be careful to capture the state of
# any values we use in rule commands. This is the reason for all the target-specific variables.
$(obj): cc := $(cc)
$(obj): ccFlags := $(ccFlags)
$(obj): includeSearchPaths := $(addprefix -I,$(includeSearchPaths))

# Call createObjRule with a source file path
define createObjRule
srcPath := $(1)

# Pick off the matching obj files
objFiles := $$(addprefix $$(objPath),$$(notdir $$(filter $$(srcPath)%,$$(src:.cpp=.o))))

# We're going to automatically generate make rules for our header dependencies.
# See this for more info: http://www.cs.berkeley.edu/~smcpeak/autodepend/autodepend.html
$$(objFiles): $$(objPath)%.o: $$(srcPath)%.cpp | $$(sort $$(dir $$(objFiles)))
	@echo Compiling $$< to $$@
	$$(quiet)$$(cc) -c $$< $$(ccFlags) $$(includeSearchPaths) -o $$@
	@$$(cc) -MM $$< $$(ccFlags) $$(includeSearchPaths) > $$(@:.o=.d)
	@mv -f $$(@:.o=.d) $$(@:.o=.d.tmp)
	@sed -e 's|.*:|$$@:|' < $$(@:.o=.d.tmp) > $$(@:.o=.d)
	@sed -e 's/.*://' -e 's/\\$$$$//' < $$(@:.o=.d.tmp) | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$$$/:/' >> $$(@:.o=.d)
	@rm -f $$(@:.o=.d.tmp)
endef

srcPaths := $(sort $(dir $(src)))
$(foreach path,$(srcPaths),$(eval $(call createObjRule,$(path))))
endif

# Rule for static libs
ifneq ($(staticLib),)
$(staticLib): ar := $(ar)
$(staticLib): $(obj) | $(dir $(staticLib))
	@echo Creating $@
	$(quiet)$(ar) $@ $^
endif

# Rules for shared libs
ifneq ($(sharedLib),)
sharedLibMajor := $(sharedLib).$(soMajorVersion)
sharedLibMajorMinor := $(sharedLib).$(soMajorVersion).$(soMinorVersion)
$(sharedLibMajorMinor): cc := $(cc)
$(sharedLibMajorMinor): ccFlags := $(ccFlags)
$(sharedLibMajorMinor): libs := $(libs)
$(sharedLibMajorMinor): libSearchPaths := $(libSearchPaths)
$(sharedLibMajorMinor): $(dependentLibs) $(obj) | $(dir $(sharedLibMajorMinor))
	@echo Linking $@
	$(quiet)$(cc) $(ccFlags) -shared -o $@ $^ $(libSearchPaths) $(libs)

$(sharedLibMajor): $(sharedLibMajorMinor) | $(dir $(sharedLibMajor))
	$(quiet)cd $(dir $@)  &&  ln -sf $(notdir $^) $(notdir $@)

$(sharedLib): $(sharedLibMajor) | $(dir $(sharedLib))
	$(quiet)cd $(dir $@)  &&  ln -sf $(notdir $^) $(notdir $@)
endif

# Rule for Mac-style dynamic libs
ifneq ($(dylib),)
$(dylib): cc := $(cc)
$(dylib): ccFlags := $(ccFlags)
$(dylib): libs := $(libs)
$(dylib): libSearchPaths := $(libSearchPaths)
$(dylib): $(dependentLibs) $(obj) | $(dir $(dylib))
	@echo Linking $@
	$(quiet)$(cc) $(ccFlags) -dynamiclib -o $@ $^ $(libSearchPaths) $(libs)
endif

# Rules for exes
ifneq ($(exe),)
$(exe): cc := $(cc)
$(exe): ccFlags := $(ccFlags)
$(exe): obj := $(obj)
$(exe): libs := $(libs)
$(exe): libSearchPaths := $(libSearchPaths)
$(exe): sharedLibSearchPathCommand := $(addprefix -Wl$(comma)-rpath$(comma),$(sharedLibSearchPaths))
$(exe): postCreateExeCommand := $(postCreateExeCommand)
$(exe): $(dependentLibs) $(obj) | $(dir $(exe))
	@echo Linking $@
	$(quiet)$(cc) $(ccFlags) -o $@ $(obj) $(libSearchPaths) $(libs) $(sharedLibSearchPathCommand)
	$(quiet)$(postCreateExeCommand)
endif
