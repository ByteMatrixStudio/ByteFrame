#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#define MX_IMPLEMENTATION // TODO: FIX THIS
#define RD_IMPLEMENTATION 
#include "../renderfull.h"
#include "../mathx.h"
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 600

int main(void){
  rd_canvas canva = {0};
  rd_init_canvas(&canva, WIDTH, HEIGHT);
  InitWindow(WIDTH, HEIGHT, "hello from raylib");

  Image img = {.data=canva.pixels, .width=WIDTH, .height=HEIGHT, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
  Texture2D tex = LoadTextureFromImage(img);
  mt_Vec2 rec1 = {.x=50, .y=50};


  while (!WindowShouldClose()){
    float dt = GetFrameTime();
    SetTargetFPS(60);
            
    mt_Vec2transformP(&rec1, 10*dt, 20*dt);
    
    rd_fill_background(&canva, rd_white);
    rd_draw_rect(&canva, 40, 20, 0, 0, rd_blue);
    rd_draw_rect(&canva, 30, 20, rec1.x, rec1.y, rd_red);
    rd_draw_rect(&canva, 10, 20, 40, 60, rd_green);

    BeginDrawing();    
    {
      DrawFPS(0, 10);
      UpdateTexture(tex, canva.pixels);
      DrawTexture(tex, 0, 0, WHITE);
    }
    EndDrawing();
  }
  CloseWindow();
  // rd_canvas_to_ppm(&canva, "image.ppm");
  return 0;
}
