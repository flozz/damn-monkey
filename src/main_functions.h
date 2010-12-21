#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


/**
 * \file main_functions.h
 * \brief The header file of main_functions.c.
 */


#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LINUX
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_mixer/SDL_mixer.h>
#endif

#ifdef WINDOWS
//TODO
#endif


SDL_Surface* load_resource(char *resource_name);
SDL_Surface* str_to_surface(char *font_name, char *str);
Mix_Chunk* load_sound_resource(char *resource_name);


#endif //MAIN_MENU_H_INCLUDED

