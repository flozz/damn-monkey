#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


/**
 * \file main_functions.h
 * \brief The header file of main_functions.c.
 */


#include <stdio.h>
#include <stdio.h>
#include <string.h>

#ifdef LINUX
#include "SDL.h"
#include "SDL_image.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#endif

#ifdef WINDOWS
//TODO
#endif

#include "conf.h"


SDL_Surface* load_resource(char *resource_name);
SDL_Surface* str_to_surface(char *font_name, char *str);


#endif //MAIN_MENU_H_INCLUDED

