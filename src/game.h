#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


/**
 * \file game.h
 * \brief The header file of game.c.
 */


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


#define COLLIDE_RECT  0
#define COLLIDE_LINE  1
#define COLLIDE_POINT 2

#define GAME_STATE_NONE            0
#define GAME_STATE_PLAYING         1
#define GAME_STATE_PAUSED          2
#define GAME_STATE_LEVEL_COMPLETED 3
#define GAME_STATE_LIFE_LOST       4
#define GAME_STATE_OVER            5

#define HORIZ_MOVE_NONE_L  0
#define HORIZ_MOVE_NONE_R  1
#define HORIZ_MOVE_LEFT    2
#define HORIZ_MOVE_RIGHT   3

#define JUMP_NONE 0
#define JUMP_UP   1
#define JUMP_DOWN 2


/**
 * \struct DM_Collide
 * \brief Contain informations about one collision surface.
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
 * \struct DM_Collide
 * \brief Contain all collisions of the map.
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
 * \brief Contain informations about Jumpman.
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
	int start_pos_x;             /*!< The start point of Jumpman (x). */
	int start_pos_y;             /*!< The start point of Jumpman (y). */
	int start_move;              /*!< The start movement of Jumpman (SPRITE_LOOK_RIGHT or SPRITE_LOOK_LEFT). */
};


DM_Jumpman JUMPMAN;
int GAME_SPEED;
int GAME_STATE;


void init_game();
void update_jumpman();
void lets_play_yeah();
DM_Map* load_map_infos(char *level_name);
void free_dm_map(DM_Map *map);
int collide(DM_Collide *collide1, DM_Collide *collide2);
int _collide_line_point(DM_Collide *collide1, DM_Collide *collide2);

#endif //GAME_H_INCLUDED

