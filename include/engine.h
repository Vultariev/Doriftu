#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include <math.h>
#include <string.h>

#ifndef ENGINE_H_
#define ENGINE_H_

#define G_rate 100.000
#define R_rate 60.000
#define MAX_TEX 5
#define MAX_CTRL 4

typedef struct texture
{
	SDL_Texture *data;
	char file[256];
} texture;
int texts;
texture textures[MAX_TEX];

typedef struct ctrl
{
	char label[256];
	SDL_Keycode key;
	double value;
} ctrl;
int ctrls;
ctrl controls[MAX_CTRL];

typedef struct color
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
} color;

typedef struct vec
{
	double x;
	double y;
} vec;

typedef struct wheel
{
	vec vel; // the local velocity between the wheel contact patch and the ground surface
	vec pos; // the local position of the wheel reletive to the parent car
	vec lpos; //the last world pos of the wheel
	double inertia; //the wheel's resistance to torque
	double angvel; // the wheel's angular speed
	double steer; // the steer angle
	double load; //the weight of the car on the wheel
	double cf; // the coef of friction
	char tex[256]; // the texture of the wheel
} wheel;

typedef struct car
{
	wheel FR, FL, RR, RL;
	double scale; //the render scale of the car
	double inertia; // the rotational mass of the car
	double mass; //the mass of the car
	vec force; //the total force being applied to the car
	vec vel; //the velocity of the car
	vec pos; //the current world position of the car
	double angle, angvel, torque;
	vec trans; //this emulates weight transfer
	vec tr; //this is the constant for the weight transfer system
	char tex[256]; // the texture of the car body
} car;

SDL_Window *win;

SDL_Renderer *ren;

color backgroundColor;

//Making a varible for events like keypresses, mouse movements, etc...
SDL_Event event;

void init();

double neg(double a);

vec Vec(double x, double y);

color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void createctrl(char label[], SDL_Keycode key);

double getctrl(char label[]);

void applyForce(car *in, vec force, vec pos);

void tickCar(car* in);

void setTires(car* in, char all[]);

void setDrawColor(color in);

void clear();

int loadTexture(char tex[]);

int textureIndex(char tex[]);

int drawTexture(char tex[], vec pos, double angle, double scalex, double scaley);

SDL_Texture * grabTexture(char tex[]);

vec vadd(vec a, vec b);

double magnitude(vec a);

double direction(vec a);

vec split(double direction, double magnitude);

void drawCar(car * in);

#endif
