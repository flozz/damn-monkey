#ifndef PAUSE_MENU_H_INCLUDED
#define PAUSE_MENU_H_INCLUDED


/**
 * \file pause_menu.h
 * \brief The header file of pause_menu.c.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conf.h"

#ifdef LINUX
#include "SDL.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#endif

#include "main_functions.h"
#include "refresh.h"
#include "menu.h"


int pause_menu(SDL_Surface *screen);


#endif //PAUSE_MENU_H_INCLUDED

