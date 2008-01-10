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

#########################################################
# some more definitions

# PS3 doesn't support shared libraries
ifeq ($(PLATFORM_NAME), ps3)
TARGETS := $(TARGET)
else
TARGETS := $(TARGET) $(TARGET_DYN)
endif

OBJS  = $(addprefix $(INTERMEDIATE_DIR), $(notdir $(addsuffix $(OBJ_SUFFIX), $(basename $(SRC)))))
OBJS += $(addprefix $(INTERMEDIATE_DIR), $(notdir $(addsuffix .res, $(basename $(RES)))))
DEPENDENCY_FILES := $(addsuffix .d, $(basename $(OBJS)))
CLEAN_LIST  = $(OBJS) $(DEPENDENCY_FILES) $(TARGETS)

# Tell make where to find our source files
SRC_DIRS = $(sort $(dir $(SRC))) # Generate a unique list of the paths containing our source files
vpath %.cpp $(subst $(space),:,$(SRC_DIRS)) # Pass vpath a colon-separated list of paths

# Tell make where to find our resource files
RES_DIRS = $(sort $(dir $(RES)))
vpath %.rc $(subst $(space),:,$(RES_DIRS))

#########################################################
# all rule

.PHONY:	all clean createdirs check_build done

all: check_build createdirs $(TARGETS) done
install: check_install uninstall_headers uninstall_libraries \
				 install_headers install_libraries done
uninstall: check_uninstall uninstall_headers uninstall_libraries done

# Pull in dependency info for *existing* .o files
ifneq ($(PRINT_DEPENDENCIES_OPTION), )
-include $(OBJS:.o=.d)
endif

#########################################################
# build install

install_headers:
	mkdir /usr/include/collada -p
	mkdir /usr/include/collada/dae -p
	cp include/dae/*.h /usr/include/collada/dae
	mkdir /usr/include/collada/dom  -p
	cp include/$(COLLADA_VERSION)/dom/*.h /usr/include/collada/dom 
	mkdir /usr/include/collada/modules  -p
	cp include/modules/*.h /usr/include/collada/modules
	cp include/dae.h /usr/include/collada
	cp include/dom.h /usr/include/collada

uninstall_headers:
	rm -r -f /usr/include/collada

install_libraries:
	cp lib/$(CONF_NAME)/*.a /usr/lib
	cp lib/$(CONF_NAME)/*.so* /usr/lib

uninstall_libraries:
# We don't want to just remove all /usr/lib/libcollada*.a files. Other libraries
# such as bullet build with a "libcollada" prefix but aren't part of the COLLADA
# DOM. We don't want to remove those files if they happen to be in /usr/lib.
#	rm -f /usr/lib/libcollada*.a
	rm -f /usr/lib/libcollada_dae.a
	rm -f /usr/lib/libcollada_dom.a
	rm -f /usr/lib/libcollada_dae_shared.so*
	rm -f /usr/lib/libcollada_dom_shared.so*


#########################################################
# build rules
INCLUDES_WITH_PREFIX := $(addprefix $(CCINC) ,$(INCLUDE_DIR))

ifneq ($(PRINT_DEPENDENCIES_OPTION), )
# Sweet, our compiler can automatically generate make rules for our dependencies.
# See this for more info: http://www.cs.berkeley.edu/~smcpeak/autodepend/autodepend.html
$(INTERMEDIATE_DIR)%$(OBJ_SUFFIX) : %.cpp
	$(QUIET)$(CXX) -c $< $(CCQUIET) $(CCOPT) $(CCOUT)$@ $(INCLUDES_WITH_PREFIX)
	@$(CXX) $(PRINT_DEPENDENCIES_OPTION) $< $(CCQUIET) $(CCOPT) $(INCLUDES_WITH_PREFIX) > $(basename $@).d
	@mv -f $(basename $@).d $(basename $@).d.tmp
	@sed -e 's|.*:|$@:|' < $(basename $@).d.tmp > $(basename $@).d
	@sed -e 's/.*://' -e 's/\\$$//' < $(basename $@).d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(basename $@).d
	@rm -f $(basename $@).d.tmp
else
$(INTERMEDIATE_DIR)%$(OBJ_SUFFIX) : %.cpp
	$(QUIET)$(CXX) -c $< $(CCQUIET) $(CCOPT) $(CCOUT)$@ $(INCLUDES_WITH_PREFIX)
endif

$(INTERMEDIATE_DIR)%.res : %.rc
	$(QUIET)rc /fo$@ $<

ifeq ($(suffix $(TARGET)), $(LIB_SUFFIX))
# We're building a static lib
$(TARGET): $(OBJS)
	@echo $@
	$(QUIET)$(AR) $(LCOUT) $@ $^
endif

ifneq ($(findstring $(LIB_DYN_SUFFIX_VERSION), $(TARGET_DYN)),)
# We're building a shared lib
$(TARGET_DYN): $(OBJS) $(DEP_LIBS)
	echo $@
	$(QUIET)$(LD) $(LCOPT) $(LDOUT) $@ $^ $(LIBRARIES)
	$(ROOT_DIR)/build/create_so_links $@
endif

ifeq ($(suffix $(TARGET)), $(EXE_SUFFIX))
# We're building an executable
$(TARGET): $(OBJS) $(DEP_LIBS)
	@echo $@
	$(QUIET)$(LD) $(LCOPT) $(LDOUT) $@ $(OBJS) $(LIBRARIES) $(SHARED_LIB_COMMAND)
	$(POST_CREATE_EXE_COMMAND)
endif

#########################################################
# clean rule
clean:
ifneq ($(strip $(CLEAN_LIST)),)
ifeq ($(USE_SHELL),)
#	@for %%d in ($(subst /,\,$(CLEAN_LIST))) do if exist "%%d" del /Q "%%d" 2> nul
else
	@echo cleaning $(notdir $(CLEAN_LIST))
	@rm -f $(CLEAN_LIST)
# Remove the .so links. It'd be better to have a list of the links we built, and delete
# only that list of files instead of deleting *.so*
	@rm -f $(OUTDIR)*.so*
endif
endif

#########################################################
#create directory rule
createdirs:
ifneq ($(TARGET),)
ifeq ($(USE_SHELL),)
				@for %%d in ($(CREATE_DIR)) do if not exist "%%d" mkdir "%%d"
else
				@for d in $(CREATE_DIR); do \
					if [ ! -d $dd ] ; then \
						mkdir -p $$d ; \
					fi; \
					done;
endif
endif

#########################################################
# check_build rule: can be used to perform some basic checks and tests
# when doing a build.
check_build:
	@echo building $(TARGETS) - $(CONF_NAME)
#	@echo TARGET = $(TARGET)
#	@echo EXECUTABLE = $(EXECUTABLE)
#	@echo LIBRARY = $(LIBRARY)
#	@echo DEBUG = $(DEBUG)
#	@echo SRC = $(SRC)
#	@echo OBJS = $(OBJS)

#########################################################
# check_install rule: can be used to perform some basic checks and tests
# when doing an install.
check_install:
	@echo Adding $(CONF_NAME) files to /usr/include and /usr/lib

#########################################################
# check_uninstall rule: can be used to perform some basic checks and tests
# when doing an uninstall.
check_uninstall:
	@echo Removing files from /usr/include and /usr/lib

#########################################################
# subdirectories

$(SUBDIRS):
	@$(MAKE) -r -R -C $@ $(MAKECMDGOALS)

done:
	@echo done
