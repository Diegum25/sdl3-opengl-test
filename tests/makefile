TESTFILES = main.c

all: build

dir:
	mkdir -p build

link: dir
	ln -f ../build/librmi.so build/librmi.so 

build: link
	gcc main.c -L../build -Wl,-rpath,'$$ORIGIN' -lrmi -obuild/test

clean:
	rm -r build/*
