.DEFAULT_GOAL := all

ALL_TARGETS := $(patsubst %.puml,%.png,$(wildcard *.puml))

%.png: %.puml
	plantuml -p -tpng <$< >$@

.PHONY: all
all: $(ALL_TARGETS)
