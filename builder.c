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

  nb_append(&cmd, "clang");
  nb_append(&cmd, "-O3");
  nb_append(&cmd, "--target=wasm32");
  nb_append(&cmd, "-nostdlib");
  nb_append(&cmd, "-Wl,--export-table");
  nb_append(&cmd, "-Wl,--no-entry");
  nb_append(&cmd, "-Wl,--export=make_canvas");
  nb_append(&cmd, "-Wl,--export=draw_demo");
  nb_append(&cmd, "-Wl,--export=canvas_pixels");
  nb_append(&cmd, "-Wl,--export=canvas_width");
  nb_append(&cmd, "-Wl,--export=canvas_height");
  nb_append(&cmd, "examples/wasm.c");
  nb_append(&cmd, "-o");
  nb_append(&cmd, "renderer.wasm");
  nb_cmd(&cmd);
  // nb_append(&cmd, "./terminal");
  // nb_cmd(&cmd);
  return 0;
}
