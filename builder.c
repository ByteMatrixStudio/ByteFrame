#define NB_IMPLEMENTATION
#include "./nb.h"



void build_libs(nb_arr *cmd) {
    nb_mkdir_if_not_exist("lib");
    nb_append_da(cmd,
        "g++", "-c", "-o", "libbyteframe.o",
        "-I./includes", "./byteframe.cpp", "-O3");
    nb_cmd(cmd);

    nb_append_da(cmd, "ar", "rcs", "lib/libbyteframe.a", "libbyteframe.o");
    nb_cmd(cmd);

    nb_append_da(cmd,
        "g++", "-fPIC", "-shared", "-I./includes",
        "-o", "lib/libbyteframe.so", "./byteframe.cpp", "-O3");
    nb_cmd(cmd);
}

void build_examples(nb_arr *cmd) {
     nb_append_da(cmd,
        "g++", "./examples/example.cpp", "-o", "example",
        "-I./includes", "-L./lib",
        "-l:libbyteframe.a", "-lraylib", "-O3");
    nb_cmd(cmd);

    nb_append_da(cmd,
        "g++", "./examples/pongish.cpp", "-o", "pong",
        "-I./includes", "-L./lib",
        "-l:libbyteframe.a", "-lraylib", "-O3");
    nb_cmd(cmd);

     nb_append_da(cmd,
        "g++", "./examples/mandlebrot.cpp", "-o", "mandlebrot",
        "-I./includes", "-L./lib",
        "-l:libbyteframe.a", "-lraylib", "-O3");
    nb_cmd(cmd);
    nb_append_da(cmd, 
                 "g++", "./examples/snake.cpp", "-o", "snake", "-I./includes", "-L./lib", "-l:libbyteframe.a", "-lraylib", "-O3"
                 );
    nb_cmd(cmd);
}   

int main(int argc, char **argv) {
    float time_begin = nb_time();
    
    nb_rebuild(argc, argv);

    nb_arr cmd = {0};

    if (argc > 1){
        if (strcmp(argv[1], "libs") == 0) build_libs(&cmd);
        if (strcmp(argv[1], "examples") == 0) build_examples(&cmd);
    } else {
        build_libs(&cmd);
        build_examples(&cmd);
    }
    
    printf("\nTook %.2f seconds to build\n", (nb_time()-time_begin));
    return 0;
}
