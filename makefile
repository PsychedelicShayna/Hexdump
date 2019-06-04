binary = hexdump.exe
objects = main.o
stlver = c++14
target = 32

build/x$(target)/$(binary): $(addprefix build/x$(target)/objects/, $(objects))
	mkdir -p build/x$(target)/
	clang++ build/x$(target)/objects/*.o -o build/x$(target)/$(binary) -std=$(stlver) -m$(target)

build/x$(target)/objects/main.o: source/main.cxx
	mkdir -p build/x$(target)/objects
	clang++ source/main.cxx -c -o build/x$(target)/objects/main.o -std=$(stlver) -m$(target)