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
  createctrl("gas", SDLK_w);
  createctrl("brake", SDLK_s);
  createctrl("right", SDLK_d);
  createctrl("left", SDLK_a);
  player.FR.pos = Vec(2-8,8);
  player.FL.pos = Vec(8,8);
  player.RR.pos = Vec(2-8,-8);
  player.RR.steer = 0;
  player.RL.pos = Vec(8,-8);
  player.RL.steer = 0;
  player.pos = Vec(100,100);
  player.scale = 2;
  player.angle = 30;
  player.vel = Vec(0,1);
  player.mass = 100;
  player.inertia = 200;
  player.force = Vec(0,0);
  double srate, steer, steert;
  srate = 2;
  while(1)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
        printf("\033[2K");
        return 0;
      }
      if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
      {
        int i = ctrls-1;
        while(i >= 0)
        {
          if(controls[i].key == event.key.keysym.sym)
          {
            if(event.type == SDL_KEYUP)
            {
              controls[i].value = 0;
            }
            else
            {
              controls[i].value = 1;
            }
          }
          i--;
        }
      }
    }

    if(t % (int)floor((G_rate/R_rate)) == 0)
    {
      clear();
      drawCar(&player);
      SDL_RenderPresent(ren);
    }

    {
      if(getctrl("gas"))
      {
        applyForce(&player, split(player.angle, 100), vadd(player.pos, split(player.angle, (player.RR.pos.y + player.RL.pos.y)/0.5)));
      }
      tickCar(&player);
      steert = 30*(getctrl("right") - getctrl("left"));
      if(fabs(steert-steer) < srate)
      {
        steer = steert;
      }
      steer += (steer < steert)*srate - (steer > steert)*srate;
      player.FR.steer = steer;
      player.FL.steer = steer;
      printf("\033[2KPlayer FR vel: ( %f, %f )\r",player.FR.vel.x, player.FR.vel.y);
      fflush(stdout);
    }

    SDL_Delay(1000/G_rate);
    t = t < G_rate ? t + 1 : 0;
  }
}
