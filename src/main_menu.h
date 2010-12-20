#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


/**
 * \file main_menu.h
 * \brief The header file of main_menu.c.
 */


#include <stdio.h>
#include <stdio.h>

#ifdef LINUX
#include "SDL.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#endif

#ifdef WINDOWS
//TODO
#endif

#include "main_functions.h"
#include "menu.h"


void corp_logo(SDL_Surface *screen);


#endif //MAIN_MENU_H_INCLUDED

