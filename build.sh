#!/bin/bash
cd `dirname $0`
gcc src/*.c `sdl2-config --cflags --libs` -lSDL2_image -lm -Iinclude/ -o Doriftu
