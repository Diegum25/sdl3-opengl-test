#!/usr/bin/make

RMIFILES = src/init.c \
	   src/globals.c \
	   src/log.c \
	   src/run.c

OTHERFILES = build/glad/src/gl.c

CFLAGS = -Wall -Icglm/include -Ibuild/glad/include -Iinclude -Isrc -lSDL3 -L./build/cglm -l:libcglm.a -shared -fPIC

BUILD = gcc $(CFLAGS) $(RMIFILES) $(OTHERFILES) -o$(RMI)

RMI = build/librmi.so
GLADOUTDIR = build/glad
GLAD = $(GLADOUTDIR)/include/glad/gl.h
CGLMOUTDIR = build/cglm
CGLM = $(CGLMOUTDIR)/libcglm.a

.PHONY: all clean

all: $(RMI)

$(GLAD): glad/glad
	PYTHONPATH=glad python -m glad --api gl:compatibility=4.6 --out-path $(GLADOUTDIR) --reproducible

$(CGLM): cglm/src
	cmake -S cglm/ -B $(CGLMOUTDIR) -DCGLM_SHARED=OFF -DCGLM_STATIC=ON
	cmake --build $(CGLMOUTDIR)

$(RMI): $(RMIFILES) $(GLAD) $(CGLM)
	$(BUILD)

clean:
	rm -rf build