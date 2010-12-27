/***************************************************************************
*                                                                          *
*  This file is part of Damn Monkey                                        *
*                                                                          *
*  Copyright (C) 2010 - 2011  Fabien LOISON, Mathilde BOUTIGNY,            *
*  Vincent PEYROUSE and Germain CARRÉ                                      *
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
 * \file refresh.c
 * \brief TODO.
 */


#include "refresh.h"


DM_Refresh_Layer layer_bg;
DM_Refresh_Layer layer_active;
DM_Refresh_Layer layer_fg;
DM_Refresh_Layer layer_menu;
SDL_TimerID main_timer;


/**
 * \fn void refresh_init()
 * \brief Initialize the refresh
 */
void refresh_init()
{
	main_timer = SDL_AddTimer(20, refresh_cb, NULL);
	layer_bg.first = NULL;
	layer_active.first = NULL;
	layer_fg.first = NULL;
	layer_menu.first = NULL;
}


/**
 * \fn void refresh_destroy()
 * \brief Stop the refresh
 */
void refresh_destroy()
{
	SDL_RemoveTimer(main_timer);
}


/**
 * \fn int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)())
 * \brief Add an object to the refresh list.
 *
 * \param layer The layer where the object will be added.
 * \param object A pointer on the object
 * \param callback The callback function that will be called for blitting the object
 *                 This function must have a prototype that looks like that:
 * \code
 * void function_name(void *object, SDL_Surface *screen);
 * \endcode
 * 
 * \return The id of the refresh item.
 */
int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)())
{
	//
}


/**
 * \fn void unref_object(int id)
 * \brief TODO
 */
void unref_object(int id)
{
	//
}


/**
 * \fn void refresh_cb(Uint32 interval, void *arg)
 * \brief TODO
 */
void refresh_cb(Uint32 interval, void *arg)
{
	//
}


/**
 * \fn int get_id()
 * \brief Return an unique identifier.
 *
 * \return The identifier.
 */
int get_id()
{
	static int id = 0;
	id++;
	return id;
}


