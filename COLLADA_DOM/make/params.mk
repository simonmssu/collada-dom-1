# platform: 'linux', 'ps3', or 'all'
platform := linux

# Build configuration: 'release', 'debug', or 'all'
conf := release

# Collada version: No other versions supported for now
colladaVersion := 1.4

# parser: 'libxml', 'tinyxml', or 'all'.
parser := libxml


# Internal variables. You typically won't want to set these yourself on the command line.

colladaVersionNoDots := 14

# Set linux, ps3 variables based on platform
ifeq ($(platform), all)
linux := yes
ps3 := yes
else ifeq ($(platform), linux)
linux := yes
else ifeq ($(platform), ps3)
ps3 := yes
endif

# Set debug, release variables based on configuration
ifeq ($(conf), all)
debug := yes
release := yes
else ifeq ($(conf), release)
release := yes
else ifeq ($(conf), debug)
debug := yes
endif

# Set libxml, tinyxml variables based on parser setting
ifeq ($(parser), all)
libxml := yes
tinyxml := yes
else ifeq ($(parser), libxml)
libxml := yes
else ifeq ($(parser), tinyxml)
tinyxml := yes
endif
