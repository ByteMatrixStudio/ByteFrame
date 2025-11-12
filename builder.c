#define NB_IMPLEMENTATION
#include "nb.h"

int main(int argc, char** argv){
  nb_rebuild(argc, argv);

  nb_arr cmd = {0};

  nb_append_da(&cmd, "cc");
  nb_append_da(&cmd, "-o", "terminal");
  nb_append_da(&cmd, "examples/terminal.c");
  nb_cmd(&cmd);

  nb_append_da(&cmd, "cc");
  nb_append_da(&cmd, "-o", "raylib");
  nb_append_da(&cmd, "examples/raylib.c");
  nb_append_da(&cmd, "-lraylib");
  nb_cmd(&cmd);
  // nb_append(&cmd, "./terminal");
  // nb_cmd(&cmd);
  return 0;
}
