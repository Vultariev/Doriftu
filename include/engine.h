#include "SDL2/SDL.h"

#ifndef ENGINE_H_
#define ENGINE_H_

#define MAX_TEX 5

typedef struct texture
{
	SDL_Texture *data;
	char file[256];
} texture;
int texts;

texture textures[MAX_TEX];

typedef struct ctrl
{
	SDL_Keycode key;
	double value;
} ctrl;

typedef struct color
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
} color;

SDL_Window *win;

SDL_Renderer *ren;

color backgroundColor;

//Making a varible for events like keypresses, mouse movements, etc...
SDL_Event event;

void init();

color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void setDrawColor(color in);

void clear();

int loadTexture(char tex[]);

int textureIndex(char tex[]);

SDL_Texture * grabTexture(char tex[]);

#endif
