#!hi lol

RMIFILES = src/init.c \
	   src/globals.c

all: rmi

dirs:
	mkdir -p build build/cglm

cglm: dirs
	cmake -S cglm/ -B build/cglm -DCGLM_SHARED=OFF -DCGLM_STATIC=ON
	cmake --build build/cglm

rmi: cglm
	gcc -Icglm/include -Isrc -lSDL3 -L./build/cglm -l:libcglm.a -shared -fPIC $(RMIFILES) -obuild/librmi.so

clean:
	rm -r build/*
