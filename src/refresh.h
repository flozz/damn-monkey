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
 * \file refresh.h
 * \brief The header file of refresh.c.
 */


#ifndef REFRESH_H_INCLUDED
#define REFRESH_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>

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


/**
 * \struct DM_Refresh_Layer
 * \brief A Layer.
 */
typedef struct DM_Refresh_Layer DM_Refresh_Layer;
struct DM_Refresh_Layer
{
	SDL_Surface *screen;          /*!< The main SDL_Surface. */
	struct DM_Refresh_Item *next; /*!< Pointer on the first item of the list */
};


/**
 * \struct DM_Refresh_Item
 * \brief An object to refresh.
 */
typedef struct DM_Refresh_Item DM_Refresh_Item;
struct DM_Refresh_Item
{
	int id;                       /*!< A unique identifier for the item. */
	void *object;                 /*!< Pointer on the object. */
	void (*callback)();           /*!< The callback function that blit the object. */
	struct DM_Refresh_Item *next; /*!< Pointer on the next item of the list. */
};


/**
 * \var LAYER_BG
 * \brief The background layer.
 *
 * Used for the level objects like platforms,...
 */
DM_Refresh_Layer LAYER_BG;

/**
 * \var LAYER_ACTIVE
 * \brief The active layer.
 *
 * Contains the actives objects such as Jumpman, the barrels,...
 */
DM_Refresh_Layer LAYER_ACTIVE;

/**
 * \var LAYER_FG
 * \brief The foreground layer.
 *
 * Used for objects that should be over Jumpman, and for displaying the
 * remaining lives and the score.
 */
DM_Refresh_Layer LAYER_FG;

/**
 * \var LAYER_MENU
 * \brief The menu layer.
 *
 * Used for displaying the menus.
 */
DM_Refresh_Layer LAYER_MENU;

/** \cond */ //Hide this to doxygen
SDL_TimerID main_timer;
/** \endcond */


void refresh_init(SDL_Surface *screen);
void refresh_destroy();
int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)());
void deref_object(DM_Refresh_Layer *layer, int id);
Uint32 refresh_cb(Uint32 interval, void *arg);
void surface_refresh_cb(void *object, SDL_Surface *screen);
/** \cond */ //Hide the "privates" functions for Doxygen
int _get_id();
/** \endcond */

#endif //REFRESH_H_INCLUDED

