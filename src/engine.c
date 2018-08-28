#include "engine.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

void init()
{
  ctrls = 0;
  texts = 0;
  //Starting up good 'ol SDL2 with video
  SDL_Init(SDL_INIT_VIDEO);

  //Gota have a window for a game right? (Don't worry: win does not stand for winblows)
  win = SDL_CreateWindow("Doriftu",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_RESIZABLE);

  //Creating a renderer to draw stuff like textures
  ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  backgroundColor = createColor(255, 255, 255, 255);
}

double neg(double a)
{
  if(a > 0)
  {
    return 1;
  }
  if(a < 0)
  {
    return -1;
  }
  return 1;
}

vec Vec(double x, double y)
{
  vec o;
  o.x = x;
  o.y = y;
  return o;
}

color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  color out;
  out.r = r;
  out.g = g;
  out.b = b;
  out.a = a;
  return out;
}

int ctrlindex(char label[])
{
  int i = ctrls-1;
  while(i >= 0)
  {
    if(strcmp(controls[i].label,label) == 0)
    {
      return i;
    }
    i--;
  }
  return -1;
}

void createctrl(char label[], SDL_Keycode key)
{
  if(ctrlindex(label) == -1)
  {
    strcat(controls[ctrls].label, label);
    controls[ctrls].key = key;
    ctrls++;
  }
}

double getctrl(char label[])
{
  return controls[ctrlindex(label)].value;
}

void applyForce(car *in, vec force, vec pos)
{
  vec delta = in->pos;
  delta.x -= pos.x;
  delta.y -= pos.y;
  in->force.x += force.x;
  in->force.y += force.y;
  in->torque += magnitude(delta)*sin((direction(delta) + direction(force))*M_PI/180);
}

void tickCar(car* in)
{
  in->vel.x += in->force.x/in->mass/G_rate;
  in->vel.y += in->force.y/in->mass/G_rate;
  in->force.x = 0;
  in->force.y = 0;
  in->pos.x += in->vel.x/G_rate;
  in->pos.y += in->vel.y/G_rate;
  in->angvel += in->torque/in->inertia/G_rate;
  in->torque = 0;
  in->angle += in->angvel/G_rate;
}

void setTires(car* in, char all[])
{
  strcpy(in->FR.tex, all);
  strcpy(in->FL.tex, all);
  strcpy(in->RR.tex, all);
  strcpy(in->RL.tex, all);
}

void setDrawColor(color in)
{
  SDL_SetRenderDrawColor(ren,in.r,in.g,in.b,in.a);
}

void clear()
{
  setDrawColor(backgroundColor);
  SDL_RenderClear(ren);
}

int loadTexture(char tex[])
{
  if(texts >= MAX_TEX)
  {
    fprintf(stderr, "Cannot load any more textures: buffer is full\n\n");
    return -2;
  }
  SDL_Surface *buff = IMG_Load(tex);
  if(buff == NULL)
  {
    fprintf(stderr, "Could not load %s: %s\n\n", tex, SDL_GetError());
    return -1;
  }

  strcpy(textures[texts].file,tex);

  textures[texts].data = SDL_CreateTextureFromSurface(ren,buff);;

  texts++;
  return 0;
}

int textureIndex(char tex[])
{
  int i = 0;
  while(i < MAX_TEX)
  {
    if(strcmp(textures[i].file,tex) == 0)
    {
      return i;
    }
    i++;
  }
  return -1;
}

SDL_Texture * grabTexture(char tex[])
{
  if(textureIndex(tex) != -1)
  {
    return textures[textureIndex(tex)].data;
  }
  else
  {
    loadTexture(tex);
    return textures[textureIndex(tex)].data;
  }
  return NULL;
}

int drawTexture(char tex[], vec pos, double angle, double scalex, double scaley)
{
  SDL_Texture * draw = grabTexture(tex);
  if(draw == NULL)
  {
    if(loadTexture(tex) != 0)
    {
      return -1;
    }
  }
  draw = grabTexture(tex);
  if(draw == NULL)
  {
    return -2;
  }
  SDL_Rect d;
  SDL_QueryTexture(draw, NULL, NULL, &d.w, &d.h);
  d.w *= scalex;
  d.h *= scaley;
  d.x = (int)pos.x - d.w/2;
  d.y = (int)pos.y - d.h/2;
  SDL_RenderCopyEx(ren, draw, NULL, &d, angle, NULL, 0);
  return 0;
}

double magnitude(vec a)
{
  return sqrt(a.x*a.x+a.y*a.y);
}

double direction(vec a)
{
  if(a.y > 0)
  {
    return -atan(a.x/a.y)*180/M_PI;
  }
  if(a.x != 0)
  {
    return -(-atan(a.y/a.x)*180/M_PI + 90*neg(a.x));
  }
  return 0;
}

vec split(double direction, double magnitude)
{
  vec out;
  out.y = sin(direction*M_PI/180 - M_PI/2)*magnitude;
  out.x = cos(direction*M_PI/180 - M_PI/2)*magnitude;
  return out;
}

vec vadd(vec a, vec b)
{
  a.x += b.x;
  a.y += b.y;
  return a;
}

void drawCar(car * in)
{
  drawTexture(in->FR.tex, vadd(in->pos,split(in->angle + direction(in->FR.pos), magnitude(in->FR.pos)*in->scale)), in->angle + in->FR.steer, in->scale, in->scale);
  drawTexture(in->FL.tex, vadd(in->pos,split(in->angle + direction(in->FL.pos), magnitude(in->FL.pos)*in->scale)), in->angle + in->FL.steer, in->scale, in->scale);
  drawTexture(in->RR.tex, vadd(in->pos,split(in->angle + direction(in->RR.pos), magnitude(in->RR.pos)*in->scale)), in->angle + in->RR.steer, in->scale, in->scale);
  drawTexture(in->RL.tex, vadd(in->pos,split(in->angle + direction(in->RL.pos), magnitude(in->RL.pos)*in->scale)), in->angle + in->RL.steer, in->scale, in->scale);
  drawTexture(in->tex, in->pos, in->angle, in->scale, in->scale);
}
