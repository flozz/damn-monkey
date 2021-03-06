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
 * \file level_01.c
 * \brief This is the code of the first level of Damn Monkey.
 */


#include "level_01.h"


/**
 * \fn void barrel_init(SDL_Surface *screen)
 * \brief Initialize the barrel refresh
 *
 * \param screen The main SDL_Surface.
 */
void barrel_init(SDL_Surface *screen)
{
	barrel_timer = SDL_AddTimer(20, _barrel_cb, NULL);
}


/**
 * \fn void barrel_destroy()
 * \brief Stop the refresh
 */
void barrel_destroy()
{
	SDL_RemoveTimer(barrel_timer);
}


/**
 * \fn int ref_barrel(void *object, void (*callback)())
 * \brief Add a barrel to the refresh list.
 *
 * \param object A pointer on the object
 * \param callback The callback function that will be called for blitting the
 *                 object. This function must have a prototype that looks
 *                 like that:
 * \code
 * void function_name(void *object, SDL_Surface *screen);
 * \endcode
 * 
 * \return The id of the refresh item.
 */
int ref_barrel(void *object, void (*callback)())
{
	int barrel_id = ref_object(&LAYER_ACTIVE, object, callback);
	return barrel_id;
}


/**
 * \fn void deref_barrel(int id)
 * \brief Dereference a barrel.
 *
 * \param id The identifier of the object.
 */
void deref_barrel(int id)
{
	deref_object(&LAYER_ACTIVE, id);
}


/** \cond */ //Hide the "privates" functions to Doxygen

//Callback function for the barrel_timer
Uint32 _barrel_cb(Uint32 interval, void *arg)
{
	if (GAME_STATE != GAME_STATE_PAUSED)
	{
		int i;
		//Every 'turn' we check every barrel
		for (i=0 ; i<BARRELS->numb_items ; i++)
		{
			if (BARRELS->barrels[i].sprite->screen_pos.x > 780 \
					|| BARRELS->barrels[i].sprite->screen_pos.y > 550)
			{
				//The barrel is at the level end, we dereference it and replace
				//at the level beginning
				deref_barrel(BARRELS->barrels[i].refresh_id);
				BARRELS->barrels[i].refresh_id = -1; 
				SDL_Delay(50);
				BARRELS->barrels[i].sprite->screen_pos.x = 0;
				BARRELS->barrels[i].sprite->screen_pos.y = 150;
			}
			else if (BARRELS->barrels[i].sprite->screen_pos.x == 150 \
					&& BARRELS->barrels[i].sprite->screen_pos.y == 150)
			{
				//The barrel is after Donkey Kong, we reference it and show it
				BARRELS->barrels[i].refresh_id = ref_barrel(
						&BARRELS->barrels[i],
						barrel_cb
						);
			}
			else if (BARRELS->barrels[i].sprite->screen_pos.x < 150 \
					&& BARRELS->barrels[i].sprite->screen_pos.y == 150)
			{
				//The barrel is waiting to being launched
				if (BARRELS->barrels[BARRELS->last_sent].sprite->screen_pos.y \
						>= 180 - 8 * GAME_SPEED - 5)
				{
					BARRELS->damnmonkey->current_mov = SPRITE_THROW_BARREL;
				}
				if (BARRELS->barrels[BARRELS->last_sent].sprite->screen_pos.y \
						>= 180 - 8 * GAME_SPEED)
				{
					//The last barrel is already sent with an enough offset,
					//we can launch the next one.
					BARRELS->damnmonkey->current_mov = SPRITE_CUSTOM;
					BARRELS->last_sent = i;
					BARRELS->barrels[i].sprite->screen_pos.x = 150;
				}
			}
		}
		return refresh_cb(interval, &LAYER_ACTIVE);
	}
	return interval;
}

/** \endcond */


/**
 * \fn void barrel_cb(void *object, SDL_Surface *screen)
 * \brief Callback function for blitting DM_Barrel
 *
 * \param object The DM_Barrel to blit.
 * \param screen The main surface.
 */
