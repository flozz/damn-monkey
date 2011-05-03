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

#include "main_functions.h"
#include "parser.h"


#define NUMB_SPRITE_ITEMS 12

#define SPRITE_LOOK_RIGHT    0 //look-right   (jumpman, barrel)
#define SPRITE_WALK_RIGHT    1 //walk-right   (jumpman, barrel)
#define SPRITE_LOOK_LEFT     2 //look-left    (jumpman)
#define SPRITE_WALK_LEFT     3 //walk-left    (jumpman)
#define SPRITE_JUMP_RIGHT    4 //jump-right   (jumpman)
#define SPRITE_JUMP_LEFT     5 //jump-left    (jumpman)
#define SPRITE_LADDER        6 //ladder       (jumpman)
#define SPRITE_WALK_LADDER   7 //walk-ladder  (jumpman)
#define SPRITE_DEAD          8 //dead         (jumpman)
#define SPRITE_THROW_BARREL  9 //throw-barrel (dk)
#define SPRITE_ASK_HELP     10 //ask-help     (lady)
#define SPRITE_CUSTOM       11 //custom       (any animated object)


/**
 * \struct DM_Sprite_item
 * \brief This structure contain all the informations about a single animation.
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
 * \brief Contain all the animations of a sprite file.
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
};


DM_Sprite* new_sprite(char *sprite_name);
void free_sprite(DM_Sprite *sprite);
void sprite_cb(void *object, SDL_Surface *screen);


#endif //SPRITE_H_INCLUDED

