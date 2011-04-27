#ifndef CREDITS_H_INCLUDED
#define CREDITS_H_INCLUDED


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


/**
 * \struct DM_Credits
 * \brief Contain all the informations needed for displaying credits.
 */
typedef struct DM_Credits DM_Credits;
struct DM_Credits
{
	int numb_pages;       /*!< Number of pages. */
	int current_page;     /*!< Index of the current page (1..numb_page). */
	int speed;            /*!< The speed of the translation effect. */
	SDL_Surface **titles; /*!< Contain the SDL_Surface of all titles. */
	SDL_Rect title_rect;  /*!< Contain placement information of the title. */
	SDL_Surface **pages;  /*!< Contain the SDL_Surface of all pages. */
	SDL_Rect page_rect;   /*!< Contain placement information of the page. */
};


DM_Credits* new_credits(int numb_pages);
void free_credits(DM_Credits *credits);
void credits_cb(void *object, SDL_Surface *screen);
void credits(SDL_Surface *screen);


#endif //CREDITS_H_INCLUDED

