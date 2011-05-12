#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


/**
 * \file main_menu.h
 * \brief The header file of main_menu.c.
 */


#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#ifdef LINUX
#include "SDL.h"
#include "SDL_mixer.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_mixer.h>
#endif

#include "refresh.h"
#include "main_functions.h"
#include "menu.h"


/**
 * \def MAIN_MENU_PLAY
 * \brief Play item selected.
 *
 * \def MAIN_MENU_CREDITS
 * \brief Credit item selected.
 *
 * \def MAIN_MENU_QUIT
 * \brief Quit item selected.
 */
#define MAIN_MENU_PLAY    0
#define MAIN_MENU_CREDITS 1
#define MAIN_MENU_QUIT    2


void corp_logo(SDL_Surface *screen);
int main_menu(SDL_Surface *screen);


#endif //MAIN_MENU_H_INCLUDED

