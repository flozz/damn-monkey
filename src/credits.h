/****************************************************************************
*        ___                                           _                    *
*       /   \__ _ _ __ ___  _ __     /\/\   ___  _ __ | | _____ _   _       *
*      / /\ / _` | '_ ` _ \| '_ \   /    \ / _ \| '_ \| |/ / _ \ | | |      *
*     / /_// (_| | | | | | | | | | / /\/\ \ (_) | | | |   <  __/ |_| |      *
*    /___,' \__,_|_| |_| |_|_| |_| \/    \/\___/|_| |_|_|\_\___|\__, |      *
*                                                               |___/       *
*                                                                           *
*   This file is part of Damn Monkey                                        *
*                                                                           *
*   Copyright (C) 2010 - 2011  Fabien LOISON                                *
*   Copyright (C) 2010 - 2011  Mathilde BOUTIGNY                            *
*   Copyright (C) 2010 - 2011  Vincent PEYROUSE                             *
*   Copyright (C) 2010 - 2011  Germain CARRÉ                                *
*   Copyright (C) 2010 - 2011  Matthis FRENAY                               *
*                                                                           *
*   Damn Monkey is free software: you can redistribute it and/or modify     *
*   it under the terms of the GNU General Public License as published by    *
*   the Free Software Foundation, either version 3 of the License, or       *
*   (at your option) any later version.                                     *
*                                                                           *
*   This program is distributed in the hope that it will be useful,         *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
*   GNU General Public License for more details.                            *
*                                                                           *
*   You should have received a copy of the GNU General Public License       *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
*                                                                           *
*****************************************************************************
*                                                                           *
*  WEB SITE: https://launchpad.net/damn-monkey                              *
*                                                                           *
****************************************************************************/


/**
 * \file credits.h
 * \brief The header file of credits.c.
 */


#ifndef CREDITS_H_INCLUDED
#define CREDITS_H_INCLUDED


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

