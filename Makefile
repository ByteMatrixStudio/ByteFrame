all: libbyteframe.so libbyteframe.o libbyteframe.a example folders pong mandlebrot


libbyteframe.a: libbyteframe.o folders
	ar rcs lib/libbyteframe.a libbyteframe.o

libbyteframe.o:
	g++ -c -o libbyteframe.o -I./includes ./byteframe.cpp -O3

libbyteframe.so: folders byteframe.cpp
	g++ -fPIC -shared -I./includes -o lib/libbyteframe.so ./byteframe.cpp -O3


folders:
	mkdir -p lib/

pong:
	g++ ./examples/pongish.cpp -o pong -I./includes -L./lib -l:libbyteframe.a -lraylib -O3


example:
	g++ ./examples/example.cpp -o example -I./includes -L./lib -l:libbyteframe.a -lraylib -O3

mandlebrot: libbyteframe.a
	g++ ./examples/mandlebrot.cpp -o mandlebrot -I./includes -L./lib -l:libbyteframe.a -lraylib -O3
