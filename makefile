#!/usr/bin/make

RMIFILES = src/init.c \
	   src/globals.c \
	   src/log.c \
	   src/run.c

OTHERFILES = build/glad/src/gl.c

CFLAGS = -Wall -Icglm/include -Ibuild/glad/include -Iinclude -Isrc -lSDL3 -L./build/cglm -l:libcglm.a -shared -fPIC

BUILD = gcc $(CFLAGS) $(RMIFILES) $(OTHERFILES) -obuild/librmi.so 

all: rmi

dirs:
	mkdir -p build build/cglm build/glad

cglm: dirs
	cmake -S cglm/ -B build/cglm -DCGLM_SHARED=OFF -DCGLM_STATIC=ON
	cmake --build build/cglm

glad: dirs # i have no idea how to make this not run all the time
	PYTHONPATH=glad python -m glad --api gl:compatibility=4.6 --out-path build/glad --reproducible

rmi: cglm glad
	$(BUILD)

clean:
	rm -r build/*

force:
	$(BUILD)
