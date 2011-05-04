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
 * \file game.c
 * \brief TODO
 */


#include "game.h"


/**
 * \fn void init_game()
 * \brief Initialize the game. Must be called only one time in the program.
 */
void init_game()
{
	//Init game vars
	GAME_SPEED = 1;
	GAME_STATE = GAME_STATE_NONE;
	//Init jumpman
	JUMPMAN.start_pos_x = 42;
	JUMPMAN.start_pos_y = 42;
	JUMPMAN.start_move = SPRITE_LOOK_RIGHT;
	JUMPMAN.pos_x = 0;
	JUMPMAN.pos_y = 0;
	JUMPMAN.movement = SPRITE_LOOK_RIGHT;
	JUMPMAN.sprite = new_sprite("jumpman");
	JUMPMAN.platform_collide.shape = COLLIDE_POINT;
	JUMPMAN.platform_collide.x2 = 0;
	JUMPMAN.platform_collide.y2 = 0;
	JUMPMAN.platform_collide.shape = COLLIDE_POINT;
	JUMPMAN.enemy_collide.shape = COLLIDE_RECT;
	update_jumpman();
}


/**
 * \fn void update_jumpman()
 * \brief Update all the informations about Jumman (collides points, position,...)
 */
void update_jumpman()
{
	//Check the Jumpman posision
	if (JUMPMAN.pos_x <= 0)
	{
		JUMPMAN.pos_x = 1;
	}
	else if (JUMPMAN.pos_y <= 0)
	{
		JUMPMAN.pos_y = 1;
	}
	else if (JUMPMAN.pos_x > (800 - JUMPMAN.sprite->items[JUMPMAN.movement].w))
	{
		JUMPMAN.pos_x = 800 - JUMPMAN.sprite->items[JUMPMAN.movement].w;
	}
	else if (JUMPMAN.pos_y > (600 - JUMPMAN.sprite->items[JUMPMAN.movement].h))
	{
		JUMPMAN.pos_y = 600 - JUMPMAN.sprite->items[JUMPMAN.movement].h;
	}
	//Push the variables in the DM_Sprite object
	JUMPMAN.sprite->screen_pos.x = JUMPMAN.pos_x;
	JUMPMAN.sprite->screen_pos.y = JUMPMAN.pos_y;
	JUMPMAN.sprite->current_mov = JUMPMAN.movement;
	//Update the collide point and rect
	if (JUMPMAN.sprite->items[JUMPMAN.movement].n > 0)
	{ 
		//Platform collide point
		JUMPMAN.platform_collide.x1 = JUMPMAN.pos_x + JUMPMAN.sprite->items[JUMPMAN.movement].w / 2;
		JUMPMAN.platform_collide.y1 = JUMPMAN.pos_y + JUMPMAN.sprite->items[JUMPMAN.movement].h;
		//Enemies collide rect
		JUMPMAN.enemy_collide.x1 = JUMPMAN.pos_x;
		JUMPMAN.enemy_collide.y1 = JUMPMAN.pos_y;
		JUMPMAN.enemy_collide.x2 = JUMPMAN.pos_x + JUMPMAN.sprite->items[JUMPMAN.movement].w;
		JUMPMAN.enemy_collide.y2 = JUMPMAN.pos_y + JUMPMAN.sprite->items[JUMPMAN.movement].h;
	}
	else
	{
		//Platform collide point
		JUMPMAN.platform_collide.x1 = 0;
		JUMPMAN.platform_collide.y1 = 0;
		//Enemies collide rect
		JUMPMAN.enemy_collide.x1 = 0;
		JUMPMAN.enemy_collide.y1 = 0;
		JUMPMAN.enemy_collide.x2 = 0;
		JUMPMAN.enemy_collide.y2 = 0;
	}
}


