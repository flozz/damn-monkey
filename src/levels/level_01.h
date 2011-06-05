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
 * \file level_01.h
 * \brief The header file of level_01.c.
 */


#ifndef LEVEL_01_H_INCLUDED
#define LEVEL_01_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../conf.h"

#ifdef LINUX
#include "SDL.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#endif

#include "../main_functions.h"
#include "../refresh.h"
#include "../game.h"
#include "../sprite.h"


/**
 * \struct DM_Barrel
 * \brief Contain informations about one barrel.
 */
typedef struct DM_Barrel DM_Barrel;
struct DM_Barrel
{
	DM_Map *map;                  /*!< Pointer to the DM_Map considered*/
	DM_Collide *platform_collide; /*!< Collision point with platforms. */
	DM_Collide *jumpman_collide;  /*!< Collision rect with jumpman. */
	DM_Sprite *sprite;            /*!< The sprite of barrel. */
	int refresh_id;               /*!< The refresh id*/
};


/**
 * \struct DM_Barrel_Array
 * \brief Contain informations about barrels.
 */
typedef struct DM_Barrel_Array DM_Barrel_Array;
struct DM_Barrel_Array
{
	DM_Barrel *barrels;          /*!< Barrels array*/
	DM_Sprite *damnmonkey;       /*!< Damn Monkey sprite */
	int numb_items;              /*!< The number of barrels in the array*/
	int last_sent;               /*!< The last sent barrel index in the array*/
};


/** \cond */ //Hide this to doxygen
SDL_TimerID barrel_timer;
/** \endcond */

DM_Barrel_Array *BARRELS;


void barrel_init(SDL_Surface *screen);
void barrel_destroy();
int ref_barrel(void *object, void (*callback)());
void deref_barrel(int id);
void barrel_cb(void *object, SDL_Surface *screen);
/** \cond */ //Hide this to doxygen
Uint32 _barrel_cb(Uint32 interval, void *arg);
/** \endcond */
int check_platform_orientation(DM_Collide *collide_point, DM_Map *map);
void free_dm_barrel(DM_Barrel *barrels);
void level_01(SDL_Surface *screen);


#endif //LEVEL_01_H_INCLUDED

