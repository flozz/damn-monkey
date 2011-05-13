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
 * \file sprite.h
 * \brief The header file of sprite.c.
 */


#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED


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
#include "parser.h"


/**
 * \def SPRITE_LOOK_RIGHT
 * \brief Don't move, just looking at right (for Jumpman).
 *
 * \def SPRITE_WALK_RIGHT
 * \brief Walking to the right (for Jumpman and the barrels).
 *
 * \def SPRITE_LOOK_LEFT
 * \brief Don't move, just looking at left (for Jumpman).
 *
 * \def SPRITE_WALK_LEFT
 * \brief Walking to the left (for Jumpman and the barrels).
 *
 * \def SPRITE_JUMP_RIGHT
 * \brief Jumping to the right (for Jumpman).
 *
 * \def SPRITE_JUMP_LEFT
 * \brief Jumping to the left (for Jumpman).
 *
 * \def SPRITE_LADDER
 * \brief Don't move, on a ladder (for Jumpman).
 *
 * \def SPRITE_WALK_LADDER
 * \brief Riding up or riding donw a ladder (for Jumpman and barrels).
 *
 * \def SPRITE_DEAD
 * \brief Dead (for Jumpman).
 *
 * \def SPRITE_THROW_BARREL
 * \brief Throwing barrels (for Donkey Kong).
 *
 * \def SPRITE_ASK_HELP
 * \brief Asking help (for Lady).
 *
 * \def SPRITE_CUSTOM
 * \brief Used for any animated objects.
 */
#define SPRITE_LOOK_RIGHT    0 //look-right
#define SPRITE_WALK_RIGHT    1 //walk-right
#define SPRITE_LOOK_LEFT     2 //look-left
#define SPRITE_WALK_LEFT     3 //walk-left
#define SPRITE_JUMP_RIGHT    4 //jump-right
#define SPRITE_JUMP_LEFT     5 //jump-left
#define SPRITE_LADDER        6 //ladder
#define SPRITE_WALK_LADDER   7 //walk-ladder
#define SPRITE_DEAD          8 //dead
#define SPRITE_THROW_BARREL  9 //throw-barrel
#define SPRITE_ASK_HELP     10 //ask-help
#define SPRITE_CUSTOM       11 //custom

/** \cond */ //Hide this to Doxygen
#define NUMB_SPRITE_ITEMS 12 //The number of sprites movements (SPRITES_*)
/** \endcond */


/**
 * \struct DM_Sprite_item
 * \brief Contains all the informations about a single animation of a
 *        sprite file.
 */
typedef struct DM_Sprite_item DM_Sprite_item;
struct DM_Sprite_item
{
	int x;  /*!< The x position of the first image. */
	int y;  /*!< The y position of the first image. */
	int w;  /*!< The width of an image. */
	int h;  /*!< The height of an image. */
	int n;  /*!< The number of images for this animation. */
	int d;  /*!< The delay between two steps of the animations. */
};


/**
 * \struct DM_Sprite
 * \brief Contains all the animations of a sprite file.
 */
typedef struct DM_Sprite DM_Sprite;
struct DM_Sprite
{
	SDL_Surface *sprite;        /*!< The sprite SDL_Surface. */
	DM_Sprite_item items[NUMB_SPRITE_ITEMS];    /*!< The animations list. */
	SDL_Rect screen_pos;        /*!< The position of the sprite on the screen. */
	SDL_Rect image_pos;         /*!< The position of the image in the sprite. */
	int current_mov;            /*!< The current movement (SPRITE_*). */
	int prev_mov;               /*!< \private */
	int step;                   /*!< \private */
	int last_step_change;       /*!< \private */
};


DM_Sprite* new_sprite(char *sprite_name);
void free_sprite(DM_Sprite *sprite);
void sprite_cb(void *object, SDL_Surface *screen);


#endif //SPRITE_H_INCLUDED

