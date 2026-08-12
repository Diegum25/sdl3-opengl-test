#!/usr/bin/make

RMIFILES = src/init.c \
	   src/globals.c \
	   src/log.c \
	   src/run.c \
	   src/window.c

OTHERFILES = build/glad/src/gl.c

CFLAGS = -Wall -I$(GLADOUTDIR)/include -Iinclude -Isrc -lSDL3 -shared -fPIC

BUILD = gcc $(CFLAGS) $(RMIFILES) $(OTHERFILES) -o$(RMI)

RMI = build/librmi.so
GLADOUTDIR = build/glad
GLAD = $(GLADOUTDIR)/include/glad/gl.h

.PHONY: all clean force

all: $(RMI)

$(GLAD): glad/glad
	PYTHONPATH=glad python -m glad --api gl:compatibility=4.6 --out-path $(GLADOUTDIR) --reproducible

$(RMI): $(RMIFILES) $(GLAD)
	$(BUILD)

force: $(RMIFILES) $(GLAD)
	$(BUILD)

clean:
	rm -rf build