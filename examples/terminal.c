#define RD_IMPLEMENTATION
#define MT_IMPLEMENTATION
#define MT_STRIP_PREFIX
#include "../mathx.h"
#include "../renderfull.h"

#define FPS 30

int main(void){
  rd_canvas canva = {0};
  rd_init_canvas(&canva, 200, 100);

  float dt = (float)1/FPS; 
  Vec2 rec1 = {.x=50, .y=50};
  Vec2 rec2 = {.x=0, .y=10};
   
  while (true){
    usleep(1000 * 1000 * dt); 
    Vec2transformP(&rec1, 10*dt, 20*dt);
    rd_fill_background(&canva, rd_white);
    rd_draw_rect(&canva, 40, 20, rec2.x, rec2.y, rd_blue);
    rd_draw_rect(&canva, 30, 20, rec1.x, rec1.y, rd_red);
    rd_draw_rect(&canva, 10, 20, 40, 60, rd_green);
    rd_canvas_to_terminal(&canva);

    uint8_t key = rd_poll_key_terminal();

    if      (key == 'w') Vec2transformP(&rec2, 0*dt, 20*dt);
    else if (key == 'a') Vec2transformP(&rec2, -40*dt, 0*dt);
    else if (key == 's') Vec2transformP(&rec2, 0*dt, -20*dt);
    else if (key == 'd') Vec2transformP(&rec2, 40*dt, 0*dt);
  }
   return 0;
}
