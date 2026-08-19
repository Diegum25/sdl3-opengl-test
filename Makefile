#!/usr/bin/make

RMIFILES = src/init.c \
	   src/globals.c \
	   src/log.c \
	   src/run.c \
	   src/window.c

OTHERFILES = build/glad/src/gl.c

CFLAGS = -Wall -O3 -s -I$(GLADOUTDIR)/include -Iinclude -Isrc -lSDL3 -shared -fPIC -Lbuild -Wl,-rpath,'$$ORIGIN' -lglad

BUILD = gcc $(CFLAGS) $(RMIFILES) -o$(RMI)

# this many variables actually look like ass
RMI = build/librmi.so
GLADOUTDIR = build/glad
GLAD = $(GLADOUTDIR)/include/glad/gl.h

.PHONY: all clean force

all: $(RMI)

build/libglad.so: $(OTHERFILES) $(GLAD)
	gcc -Wall -O3 -s -I$(GLADOUTDIR)/include -shared -fPIC $(OTHERFILES) -obuild/libglad.so

$(GLAD): glad/glad
	PYTHONPATH=glad python -m glad --api gl:compatibility=4.6 --out-path $(GLADOUTDIR) --reproducible

$(RMI): $(RMIFILES) $(GLAD) build/libglad.so
	$(BUILD)

clean:
	rm -rf build
