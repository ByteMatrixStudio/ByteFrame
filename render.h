#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>

#define WIDTH  800
#define HEIGHT 600

typedef struct {
  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_Event e;
  bool quit;
} rd_window;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} rd_color;

static rd_color rd_gray = { .r=0x18, .g=0x18, .b=0x18, .a=0xff};

static rd_window *default_w = {0};

#ifdef RD_IMPLEMENTATION
rd_window *rd_init_generic(const char* window_name, size_t width, size_t height){
  SDL_Init(SDL_INIT_VIDEO);
  rd_window *w = malloc(sizeof(rd_window));
  w->win = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  w->rend = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_SOFTWARE);
  w->quit = false;
  return w;
}



void rd_init(const char* window_name, size_t width, size_t height){
  SDL_Init(SDL_INIT_VIDEO);
  default_w = malloc(sizeof(rd_window));
  default_w->win = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  default_w->rend = SDL_CreateRenderer(default_w->win, -1, SDL_RENDERER_SOFTWARE);
  default_w->quit = false;
}

bool rd_close(){
  while(SDL_PollEvent(&default_w->e)) {
    if (default_w->e.type == SDL_QUIT) return true;
  }
  return false;
}

void rd_clear_gen(uint8_t r, uint8_t g, uint8_t b, uint8_t a){  
    SDL_SetRenderDrawColor(default_w->rend, r, g, b, a);
    SDL_RenderClear(default_w->rend);
    SDL_RenderPresent(default_w->rend);
}


void rd_clear(rd_color c){  
    SDL_SetRenderDrawColor(default_w->rend, c.r, c.g, c.b, c.a);
    SDL_RenderClear(default_w->rend);
    SDL_RenderPresent(default_w->rend);
}
void rd_quit(){
    SDL_DestroyRenderer(default_w->rend);
    SDL_DestroyWindow(default_w->win);
    SDL_Quit();
}
#endif // RD_IMPLEMENTATION