void barrel_cb(void *object, SDL_Surface *screen)
{
	if (GAME_STATE != GAME_STATE_PAUSED)
	{
		DM_Barrel *barrel = object;
		
		//Damn Monkey collide initialisation
		DM_Collide damnmonkey_collide;
		damnmonkey_collide.shape = COLLIDE_RECT;
		damnmonkey_collide.x1 = BARRELS->damnmonkey->screen_pos.x;
		damnmonkey_collide.y1 = BARRELS->damnmonkey->screen_pos.y;
		damnmonkey_collide.x2 = BARRELS->damnmonkey->screen_pos.x + \
								BARRELS->damnmonkey->screen_pos.w;
		damnmonkey_collide.y2 = BARRELS->damnmonkey->screen_pos.y + \
								BARRELS->damnmonkey->screen_pos.h;
		
		if (!collide(&barrel->jumpman_collide, &JUMPMAN.enemy_collide) \
				&& !collide(&JUMPMAN.enemy_collide, &damnmonkey_collide))
		{
			//There's no collision between Jumpman and a barrel
			if (check_ladder_top_collides(&barrel->platform_collide, barrel->map) \
					&& barrel->platform_collide.x1 == get_collide_ladder_center(
						&barrel->platform_collide, barrel->map
						)
					)
			{
				//The barrel is on a ladder, random fall on the ladder
				if (rand()%2)
				{
					barrel->sprite->current_mov = SPRITE_WALK_LADDER;
					barrel->sprite->screen_pos.y = barrel->sprite->screen_pos.y \
												   + 4;
				}
				else
				{
					//Movement continuation
					if (barrel->sprite->current_mov != SPRITE_WALK_LEFT)
					{
						barrel->sprite->screen_pos.x++;
					}
					else
					{
						barrel->sprite->screen_pos.x--;
					}
				}
			}
			else
			{
				//The barrel isn't on a ladder so we check if it is in
				//collision with a platform
				if (check_platform_collides(&barrel->platform_collide, barrel->map))
				{
					//We generate the good movement according to the gravity
					barrel->sprite->current_mov = check_platform_orientation(
							&barrel->platform_collide,
							barrel->map
							);
					if (barrel->sprite->current_mov != SPRITE_WALK_LEFT)
					{
						barrel->sprite->screen_pos.x++;
					}
					else
					{
						barrel->sprite->screen_pos.x--;
					}
				}
				else
				{
					//No collision : the barrel is falling/descending
					barrel->sprite->screen_pos.y++;
				}
			}
			
			//Collision rect and point update
			barrel->jumpman_collide.x1 = barrel->sprite->screen_pos.x + 2;
			barrel->jumpman_collide.y1 = barrel->sprite->screen_pos.y + 2;
			barrel->jumpman_collide.x2 = barrel->jumpman_collide.x1 + barrel->sprite->items[barrel->sprite->current_mov].w - 4;
			barrel->jumpman_collide.y2 = barrel->jumpman_collide.y1 + barrel->sprite->items[barrel->sprite->current_mov].w - 4;
			barrel->platform_collide.x1 = barrel->jumpman_collide.x1 + (barrel->sprite->items[barrel->sprite->current_mov].w / 2);
			barrel->platform_collide.y1 = barrel->jumpman_collide.y1 + barrel->sprite->items[barrel->sprite->current_mov].h;

		}
		else
		{
			//There's a collision between Jumpman and a barrel => A life lost
			GAME_STATE = GAME_STATE_LIFE_LOST;
		}
		//Call of sprite_cb in order to update the screen
		sprite_cb(barrel->sprite, screen);
	}
}


/**
 * \fn int check_platform_orientation(DM_Collide *collide_point, DM_Map *map)
 * \brief Function for checking platform orientation
 *
 * \param collide_point The barrel collide point to check.
 * \param map The pointer to the DM_Map structure.
 *
 * \return int The barrel movement corresponding to the platform orientation.
 */
int check_platform_orientation(DM_Collide *collide_point, DM_Map *map)
{
	int i;
	for (i=0 ; i<map->platform_count ; i++)
	{
		//The collide function allow us to find the barrel which is considered
		if (collide(collide_point, &map->platforms[i]))
		{
			if (map->platforms[i].x1 < map->platforms[i].x2 \
					&& map->platforms[i].y1 > map->platforms[i].y2)
			{
				return SPRITE_WALK_LEFT;
			}
			else if (map->platforms[i].x1 < map->platforms[i].x2 \
					&& map->platforms[i].y1 < map->platforms[i].y2)
			{
				return SPRITE_WALK_RIGHT;
			}
			else if (map->platforms[i].x1 > map->platforms[i].x2 \
					&& map->platforms[i].y1 > map->platforms[i].y2)
			{
				return SPRITE_WALK_RIGHT;
			}
			else if (map->platforms[i].x1 > map->platforms[i].x2 \
					&& map->platforms[i].y1 < map->platforms[i].y2)
			{
				return SPRITE_WALK_LEFT;
			}
			else if (map->platforms[i].y1 == map->platforms[i].y2)
			{
				return SPRITE_WALK_RIGHT;
			}
		}
	}
	return 42;
}


/**
 * \fn void free_dm_barrel(DM_Barrel *barrels)
 * \brief Releases the memory of a DM_Barrel pointer.
 *
 * \param splited The DM_Barrel pointer to free.
 */
