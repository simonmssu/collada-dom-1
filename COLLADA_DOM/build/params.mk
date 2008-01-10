#debug/release/both
#1.4/1.5/all
#libxml/TinyXml/both
#clean+build option

# or 'debug' or 'all'
conf := release

# No other versions supported for now
colladaVersion := 1.4

# or 'tinyxml' or 'both'
parser := libxml

# Clean first? 'yes' or 'no'
clean := no

ifeq ($(conf), both)
debug := yes
release := yes
endif

ifeq ($(conf), release)
debug :=
release := yes
endif

ifeq ($(conf), debug)
debug := yes
release :=
endif

colladaVersionNoDots := 14

ifeq ($(parser), both)
libxml := yes
tinyxml := yes
endif

ifeq ($(parser), libxml)
libxml := yes
tinyxml := no
endif

ifeq ($(parser), tinyxml)
libxml := no
tinyxml := yes
endif