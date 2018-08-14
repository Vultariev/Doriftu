#include <stdio.h>
#include "SDL2/SDL.h"
#include "engine.h"

#define G_rate 100.000
#define R_rate 60.000

int main(void)
{
  init();
  int t = 0;


  while(1)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 0;
      }
    }

    if(t % (int)(G_rate/R_rate) == 0)
    {
      
    }

    if(t % (int)(G_rate/R_rate) == 1)
    {
      SDL_RenderPresent(ren);
    }

    SDL_Delay(1000/G_rate);
    t = t < G_rate ? t + 1 : 0;
    printf("\033[2KT: %d\r",t);
    fflush(stdout);
  }
}
