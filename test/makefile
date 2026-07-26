#!/usr/sbin/make

TESTFILES = src/main.c

CFLAGS = -Wall -I../include -Iinclude -lSDL3 -L../build -Wl,-rpath,'$$ORIGIN' -lrmi

all: build

dir:
	mkdir -p build

link: dir
	ln  ../build/librmi.so build/librmi.so 

build: link # Linking sdl3 here in the meanwhile but the goal is to not do so. it gets linked to rmi anyways.
	gcc $(CFLAGS) $(TESTFILES) -obuild/test

clean:
	rm -r build/*
