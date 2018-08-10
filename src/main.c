#include <stdio.h>
#include "SDL2/SDL.h"

int main(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Event event;
  SDL_Window *win = SDL_CreateWindow("Doriftu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 400, 0);

  while(1)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        goto end;
      }
    }
  }

  end:
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
