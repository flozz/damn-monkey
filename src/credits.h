#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


/**
 * \file credits.h
 * \brief The header file of credits.c.
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


typedef struct DM_Credits DM_Credits;
struct DM_Credits
{
	int numb_pages;
	int current_page;
	int speed;
	SDL_Surface **titles;
	SDL_Rect title_rect;
	SDL_Surface **pages;
	SDL_Rect page_rect;
};


DM_Credits* new_credits(int numb_pages);
void free_credits(DM_Credits *credits);
void credits_cb(void *object, SDL_Surface *screen);
void credits(SDL_Surface *screen);


#endif //MAIN_MENU_H_INCLUDED

