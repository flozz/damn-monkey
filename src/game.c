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
	int jump = 0;
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
					case SDLK_LEFT:   //FIXME
						horiz_move = HORIZ_MOVE_LEFT;
						break;
					case SDLK_RIGHT:  //FIXME
						horiz_move = HORIZ_MOVE_RIGHT;
						break;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
/*						JUMPMAN.movement = SPRITE_LOOK_LEFT;*/
/*						update_jumpman();*/
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
			//TODO
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


