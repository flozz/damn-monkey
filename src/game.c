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
	JUMPMAN.pos_x = 42;
	JUMPMAN.pos_y = 42;
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


/**
 * \fn int lets_play_yeah(DM_Map *map)
 * \brief This is the main function of the game. It control jumpman,...
 *
 * \param map The DM_Map that contain collides for the level.
 *
 * \return Returns the game status (GAME_STATE_LEVEL_COMPLETED, GAME_STATE_LIFE_LOST).
 */
int lets_play_yeah(DM_Map *map) {
	//Enable the key repetition
	SDL_EnableKeyRepeat(0, 0);
	//Initialize the GAME_STATE variable
	GAME_STATE = GAME_STATE_PLAYING;
	//Set the start position of jumpman
	JUMPMAN.movement = map->start_look;
	JUMPMAN.pos_x = map->start_point_x - JUMPMAN.sprite->items[JUMPMAN.movement].w / 2;
	JUMPMAN.pos_y = map->start_point_y - JUMPMAN.sprite->items[JUMPMAN.movement].h;
	update_jumpman();
	//Reference Jumman in the global refresh
	int jumpman_refresh = ref_object(&layer_active, JUMPMAN.sprite, sprite_cb);
	//some vars
	int horiz_move = HORIZ_MOVE_NONE_R;
	int vert_move = VERT_MOVE_NONE;
	if (JUMPMAN.movement == SPRITE_LOOK_LEFT)
	{
		horiz_move = HORIZ_MOVE_NONE_L;
	}
	else
	{
		horiz_move = HORIZ_MOVE_NONE_R;
	}
	int jump = JUMP_NONE;
	int jump_y_start = 0;
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
					case SDLK_UP:
						if (vert_move == VERT_MOVE_NONE) {
							if (check_ladder_bottom_collides(&JUMPMAN.platform_collide, map))
							{
								vert_move = VERT_MOVE_UP;
							}
						}
						else
						{
							if (check_ladder_collides(&JUMPMAN.platform_collide, map))
							{
								vert_move = VERT_MOVE_UP;
							}
						}
						break;
					case SDLK_DOWN:
						if (vert_move == VERT_MOVE_NONE) {
							if (check_ladder_top_collides(&JUMPMAN.platform_collide, map))
							{
								vert_move = VERT_MOVE_DOWN;
							}
						}
						else
						{
							if (check_ladder_collides(&JUMPMAN.platform_collide, map))
							{
								vert_move = VERT_MOVE_DOWN;
							}
						}
						break;
					case SDLK_SPACE:
						if (!jump && vert_move == VERT_MOVE_NONE) 
						{
							jump = JUMP_UP;
							jump_y_start = JUMPMAN.pos_y;
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
					case SDLK_UP:
						if (vert_move == VERT_MOVE_UP)
						{
							vert_move = VERT_MOVE_IM;
						}
						break;
					case SDLK_DOWN:
						if (vert_move == VERT_MOVE_DOWN)
						{
							vert_move = VERT_MOVE_IM;
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
			//HORIZ
			if (!check_ladder_collides(&JUMPMAN.platform_collide, map) || 
					(
					 check_ladder_collides(&JUMPMAN.platform_collide, map) &&
					 check_ladder_top_collides(&JUMPMAN.platform_collide, map)
					) || (
					 check_ladder_collides(&JUMPMAN.platform_collide, map) &&
					 check_ladder_bottom_collides(&JUMPMAN.platform_collide, map)
					)
				)
			{
				if (horiz_move == HORIZ_MOVE_LEFT) {
					JUMPMAN.movement = SPRITE_WALK_LEFT;
					JUMPMAN.platform_collide.x1--;
					if (!check_platform_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_x -= 1;
					}
					else
					{
						JUMPMAN.platform_collide.y1--;
						if (!check_platform_collides(&JUMPMAN.platform_collide, map))
						{
							JUMPMAN.pos_x -= 1;
							JUMPMAN.pos_y -= 1;
						}
					}
				}
				else if (horiz_move == HORIZ_MOVE_NONE_L) {
					JUMPMAN.movement = SPRITE_LOOK_LEFT;
					JUMPMAN.pos_x = JUMPMAN.platform_collide.x1 - JUMPMAN.sprite->items[JUMPMAN.movement].w / 2; 
				}
				else if (horiz_move == HORIZ_MOVE_RIGHT) {
					JUMPMAN.movement = SPRITE_WALK_RIGHT;
					JUMPMAN.platform_collide.x1++;
					if (!check_platform_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_x += 1;
					}
					else
					{
						JUMPMAN.platform_collide.y1--;
						if (!check_platform_collides(&JUMPMAN.platform_collide, map))
						{
							JUMPMAN.pos_x += 1;
							JUMPMAN.pos_y -= 1;
						}
					}
				}
				else if (horiz_move == HORIZ_MOVE_NONE_R) {
					JUMPMAN.movement = SPRITE_LOOK_RIGHT;
					JUMPMAN.pos_x = JUMPMAN.platform_collide.x1 - JUMPMAN.sprite->items[JUMPMAN.movement].w / 2;
				}
			}
			//VERT 
			if (vert_move == VERT_MOVE_UP)
			{
				if (check_ladder_collides(&JUMPMAN.platform_collide, map))
				{
					if (check_ladder_top_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_y -= 5;
						vert_move = VERT_MOVE_NONE;
					}
					else
					{
						JUMPMAN.pos_y--;
						JUMPMAN.movement = SPRITE_WALK_LADDER;
					}
				}
				else
				{
					vert_move = VERT_MOVE_NONE;
				}
			}
			else if (vert_move == VERT_MOVE_DOWN)
			{
				if (check_ladder_collides(&JUMPMAN.platform_collide, map))
				{
					JUMPMAN.platform_collide.y1++;
					if(!check_ladder_bottom_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_y++;
						JUMPMAN.movement = SPRITE_WALK_LADDER;
					}
					else
					{
						vert_move = VERT_MOVE_NONE;
						JUMPMAN.pos_y--;
					}
				}
				else
				{
					vert_move = VERT_MOVE_NONE;
				}
			}
			else if (vert_move == VERT_MOVE_IM)
			{
				JUMPMAN.movement = SPRITE_LADDER;
			}
		}
		else
		{
			if (horiz_move == HORIZ_MOVE_LEFT) {
				JUMPMAN.movement = SPRITE_JUMP_LEFT;
				JUMPMAN.platform_collide.x1--;
				if (!check_platform_collides(&JUMPMAN.platform_collide, map))
				{
					JUMPMAN.pos_x -= 1;
				}
				else
				{
					JUMPMAN.platform_collide.y1--;
					if (!check_platform_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_x -= 1;
						JUMPMAN.pos_y -= 1;
					}
				}
			}
			else if (horiz_move == HORIZ_MOVE_NONE_L) {
				JUMPMAN.movement = SPRITE_JUMP_LEFT;
			}
			else if (horiz_move == HORIZ_MOVE_RIGHT) {
				JUMPMAN.movement = SPRITE_JUMP_RIGHT;
				JUMPMAN.platform_collide.x1++;
				if (!check_platform_collides(&JUMPMAN.platform_collide, map))
				{
					JUMPMAN.pos_x += 1;
				}
				else
				{
					JUMPMAN.platform_collide.y1--;
					if (!check_platform_collides(&JUMPMAN.platform_collide, map))
					{
						JUMPMAN.pos_x += 1;
						JUMPMAN.pos_y -= 1;
					}
				}
			}
			else if (horiz_move == HORIZ_MOVE_NONE_R) {
				JUMPMAN.movement = SPRITE_JUMP_RIGHT;
			}

			if (jump == JUMP_UP)
			{
				if (jump_y_start - JUMPMAN.pos_y < 10)
				{
					JUMPMAN.pos_y -= 3;
				}
				else if (jump_y_start - JUMPMAN.pos_y < 25)
				{
					JUMPMAN.pos_y -= 2;
				}
				else if (jump_y_start - JUMPMAN.pos_y < 35)
				{
					JUMPMAN.pos_y -= 1;
				}
				else
				{
					jump = JUMP_DOWN;
				}
			}
			else
			{
				JUMPMAN.platform_collide.y1++;
				if (check_platform_collides(&JUMPMAN.platform_collide, map))
				{
					jump = JUMP_NONE;
				}
			}
		}
		update_jumpman();
		//Gravity
		if (jump != JUMP_UP && vert_move == VERT_MOVE_NONE)
		{
			JUMPMAN.platform_collide.y1++;
			if (!check_platform_collides(&JUMPMAN.platform_collide, map))
			{
				JUMPMAN.pos_y++;
			}
		}
		update_jumpman();
		//Finish area
		if (collide(&map->finish, &JUMPMAN.platform_collide))
		{
			GAME_STATE = GAME_STATE_LEVEL_COMPLETED;
		}
		SDL_Delay(5);
	}

	//If the player die
	if (GAME_STATE == GAME_STATE_LIFE_LOST)
	{
		JUMPMAN.movement = SPRITE_DEAD;
		update_jumpman();
		SDL_Delay(1500);
	}

	//Dereference Jumpman
	deref_object(&layer_active, jumpman_refresh);
	return GAME_STATE;
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
	sprintf(path, "levels/%s.map", level_name);
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
			if (!strcmp(map_infos->lines_array[i]->parameters[0], "platform-collide"))
			{
				map->platforms[platform_count].shape = COLLIDE_LINE;
				map->platforms[platform_count].x1 = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->platforms[platform_count].y1 = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
				map->platforms[platform_count].x2 = atoi(map_infos->lines_array[i]->parameters[3]) + 1;
				map->platforms[platform_count].y2 = atoi(map_infos->lines_array[i]->parameters[4]) + 1;
				platform_count--;
			}
			else if (!strcmp(map_infos->lines_array[i]->parameters[0], "ladder-collide"))
			{
				map->ladders[ladder_count].shape = COLLIDE_RECT;
				map->ladders[ladder_count].x1 = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->ladders[ladder_count].y1 = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
				map->ladders[ladder_count].x2 = atoi(map_infos->lines_array[i]->parameters[3]) + 1;
				map->ladders[ladder_count].y2 = atoi(map_infos->lines_array[i]->parameters[4]) + 1;
				ladder_count--;
			}
			else if (!strcmp(map_infos->lines_array[i]->parameters[0], "jumpman-start-right"))
			{
				map->start_look = SPRITE_LOOK_RIGHT;
				map->start_point_x = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->start_point_y = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
			}
			else if (!strcmp(map_infos->lines_array[i]->parameters[0], "jumpman-start-left"))
			{
				map->start_look = SPRITE_LOOK_LEFT;
				map->start_point_x = atoi(map_infos->lines_array[i]->parameters[1]) + 1;
				map->start_point_y = atoi(map_infos->lines_array[i]->parameters[2]) + 1;
			}
			else if (!strcmp(map_infos->lines_array[i]->parameters[0], "finish-collide"))
			{
				map->finish.shape = COLLIDE_RECT;
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


//TODO
int check_platform_collides(DM_Collide *collide_point, DM_Map *map)
{
	int i;
	for (i=0 ; i<map->platform_count ; i++)
	{
		if (collide(collide_point, &map->platforms[i]))
		{
			return 1;
		}
	}
	return 0;
}

//TODO
int check_ladder_collides(DM_Collide *collide_point, DM_Map *map)
{
	int i;
	for (i=0 ; i<map->ladder_count ; i++)
	{
		if (collide(collide_point, &map->ladders[i]))
		{
			return 1;
		}
	}
	return 0;
}

//TODO
int check_ladder_top_collides(DM_Collide *collide_point, DM_Map *map)
{
	DM_Collide crect;
	crect.shape = COLLIDE_RECT;
	int i;
	for (i=0 ; i<map->ladder_count ; i++)
	{
		crect.x1 = map->ladders[i].x1;
		crect.x2 = map->ladders[i].x2;
		if (map->ladders[i].y1 < map->ladders[i].y2)
		{
			crect.y1 = map->ladders[i].y1;
			crect.y2 = map->ladders[i].y1 + 3;
		}
		else
		{
			crect.y1 = map->ladders[i].y2;
			crect.y2 = map->ladders[i].y2 + 3;
		}
		if (collide(collide_point, &crect))
		{
			return 1;
		}
	}
	return 0;
}


int check_ladder_bottom_collides(DM_Collide *collide_point, DM_Map *map)
{
	DM_Collide crect;
	crect.shape = COLLIDE_RECT;
	int i;
	for (i=0 ; i<map->ladder_count ; i++)
	{
		crect.x1 = map->ladders[i].x1;
		crect.x2 = map->ladders[i].x2;
		if (map->ladders[i].y1 < map->ladders[i].y2)
		{
			crect.y1 = map->ladders[i].y2 - 10;
			crect.y2 = map->ladders[i].y2;
		}
		else
		{
			crect.y1 = map->ladders[i].y1 - 10;
			crect.y2 = map->ladders[i].y1;
		}
		if (collide(collide_point, &crect))
		{
			return 1;
		}
	}
	return 0;
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
	if (collide1->shape == COLLIDE_RECT && collide2->shape == COLLIDE_POINT)
	{
		return _collide_rect_point(collide1, collide2);
	}
	else if (collide1->shape == COLLIDE_POINT && collide2->shape == COLLIDE_RECT)
	{
		return _collide_rect_point(collide2, collide1);
	}
	else
	{
/*		printf("W: Collide between shape %i and shape %i not implemented.\n", collide1->shape, collide2->shape);*/
		return 0;
	}
}


int _collide_line_point(DM_Collide *cline, DM_Collide *cpoint)
{
	//Check the rect
	if (!_collide_rect_point(cline, cpoint))
	{
		return 0;
	}
	//Check the line
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
		//An other test for fiability
		dy1 += 1;
		dy2 += 1;

		delta = dx1 - dx2;
		delta_a = dy1 - dy2;
		delta_b = dx1 * dy2 - dx2 * dy1;

		a = delta_a / delta;
		b = delta_b / delta;

		result = a * ptx + b;

		if (pty == result)
		{
			return 1;
		}

		return 0;
	}
}


int _collide_rect_point(DM_Collide *crect, DM_Collide *cpoint)
{
	int x1, x2, y1, y2;
	if (crect->x1 < crect->x2)
	{
		x1 = crect->x1;
		x2 = crect->x2;
	}
	else
	{
		x1 = crect->x2;
		x2 = crect->x1;
	}
	if (crect->y1 < crect->y2)
	{
		y1 = crect->y1;
		y2 = crect->y2;
	}
	else
	{
		y1 = crect->y2;
		y2 = crect->y1;
	}
	if (cpoint->x1 <  x1 || cpoint->x1 > x2 || cpoint->y1 < y1 || cpoint->y1 > y2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


