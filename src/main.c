#include "engine.h"

int main(void)
{
  init();
  int t = 0;

  loadTexture("resources/sprites/car.png");
  loadTexture("resources/sprites/tire.png");
  car player;
  strcpy(player.tex,"resources/sprites/car.png");
  setTires(&player, "resources/sprites/tire.png");
  player.FR.pos = Vec(2-8,8);
  player.FR.steer = -30;
  player.FL.pos = Vec(8,8);
  player.FL.steer = -30;
  player.RR.pos = Vec(2-8,-8);
  player.RR.steer = 0;
  player.RL.pos = Vec(8,-8);
  player.RL.steer = 0;
  player.pos = Vec(100,100);
  player.scale = 2;
  player.angle = 30;

  while(1)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
        return 0;
      }
    }

    if(t % (int)floor((G_rate/R_rate)) == 0)
    {
      clear();
      drawCar(&player);
      SDL_RenderPresent(ren);
    }

    SDL_Delay(1000/G_rate);
    t = t < G_rate ? t + 1 : 0;
  }
}
