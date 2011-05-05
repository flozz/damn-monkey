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
 * \file level_01.c
 * \brief TODO.
 */


#include "level_01.h"


/**
 * \fn void level_01()
 * \brief Draw the first level.
 *
 * \return Nothing.
 */
void level_01()
{
	//Load the background
	DM_Surface *level_surface = load_resource_as_dm_surface("level_01.png");
	int level_surface_refresh = ref_object(&layer_bg, level_surface, surface_refresh_cb);
	
	//Load the level infos (collides,...)
	DM_Map *map = load_map_infos("level_01");
	lets_play_yeah(map);
	//FIXME: free dm_map
	
	//Dereference objects and free the memory
	deref_object(&layer_bg, level_surface_refresh);
	SDL_Delay(20);
	free_dm_surface(level_surface);
}


