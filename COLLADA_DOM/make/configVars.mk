ifeq ($(os),ps3)
cc := ppu-lv2-g++
ar := ppu-lv2-ar rcs
exeSuffix := .elf
else
cc := g++
ar := ar rcs
exeSuffix :=
endif

ccFlags := -Wall
ifeq ($(conf),debug)
ccFlags += -g -D_DEBUG
debugSuffix := -d
else
ccFlags += -O2 -DNDEBUG
debugSuffix :=
endif

# Clear out a bunch of variables that may have previously been set
src :=
targets :=
includeSearchPaths :=
libs :=
libSearchPaths :=
sharedLibSearchPaths :=
dependentLibs :=
postCreateExeCommand :=
outPath := build/$(os)-$(colladaVersion)$(if $(findstring debug,$(conf)),$(debugSuffix))/
objPath := $(outPath)obj/
colladaVersionNoDots := $(subst .,,$(colladaVersion))
xmlparsers := $(if $(findstring ps3,$(os)),tinyxml,$(parsers))