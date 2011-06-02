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
 * \fn void level_01(SDL_Surface *screen)
 * \brief Play to the first level.
 *
 * \param screen The main surface (called screen in the main() function).
 */
void level_01(SDL_Surface *screen)
{
	//Load the background
	DM_Surface *level_surface = load_resource_as_dm_surface("level_01.png");
	int level_surface_refresh = ref_object(&LAYER_BG, level_surface, surface_refresh_cb);
	
	//Load and show remaining lifes
	DM_Surface *life = load_resource_as_dm_surface("life.png");
	life->rect.x = 730;
	life->rect.y = 17;
	int life_refresh = ref_object(&LAYER_MENU, life, surface_refresh_cb);
	DM_Surface *life_text = malloc(sizeof(DM_Surface));
	//"x <number of remaining lives>" surface creation
	char life_char[3];
	sprintf(life_char, "x%d", JUMPMAN_LIVES);
	life_text->surface = str_to_surface("font_main.png", life_char);
	life_text->rect.w = life_text->surface->w;
	life_text->rect.h = life_text->surface->h;
	life_text->rect.x = life->rect.x + life->rect.w + 5;
	life_text->rect.y = life->rect.y;
	int life_text_refresh = ref_object(&LAYER_MENU, life_text, surface_refresh_cb);
	
	//Load the level infos (collides,...)
	DM_Map *map = load_map_infos("level_01");
		
	lets_play_yeah(screen, map);
	
	//Dereference objects and free the memory
	deref_object(&LAYER_MENU, life_text_refresh);
	deref_object(&LAYER_MENU, life_refresh);
	deref_object(&LAYER_BG, level_surface_refresh);
	SDL_Delay(50);
	free_dm_surface(life_text);
	free_dm_surface(life);
	free_dm_surface(level_surface);
	free_dm_map(map);
}


