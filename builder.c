#define NB_IMPLEMENTATION
#include "nb.h"

int main(int argc, char** argv){
  nb_rebuild(argc, argv);

  nb_arr cmd = {0};

  nb_append_da(&cmd, "cc");
  nb_append_da(&cmd, "-o", "window");
  nb_append_da(&cmd, "examples/window.c");
  nb_append_da(&cmd, "-lSDL2");
  nb_cmd(&cmd);

  nb_append(&cmd, "./window");
  nb_cmd(&cmd);

  return 0;
}
