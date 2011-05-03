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
	char path[42] = "";
	int action;
	sprintf(path, "pixmaps/%s.sprite", sprite_name);
	DM_Splited *sprite_infos = read_file(path);
	for (i=0 ; i<sprite_infos->items_int ; i++)
	{
		action = -1;
		if (sprite_infos->lines_array[i]->parameters_int == 7)
		{
			if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "look-right"))
			{
				action = SPRITE_LOOK_RIGHT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "walk-right"))
			{
				action = SPRITE_WALK_RIGHT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "look-left"))
			{
				action = SPRITE_LOOK_LEFT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "walk-left"))
			{
				action = SPRITE_WALK_LEFT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "jump-right"))
			{
				action = SPRITE_JUMP_RIGHT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "jump-left"))
			{
				action = SPRITE_JUMP_LEFT;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "ladder"))
			{
				action = SPRITE_LADDER;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "walk-ladder"))
			{
				action = SPRITE_WALK_LADDER;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "dead"))
			{
				action = SPRITE_DEAD;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "throw-barrel"))
			{
				action = SPRITE_THROW_BARREL;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "ask-help"))
			{
				action = SPRITE_ASK_HELP;
			}
			else if (!strcmp(sprite_infos->lines_array[i]->parameters[0], "custom"))
			{
				action = SPRITE_CUSTOM;
			}

			if (action >= 0)
			{
				sprite->items[action].x = atoi(sprite_infos->lines_array[i]->parameters[1]) + 1;
				sprite->items[action].y = atoi(sprite_infos->lines_array[i]->parameters[2]) + 1;
				sprite->items[action].w = atoi(sprite_infos->lines_array[i]->parameters[3]);
				sprite->items[action].h = atoi(sprite_infos->lines_array[i]->parameters[4]);
				sprite->items[action].n = atoi(sprite_infos->lines_array[i]->parameters[5]);
				sprite->items[action].d = atoi(sprite_infos->lines_array[i]->parameters[6]);
			}
		}
	}
	//Free the memory
	free_dm_splited(sprite_infos);
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


