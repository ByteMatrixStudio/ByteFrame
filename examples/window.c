#define RD_IMPLEMENTATION
#include "../render.h"

#define WIDTH  800
#define HEIGHT 600

int main(void){
  rd_init("hello from renderer", WIDTH, HEIGHT);

  while (!rd_close()){      
    rd_clear(rd_gray);
  }
    
  rd_quit();

  return 0;
}
