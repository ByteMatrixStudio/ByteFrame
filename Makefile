all: libbyteframe.so libbyteframe.o libbyteframe.a example folders


libbyteframe.a: libbyteframe.o folders
	ar rcs lib/libbyteframe.a libbyteframe.o

libbyteframe.o:
	g++ -c -o libbyteframe.o -I./includes ./byteframe.cpp

libbyteframe.so: folders byteframe.cpp
	g++ -fPIC -shared -I./includes -o lib/libbyteframe.so ./byteframe.cpp


folders:
	mkdir -p lib/

example:
	g++ ./examples/example.cpp -o example -I./includes -L./lib -l:libbyteframe.a -lraylib
