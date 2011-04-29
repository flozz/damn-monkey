/***************************************************************************
*                                                                          *
*  This file is part of Damn Monkey                                        *
*                                                                          *
*  Copyright (C) 2010 - 2011  Fabien LOISON, Mathilde BOUTIGNY,            *
*  Vincent PEYROUSE, Germain CARRÉ and Matthis FRENAY                      *
*                                                                          *
*  Damn Monkey is free software: you can redistribute it and/or modify     *
*  it under the terms of the GNU General Public License as published by    *
*  the Free Software Foundation, either version 3 of the License, or       *
*  (at your option) any later version.                                     *
*                                                                          *
*  This program is distributed in the hope that it will be useful,         *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
*  GNU General Public License for more details.                            *
*                                                                          *
*  You should have received a copy of the GNU General Public License       *
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
*                                                                          *
***************************************************************************/


/**
 * \file sprite.c
 * \brief This file contain the code that deal with the (animated) sprites.
 */


#include "sprite.h"


/**
 * \fn DM_Sprite* new_sprite(char *sprite_name)
 * \brief Create a new DM_Sprite
 *
 * \param sprite_name The name of the sprite file
 */
DM_Sprite* new_sprite(char *sprite_name)
{
	DM_Sprite *sprite = NULL;
	char file_name[42];
	//Memory Allocation for the new sprite
	sprite = malloc(sizeof(DM_Sprite));
	if (sprite == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//Init the Sprite items informations to -1 (== the sprite does not exists)
	int i;
	for (i=0 ; i < NUMB_SPRITE_ITEMS ; i++)
	{
		sprite->items[SPRITE_LOOK_RIGHT].n = -1;
	}
	sprite->screen_pos.x = 0;
	sprite->screen_pos.y = 0;
	sprite->current_mov = SPRITE_LOOK_RIGHT;
	sprite->prev_mov = -1;
	//Load the image
	strcpy(file_name, sprite_name);
	strcat(file_name, ".png");
	sprite->sprite = load_resource(file_name);
	//Load the sprite informations
	//TODO: parser
	//FIXME /!\ Hardcoded values !
	sprite->items[SPRITE_LOOK_RIGHT].x = 0;
	sprite->items[SPRITE_LOOK_RIGHT].y = 0;
	sprite->items[SPRITE_LOOK_RIGHT].w = 60;
	sprite->items[SPRITE_LOOK_RIGHT].h = 60;
	sprite->items[SPRITE_LOOK_RIGHT].n = 1;
	sprite->items[SPRITE_LOOK_RIGHT].d = 0;

	sprite->items[SPRITE_WALK_RIGHT].x = 60;
	sprite->items[SPRITE_WALK_RIGHT].y = 0;
	sprite->items[SPRITE_WALK_RIGHT].w = 60;
	sprite->items[SPRITE_WALK_RIGHT].h = 60;
	sprite->items[SPRITE_WALK_RIGHT].n = 8;
	sprite->items[SPRITE_WALK_RIGHT].d = 60;

	sprite->items[SPRITE_LOOK_LEFT].x = 0;
	sprite->items[SPRITE_LOOK_LEFT].y = 60;
	sprite->items[SPRITE_LOOK_LEFT].w = 60;
	sprite->items[SPRITE_LOOK_LEFT].h = 60;
	sprite->items[SPRITE_LOOK_LEFT].n = 1;
	sprite->items[SPRITE_LOOK_LEFT].d = 0;

	sprite->items[SPRITE_WALK_LEFT].x = 60;
	sprite->items[SPRITE_WALK_LEFT].y = 60;
	sprite->items[SPRITE_WALK_LEFT].w = 60;
	sprite->items[SPRITE_WALK_LEFT].h = 60;
	sprite->items[SPRITE_WALK_LEFT].n = 8;
	sprite->items[SPRITE_WALK_LEFT].d = 60;
	//Return the DM_Sprite
	return sprite;
}


/**
 * \fn void free_sprite(DM_Sprite *sprite)
 * \brief Free the memory of a DM_Sprite
 *
 * \param sprite The DM_Sprite to free
 */
void free_sprite(DM_Sprite *sprite)
{
	SDL_FreeSurface(sprite->sprite);
	free(sprite);
}


/**
 * \fn void sprite_cb(void *object, SDL_Surface *screen)
 * \brief Callback function for blitting DM_Sprite
 *
 * \param object The DM_Sprite to blit
 * \param screen The main surface.
 */
void sprite_cb(void *object, SDL_Surface *screen)
{
	DM_Sprite *sprite = object;
	//Init if necessary
	if (sprite->current_mov != sprite->prev_mov)
	{
		sprite->prev_mov = sprite->current_mov;
		sprite->step = 0;
		sprite->image_pos.w = sprite->items[sprite->current_mov].w;
		sprite->image_pos.y = sprite->items[sprite->current_mov].y;
		sprite->image_pos.h = sprite->items[sprite->current_mov].h;
		sprite->screen_pos.w = sprite->items[sprite->current_mov].w;
		sprite->screen_pos.w = sprite->items[sprite->current_mov].w;
		sprite->last_step_change = SDL_GetTicks();
	}
	//Select the current image
	sprite->image_pos.x = sprite->items[sprite->current_mov].x \
						  + sprite->items[sprite->current_mov].w * sprite->step;
	//blit the image
	SDL_BlitSurface(sprite->sprite, &sprite->image_pos, screen, &sprite->screen_pos);
	//Increment the step
	if (SDL_GetTicks() - sprite->last_step_change >=  sprite->items[sprite->current_mov].d)
	{
		sprite->step += 1;
		if (sprite->step >= sprite->items[sprite->current_mov].n)
		{
			sprite->step = 0;
		}
		sprite->last_step_change = SDL_GetTicks();
	}
}


//FIXME: to remove
void sprite_test()
{
	DM_Sprite *jumpman = new_sprite("jumpman");
	int jumpman_refresh = ref_object(&layer_active, jumpman, sprite_cb);
	int stop = 0;
	SDL_Event event;
	SDL_EnableKeyRepeat(3, 3);
	while (!stop)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					stop = 1;
					break;
				case SDLK_LEFT:
					jumpman->current_mov = SPRITE_WALK_LEFT;
					jumpman->screen_pos.x -=1;
					break;
				case SDLK_RIGHT:
					jumpman->current_mov = SPRITE_WALK_RIGHT;
					jumpman->screen_pos.x +=1;
					break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					jumpman->current_mov = SPRITE_LOOK_LEFT;
					break;
				case SDLK_RIGHT:
					jumpman->current_mov = SPRITE_LOOK_RIGHT;
					break;
			}
		}
	}
	deref_object(&layer_active, jumpman_refresh);
	SDL_Delay(20);
	free_sprite(jumpman);
}


