#!/bin/bash
cd `dirname $0`
gcc src/*.c `sdl2-config --cflags --libs` -Iinclude/ -o Doriftu
