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


/**
 * \def PAUSE_MENU_CONTINUE
 * \brief Continue item selected.
 *
 * \def PAUSE_MENU_MAIN_MENU
 * \brief Main Menu item selected.
 *
 * \def PAUSE_MENU_QUIT
 * \brief Quit item selected.
 */
#define PAUSE_MENU_CONTINUE  0
#define PAUSE_MENU_MAIN_MENU 1
#define PAUSE_MENU_QUIT      2


int pause_menu(SDL_Surface *screen);


#endif //PAUSE_MENU_H_INCLUDED