//TODO
void lets_play_yeah() {
	//Enable the key repetition
	SDL_EnableKeyRepeat(0, 0);
	//Initialize the GAME_STATE variable
	GAME_STATE = GAME_STATE_PLAYING;
	//Set the start position of jumpman
	JUMPMAN.movement = JUMPMAN.start_move;
	JUMPMAN.pos_x = JUMPMAN.start_pos_x + JUMPMAN.sprite->items[JUMPMAN.movement].w / 2;
	JUMPMAN.pos_y = JUMPMAN.start_pos_y + JUMPMAN.sprite->items[JUMPMAN.movement].h;
	update_jumpman();
	//Reference Jumman in the global refresh
	int jumpman_refresh = ref_object(&layer_active, JUMPMAN.sprite, sprite_cb);
	//some vars
	int horiz_move;
	if (JUMPMAN.start_move == SPRITE_LOOK_LEFT)
	{
		horiz_move = HORIZ_MOVE_NONE_L;
	}
	else
	{
		horiz_move = HORIZ_MOVE_NONE_R;
	}
	int jump = JUMP_NONE;
	SDL_Event event;

	//The main loop of the game
	while (GAME_STATE == GAME_STATE_PLAYING || GAME_STATE == GAME_STATE_PAUSED)
	{
		if (SDL_PollEvent(&event) && GAME_STATE == GAME_STATE_PLAYING)
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: //FIXME call the pause menu
						GAME_STATE = GAME_STATE_NONE; //STOP
						break;
					case SDLK_LEFT:
						horiz_move = HORIZ_MOVE_LEFT;
						break;
					case SDLK_RIGHT:
						horiz_move = HORIZ_MOVE_RIGHT;
						break;
					case SDLK_SPACE:
						if (!jump) 
						{
							jump = JUMP_UP;
						}
						break;
					default:
						break;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
						if (horiz_move == HORIZ_MOVE_LEFT || horiz_move == HORIZ_MOVE_NONE_R)
						{
							horiz_move = HORIZ_MOVE_NONE_L;
						}
						break;
					case SDLK_RIGHT:
						if (horiz_move == HORIZ_MOVE_RIGHT || horiz_move == HORIZ_MOVE_NONE_L)
						{
							horiz_move = HORIZ_MOVE_NONE_R;
						}
						break;
					default:
						break;
				}
			}
		}
		//Update jumpman position
		if (!jump)
		{
			if (horiz_move == HORIZ_MOVE_LEFT) {
				JUMPMAN.movement = SPRITE_WALK_LEFT;
				JUMPMAN.pos_x -= 1;
			}
			else if (horiz_move == HORIZ_MOVE_NONE_L) {
				JUMPMAN.movement = SPRITE_LOOK_LEFT;
			}
			else if (horiz_move == HORIZ_MOVE_RIGHT) {
				JUMPMAN.movement = SPRITE_WALK_RIGHT;
				JUMPMAN.pos_x += 1;
			}
			else if (horiz_move == HORIZ_MOVE_NONE_R) {
				JUMPMAN.movement = SPRITE_LOOK_RIGHT;
			}
		}
		else
		{
			if (horiz_move == HORIZ_MOVE_LEFT) {
				JUMPMAN.movement = SPRITE_JUMP_LEFT;
				JUMPMAN.pos_x -= 1;
			}
			else if (horiz_move == HORIZ_MOVE_NONE_L) {
				JUMPMAN.movement = SPRITE_JUMP_LEFT;
			}
			else if (horiz_move == HORIZ_MOVE_RIGHT) {
				JUMPMAN.movement = SPRITE_JUMP_RIGHT;
				JUMPMAN.pos_x += 1;
			}
			else if (horiz_move == HORIZ_MOVE_NONE_R) {
				JUMPMAN.movement = SPRITE_JUMP_RIGHT;
			}

			if (jump == JUMP_UP)
			{
				//TODO
			}
			else
			{
				//TODO
			}
		}
		//TODO gravity
		//Update Jumpman
		update_jumpman();
		SDL_Delay(5);
	}

	//TODO Make something for every GAME_STATE

	//Dereference Jumpman
	deref_object(&layer_active, jumpman_refresh);
}


/**
 * \fn DM_Map* load_map_infos(char *level_name)
 * \brief Load the level informations from a .map file.
 *
 * \param level_name The name of the level (e.g. "level_01")
 *
 * \return Returns the DM_Map.
 */