void free_dm_barrel(DM_Barrel *barrel)
{
	//We don't deallocate the map pointer because it'll be freed later
	free_sprite(barrel->sprite);
}


/**
 * \fn void level_01(SDL_Surface *screen)
 * \brief Play to the first level.
 *
 * \param screen The main surface (called screen in the main() function).
 */
void level_01(SDL_Surface *screen)
{
	//Load the level infos (collides,...)
	DM_Map *map = load_map_infos("level_01");
	
	//Load and play level music
	Mix_Music *level_music = load_music_resource("game.ogg");
	Mix_PlayMusic(level_music, -1);

	//Load barrels and launch the barrel timer
	int i;
	int barrels_nb = 20;
	BARRELS = malloc(sizeof(DM_Barrel_Array));
	BARRELS->numb_items = barrels_nb;
	BARRELS->last_sent = 0;
	BARRELS->barrels = malloc(BARRELS->numb_items * sizeof(DM_Barrel));
	for (i=0 ; i<BARRELS->numb_items ; i++)
	{
		BARRELS->barrels[i].map = map;
		BARRELS->barrels[i].sprite = new_sprite("barrel");
		BARRELS->barrels[i].sprite->current_mov = SPRITE_WALK_RIGHT;
		BARRELS->barrels[i].sprite->screen_pos.x = 0;
		BARRELS->barrels[i].sprite->screen_pos.y = 150;
		BARRELS->barrels[i].jumpman_collide.shape = COLLIDE_RECT;
		BARRELS->barrels[i].jumpman_collide.x1 = BARRELS->barrels[i].sprite->screen_pos.x + 2;
		BARRELS->barrels[i].jumpman_collide.y1 = BARRELS->barrels[i].sprite->screen_pos.y + 2;
		BARRELS->barrels[i].jumpman_collide.x2 = BARRELS->barrels[i].jumpman_collide.x1 + \
												  BARRELS->barrels[i].sprite->items[BARRELS->barrels[i].sprite->current_mov].w - 4;
		BARRELS->barrels[i].jumpman_collide.y2 = BARRELS->barrels[i].jumpman_collide.x1 + \
												  BARRELS->barrels[i].sprite->items[BARRELS->barrels[i].sprite->current_mov].h - 4;
		BARRELS->barrels[i].platform_collide.shape = COLLIDE_POINT;
		BARRELS->barrels[i].platform_collide.x1 = BARRELS->barrels[i].jumpman_collide.x1 \
												   + (BARRELS->barrels[i].sprite->screen_pos.w / 2);
		BARRELS->barrels[i].platform_collide.y1 = BARRELS->barrels[i].jumpman_collide.y1 \
												   + (BARRELS->barrels[i].sprite->screen_pos.h);
		BARRELS->barrels[i].platform_collide.x2 = 0;
		BARRELS->barrels[i].platform_collide.y2 = 0;
		BARRELS->barrels[i].refresh_id = -1;
	}
	BARRELS->barrels[0].sprite->screen_pos.x = 150;

	//Load Damn Monkey
	BARRELS->damnmonkey = new_sprite("damnmonkey");
	BARRELS->damnmonkey->screen_pos.x = 55;
	BARRELS->damnmonkey->screen_pos.y = 94;
	BARRELS->damnmonkey->current_mov = SPRITE_CUSTOM;

	//Level launch
	barrel_init(screen);
	introduction(screen);
	
	//Load the background
	DM_Surface *level_surface = load_resource_as_dm_surface("level_01.png");
	int level_surface_refresh = ref_object(
										   &LAYER_BG,
										   level_surface,
										   surface_refresh_cb
										   );
	
	//Load Lady and help sprites and show Damn Monkey
	DM_Sprite *lady = new_sprite("lady");
	lady->current_mov = SPRITE_ASK_HELP;
	lady->screen_pos.x = 300;
	lady->screen_pos.y = 48;
	int lady_refresh = ref_object(&LAYER_ACTIVE, lady, sprite_cb);
	DM_Sprite *help = new_sprite("help");
	help->current_mov = SPRITE_CUSTOM;
	help->screen_pos.x = 340;
	help->screen_pos.y = 10;
	int help_refresh = ref_object(&LAYER_ACTIVE, help, sprite_cb);
	int damnmonkey_refresh = ref_object(
										&LAYER_ACTIVE,
										BARRELS->damnmonkey,
										sprite_cb
										);
	
	lets_play_yeah(screen, map);
	//Dereference objects and free the memory
	barrel_destroy();
	for(i=0 ; i<BARRELS->numb_items ; i++)
	{
		deref_barrel(BARRELS->barrels[i].refresh_id);
	}
	deref_object(&LAYER_ACTIVE, damnmonkey_refresh);
	deref_object(&LAYER_ACTIVE, help_refresh);
	deref_object(&LAYER_ACTIVE, lady_refresh);
	deref_object(&LAYER_BG, level_surface_refresh);
	SDL_Delay(50);
	Mix_FreeMusic(level_music);
	for(i=0 ; i<BARRELS->numb_items ; i++)
	{
		free_dm_barrel(&BARRELS->barrels[i]);
	}
	free_sprite(BARRELS->damnmonkey);
	free(BARRELS);
	free_sprite(help);
	free_sprite(lady);
	free_dm_surface(level_surface);	
	free_dm_map(map);
}


