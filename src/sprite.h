#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED


/**
 * \file sprite.h
 * \brief The header file of sprite.c.
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

#include "refresh.h" //FIXME
#include "main_functions.h"


#define NUMB_SPRITE_ITEMS 4
#define SPRITE_LOOK_RIGHT 0
#define SPRITE_WALK_RIGHT 1
#define SPRITE_LOOK_LEFT  2
#define SPRITE_WALK_LEFT  3


/**
 * \struct DM_Sprite_item
 * \brief TODO.
 */
typedef struct DM_Sprite_item DM_Sprite_item;
struct DM_Sprite_item
{
	int x;  /*!< The x position of the first image. */
	int y;  /*!< The y position of the first image. */
	int w;  /*!< The width of an image. */
	int h;  /*!< The height of an image. */
	int n;  /*!< The number of images for this item. */
	int d;  /*!< The delay between two moves. */
};


/**
 * \struct DM_Sprite
 * \brief TODO.
 */
typedef struct DM_Sprite DM_Sprite;
struct DM_Sprite
{
	SDL_Surface *sprite;        /*!< The sprite SDL_Surface. */
	DM_Sprite_item items[NUMB_SPRITE_ITEMS];    /*!< The item list. */
	SDL_Rect screen_pos;        /*!< The position of the sprite on the screen. */
	SDL_Rect image_pos;         /*!< The position of the image in the sprite. */
	int current_mov;
	int prev_mov;
	int step;
	int last_step_change;
	//TODO : jump, lader, death
};


DM_Sprite* new_sprite(char *sprite_name);
void free_sprite(DM_Sprite *sprite);
void sprite_cb(void *object, SDL_Surface *screen);
void sprite_test(); //FIXME


#endif //SPRITE_H_INCLUDED

