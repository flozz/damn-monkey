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
 * \file game.h
 * \brief The header file of game.c.
 */


#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LINUX
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_mixer/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#endif

#include "sprite.h"
#include "refresh.h"
#include "parser.h"
#include "pause_menu.h"


/**
 * \def COLLIDE_RECT
 * \brief Collide shape: rectangular.
 *
 * \def COLLIDE_LINE
 * \brief Collide shape: segment.
 *
 * \def COLLIDE_POINT
 * \brief Collide shape: point.
 */
#define COLLIDE_RECT  0
#define COLLIDE_LINE  1
#define COLLIDE_POINT 2

/**
 * \def GAME_STATE_NONE
 * \brief Game state: not playing.
 *
 * \def GAME_STATE_PLAYING
 * \brief Game state: playing.
 *
 * \def GAME_STATE_PAUSED
 * \brief Game state: paused (the pause menu is displayed).
 *
 * \def GAME_STATE_LEVEL_COMPLETED
 * \brief Game state: level completed (the player won).
 *
 * \def GAME_STATE_LIFE_LOST
 * \brief Game state: the player lost a life.
 *
 * \def GAME_STATE_OVER
 * \brief Game state: Game Over (no lives remaining).
 */
#define GAME_STATE_NONE            0
#define GAME_STATE_PLAYING         1
#define GAME_STATE_PAUSED          2
#define GAME_STATE_LEVEL_COMPLETED 3
#define GAME_STATE_LIFE_LOST       4
#define GAME_STATE_OVER            5

/**
 * \def HORIZ_MOVE_NONE_L
 * \brief Horizontal move: no horizontal move, looking left.
 *
 * \def HORIZ_MOVE_NONE_R
 * \brief Horizontal move: no horizontal move, looking right.
 *
 * \def HORIZ_MOVE_LEFT
 * \brief Horizontal move: walking left.
 *
 * \def HORIZ_MOVE_RIGHT
 * \brief Horizontal move: walking right.
 */
#define HORIZ_MOVE_NONE_L  0
#define HORIZ_MOVE_NONE_R  1
#define HORIZ_MOVE_LEFT    2
#define HORIZ_MOVE_RIGHT   3

/**
 * \def VERT_MOVE_NONE
 * \brief Vertical move: no vertical move.
 *
 * \def VERT_MOVE_IM
 * \brief Vertical move: immobile (on a ladder, but don't move).
 *
 * \def VERT_MOVE_UP
 * \brief Vertical move: ride up a ladder.
 *
 * \def VERT_MOVE_DOWN
 * \brief Vertical move: ride down a ladder.
 */
#define VERT_MOVE_NONE     0
#define VERT_MOVE_IM       1
#define VERT_MOVE_UP       2
#define VERT_MOVE_DOWN     3

/**
 * \def JUMP_NONE
 * \brief Jump: not jumping.
 *
 * \def JUMP_UP
 * \brief Jump: jumping (jump up phase).
 *
 * \def JUMP_DOWN
 * \brief Jump: jumping (jump down phase).
 */
#define JUMP_NONE 0
#define JUMP_UP   1
#define JUMP_DOWN 2


/**
 * \struct DM_Collide
 * \brief Contains informations about one collision surface.
 */
typedef struct DM_Collide DM_Collide;
struct DM_Collide
{
	int shape; /*!< The collide shape (COLLIDE_RECT, COLLIDE_LINE, COLLIDE_POINT). */
	int x1;    /*!< x1 point */
	int y1;    /*!< y1 point */
	int x2;    /*!< x2 point */
	int y2;    /*!< y2 point */
};


/**
 * \struct DM_Map
 * \brief Contains all collisions of the map.
 */
typedef struct DM_Map DM_Map;
struct DM_Map
{
	DM_Collide *platforms; /*!< Platfoms collides. */
	int platform_count;    /*!< The number of platforms. */
	DM_Collide *ladders;   /*!< Ladders collides. */
	int ladder_count;      /*!< The number of ladders. */
	DM_Collide finish;     /*!< Finish area collide. */
	int start_point_x;     /*!< Jumpman start point (x). */
	int start_point_y;     /*!< Jumpman start point (y). */
	int start_look;        /*!< Where Jumpman look at the start. */
};


/**
 * \struct DM_Jumpman
 * \brief Contains informations about Jumpman.
 */
typedef struct DM_Jumpman DM_Jumpman;
struct DM_Jumpman
{
	DM_Collide platform_collide; /*!< Collision point with platforms. */
	DM_Collide enemy_collide;    /*!< Collision rect with enemies. */
	DM_Sprite *sprite;           /*!< The sprite of Jumpman. */
	int pos_x;                   /*!< The position of Jumpman (x). */
	int pos_y;                   /*!< The position of Jumpman (y). */
	int movement;                /*!< The current movement for animation (SPRITE_*). */
};


//Some global vars
/**
 * \var JUMPMAN
 * \brief Contains all informations about Jumpman.
 */
DM_Jumpman JUMPMAN;
/**
 * \var GAME_SPEED
 * \brief The game speed (FIXME not implemented yet).
 */
int GAME_SPEED;
/**
 * \var GAME_STATE
 * \brief The game state (playing, paused,...).
 */
int GAME_STATE;
/**
 * \var JUMPMAN_LIVES
 * \brief The remaining lives of Jumpman (FIXME not implemented yet).
 */
int JUMPMAN_LIVES;


void init_game();
void update_jumpman();
int lets_play_yeah(SDL_Surface *screen, DM_Map *map);
DM_Map* load_map_infos(char *level_name);
void free_dm_map(DM_Map *map);
int check_platform_collides(DM_Collide *collide_point, DM_Map *map);
int check_ladder_collides(DM_Collide *collide_point, DM_Map *map);
int check_ladder_top_collides(DM_Collide *collide_point, DM_Map *map);
int check_ladder_bottom_collides(DM_Collide *collide_point, DM_Map *map);	
int get_collide_ladder_center(DM_Collide *collide_point, DM_Map *map);
int collide(DM_Collide *collide1, DM_Collide *collide2);
/** \cond */ //Hide the "privates" functions for Doxygen
int _collide_line_point(DM_Collide *collide1, DM_Collide *collide2);
int _collide_rect_point(DM_Collide *crect, DM_Collide *cpoint);
int _collide_rect_rect(DM_Collide *crect1, DM_Collide *crect2);
/** \endcond */


#endif //GAME_H_INCLUDED