/**
 * \fn void introduction(SDL_Screen *surface)
 * \brief Show the level intro.
 *
 * Show a introduction screen before the level beginning
 *
 * \param screen The main surface (called screen in the main() function). 
 */
void introduction(SDL_Surface *screen)
{
	DM_Surface *bg = load_resource_as_dm_surface("level_01_begin.png");
	int bg_refresh = ref_object(&LAYER_FG, bg, surface_refresh_cb);
	
	DM_Surface *title = malloc(sizeof(DM_Surface));
	title->surface = str_to_surface("font_main.png", "LEVEL 01");
	title->rect.w = title->surface->w;
	title->rect.h = title->surface->h;
	title->rect.x = 75;
	title->rect.y = 450;
	int title_refresh = ref_object(&LAYER_FG, title, surface_refresh_cb);
	
	DM_Surface *level = malloc(sizeof(DM_Surface));
	char buffer[6];
	sprintf(buffer, "%i m", 25 * (GAME_SPEED + 1));
	level->surface = str_to_surface("font_main.png", buffer);
	level->rect.w = level->surface->w;
	level->rect.h = level->surface->h;
	level->rect.x = 100;
	level->rect.y = 500;
	int level_refresh = ref_object(&LAYER_FG, level, surface_refresh_cb);
	
	DM_Surface *life = load_resource_as_dm_surface("life.png");
	life->rect.x = 100;
	life->rect.y = 550;
	int life_refresh = ref_object(&LAYER_FG, life, surface_refresh_cb);
	DM_Surface *life_text = malloc(sizeof(DM_Surface));
	char life_char[3];
	sprintf(life_char, "x%d", JUMPMAN_LIVES);
	life_text->surface = str_to_surface("font_main.png", life_char);
	life_text->rect.w = life_text->surface->w;
	life_text->rect.h = life_text->surface->h;
	life_text->rect.x = life->rect.x + life->rect.w + 5;
	life_text->rect.y = life->rect.y;
	int life_text_refresh = ref_object(&LAYER_FG, life_text, surface_refresh_cb);
	
	DM_Sprite *damnmonkey = new_sprite("damnmonkey");
	damnmonkey->current_mov = SPRITE_WALK_LADDER;
	damnmonkey->screen_pos.x = 400;
	damnmonkey->screen_pos.y = 601;
	int damnmonkey_refresh = ref_object(&LAYER_FG, damnmonkey, sprite_cb);
	SDL_Delay(1000);
	while (damnmonkey->screen_pos.y >= 53)
	{
		damnmonkey->screen_pos.y -= 2;
		SDL_Delay(20);
	}
	damnmonkey->current_mov = SPRITE_CUSTOM;
	damnmonkey->screen_pos.x = 470;
	
	DM_Sprite *lady = new_sprite("lady");
	lady->current_mov = SPRITE_ASK_HELP;
	lady->screen_pos.x = 570;
	lady->screen_pos.y = 90;
	int lady_refresh = ref_object(&LAYER_FG, lady, sprite_cb);
	
	DM_Sprite *help = new_sprite("help");
	help->current_mov = SPRITE_CUSTOM;
	help->screen_pos.x = 610;
	help->screen_pos.y = 45;
	int help_refresh = ref_object(&LAYER_FG, help, sprite_cb);
    
	SDL_Delay(2000);
	//Derefence objects and free the memory
	deref_object(&LAYER_FG, life_refresh);
	deref_object(&LAYER_FG, life_text_refresh);
	deref_object(&LAYER_FG, help_refresh);
	deref_object(&LAYER_FG, lady_refresh);
	deref_object(&LAYER_FG, damnmonkey_refresh);
	deref_object(&LAYER_FG, level_refresh);
	deref_object(&LAYER_FG, title_refresh);
	deref_object(&LAYER_FG, bg_refresh);
	SDL_Delay(50);
	free_dm_surface(life);
	free_dm_surface(life_text);
	free_sprite(help);
	free_sprite(lady);
	free_sprite(damnmonkey);
	free_dm_surface(level);
	free_dm_surface(title);
	free_dm_surface(bg);
}


