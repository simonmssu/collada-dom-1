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

# target file(s)
ROOT_DIR :=	.

# definitions
include $(ROOT_DIR)/build/params.mk

.PHONY: all clean

all:
ifdef linux
ifdef debug
	@$(MAKE) -r -R -C $(ROOT_DIR)/src/dae platform=linux conf=debug colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
	@$(MAKE) -r -R -C $(ROOT_DIR)/test platform=linux conf=debug colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
endif
ifdef release
	@$(MAKE) -r -R -C $(ROOT_DIR)/src/dae platform=linux conf=release colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
	@$(MAKE) -r -R -C $(ROOT_DIR)/test platform=linux conf=release colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
endif
endif

ifdef ps3
ifdef debug
	@$(MAKE) -r -R -C $(ROOT_DIR)/src/dae platform=ps3 conf=debug colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
	@$(MAKE) -r -R -C $(ROOT_DIR)/test platform=ps3 conf=debug colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
endif
ifdef release
	@$(MAKE) -r -R -C $(ROOT_DIR)/src/dae platform=ps3 conf=release colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
	@$(MAKE) -r -R -C $(ROOT_DIR)/test platform=ps3 conf=release colladaVersion=$(colladaVersion) parser=$(parser) $(MAKECMDGOALS)
endif
endif

clean: all