DM_Map* load_map_infos(char *level_name)
{
	int ladder_count = 0;
	int platform_count = 0;
	DM_Map *map = malloc(sizeof(DM_Map));
	if (map == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	char path[42] = "";
	sprintf("levels/%s.map", level_name);
	DM_Splited *map_infos = read_file(path);
	//Count the platforms and the ladders
	int i;
	for (i=0 ; i<map_infos->items_int ; i++)
	{
		if (map_infos->lines_array[i]->parameters_int == 5)
		{
			if (strcmp(map_infos->lines_array[i]->parameters[0], "platform-collide"))
			{
				platform_count++;
			}
			else if (strcmp(map_infos->lines_array[i]->parameters[0], "ladder-collide"))
			{
				ladder_count++;
			}
		}
	}
	//Initialize the DM_Map
	map->platforms = malloc(platform_count * sizeof(DM_Collide));
	map->platform_count = platform_count;
	map->ladders = malloc(ladder_count * sizeof(DM_Collide));
	map->ladder_count = ladder_count;
	map->finish.shape = COLLIDE_RECT;
	map->finish.x1 = 0;
	map->finish.y1 = 0;
	map->finish.x2 = 0;
	map->finish.y2 = 0;
	map->start_point_x = 0;
	map->start_point_y = 0;
	map->start_look = SPRITE_LOOK_RIGHT;
	//Fill the DM_Map
	platform_count--;
	ladder_count--;
	for (i=0 ; i<map_infos->items_int ; i++)
	{
		if (map_infos->lines_array[i]->parameters_int == 5)
		{
			if (strcmp(map_infos->lines_array[i]->parameters[0], "platform-collide"))
			{
				map->platforms[platform_count].x1 = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->platforms[platform_count].y1 = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
				map->platforms[platform_count].x2 = atoi(map_infos->lines_array[i]->parameters[3]) + 1;
				map->platforms[platform_count].y2 = atoi(map_infos->lines_array[i]->parameters[4]) + 1;
				platform_count--;
			}
			else if (strcmp(map_infos->lines_array[i]->parameters[0], "ladder-collide"))
			{
				map->ladders[ladder_count].x1 = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->ladders[ladder_count].y1 = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
				map->ladders[ladder_count].x2 = atoi(map_infos->lines_array[i]->parameters[3]) + 1;
				map->ladders[ladder_count].y2 = atoi(map_infos->lines_array[i]->parameters[4]) + 1;
				ladder_count--;
			}
			else if (strcmp(map_infos->lines_array[i]->parameters[0], "jumpman-start-right"))
			{
				map->start_look = SPRITE_LOOK_RIGHT;
				map->start_point_x = map_infos->lines_array[i]->parameters[1];
				map->start_point_y = map_infos->lines_array[i]->parameters[2];
			}
			else if (strcmp(map_infos->lines_array[i]->parameters[0], "jumpman-start-left"))
			{
				map->start_look = SPRITE_LOOK_LEFT;
				map->start_point_x = map_infos->lines_array[i]->parameters[1];
				map->start_point_y = map_infos->lines_array[i]->parameters[2];
			}
			else if (strcmp(map_infos->lines_array[i]->parameters[0], "finish-collide"))
			{
				map->finish.x1 = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->finish.y1 = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
				map->finish.x2 = atoi(map_infos->lines_array[i]->parameters[3]) + 1;
				map->finish.y2 = atoi(map_infos->lines_array[i]->parameters[4]) + 1;
			}
		}
	}
	//free
	free_dm_splited(map_infos);
	//Return the DM_Map
	return map;
}


/**
 * \fn void free_dm_map(DM_Map *map)
 * \brief Free the memory of a DM_Map
 *
 * \param map The DM_Map to free
 */
void free_dm_map(DM_Map *map)
{
	free(map->platforms);
	free(map->ladders);
	free(map);
}


/**
 * \fn collide(DM_Collide *collide1, DM_Collide *collide2)
 * \brief Check for collision between two DM_Collide.
 *
 * \param collide1 The first DM_Collide;
 * \param collide2 The second DM_Collide;
 *
 * \return Returns 1 if there is a collision, 0 else.
 */
int collide(DM_Collide *collide1, DM_Collide *collide2)
{
	if (collide1->shape == COLLIDE_LINE && collide2->shape == COLLIDE_POINT)
	{
		return _collide_line_point(collide1, collide2);
	}
	else if (collide1->shape == COLLIDE_POINT && collide2->shape == COLLIDE_LINE)
	{
		return _collide_line_point(collide2, collide1);
	}
	else
	{
		printf("W: Collide between shape %i and shape %i not implemented.", collide1->shape, collide2->shape);
	}
}


int _collide_line_point(DM_Collide *cline, DM_Collide *cpoint)
{
	float dx1 = cline->x1;
	float dy1 = cline->y1;
	float dx2 = cline->x2;
	float dy2 = cline->y2;
	float ptx = cpoint->x1;
	int   pty = cpoint->y1;

	float delta = dx1 - dx2;
	float delta_a = dy1 - dy2;
	float delta_b = dx1 * dy2 - dx2 * dy1;

	float a = delta_a / delta;
	float b = delta_b / delta;

	int result = a * ptx + b;

	if (pty == result)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


