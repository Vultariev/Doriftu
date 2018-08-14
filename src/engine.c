#include "engine.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

void init()
{
  texts = 0;
  //Starting up good 'ol SDL2 with video
  SDL_Init(SDL_INIT_VIDEO);

  //Gota have a window for a game right? (Don't worry: win does not stand for winblows)
  win = SDL_CreateWindow("Doriftu",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_RESIZABLE);

  //Creating a renderer to draw stuff like textures
  ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  backgroundColor = createColor(255, 255, 255, 255);
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
    fprintf(stderr,"Can't load any more textures: buffer is full");
    return -2;
  }
  SDL_Surface *buff = IMG_Load(tex);
  if(buff == NULL)
  {
    buff = IMG_Load("resources/sprites/null-ship.png");
  }
  if(buff == NULL)
  {
    fprintf(stderr,"Could not load resources/sprites/null-ship.png: %s\n",SDL_GetError());
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
