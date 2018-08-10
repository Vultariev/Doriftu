#!/bin/bash
cd `dirname $0`
gcc src/*.c `sdl2-config --cflags --libs` -I"/Users/15410/.local/Homebrew-brew-5198ad4/include/" -o Doriftu
