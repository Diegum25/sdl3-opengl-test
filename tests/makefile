TESTFILES = main.c

all: build

link:
	ln -f ../build/librmi.so build/librmi.so 

build: link
	gcc main.c -L../build -Wl,-rpath '$$ORIGIN' -lrmi -obuild/test
