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
 * \file refresh.c
 * \brief Contains the code of the Global Refresh system.
 *
 * The Global Refresh system handles all objects to display on the screen, and
 * manages the screen refresh. In order to keep a consistent display of all
 * the objects, it provides 4 layers:
 * - LAYER_BG: The background layer, used for the level objects like
 *             platforms,...
 * - LAYER_ACTIVE: The layer that contains the actives objects like Jumpman,
 *                 barrels,...
 * - LAYER_FG: The foreground layer that is used for objects that should be
 *             over Jumpman, and for displaying the remaining lives and the
 *             score.
 * - LAYER_MENU: The layer used for displaying the menus.
 */


#include "refresh.h"


/**
 * \fn void refresh_init(SDL_Surface *screen)
 * \brief Initializes the Global Refresh.
 *
 * \param screen The main SDL_Surface (called screen in the main() function).
 */
void refresh_init(SDL_Surface *screen)
{
	main_timer = SDL_AddTimer(20, refresh_cb, NULL); //50 Hz refresh
	LAYER_BG.screen = screen;
	LAYER_BG.next = NULL;
	LAYER_ACTIVE.screen = screen;
	LAYER_ACTIVE.next = NULL;
	LAYER_FG.screen = screen;
	LAYER_FG.next = NULL;
	LAYER_MENU.screen = screen;
	LAYER_MENU.next = NULL;
}


/**
 * \fn void refresh_destroy()
 * \brief Stops the Global Refresh.
 */
void refresh_destroy()
{
	SDL_RemoveTimer(main_timer);
}


/**
 * \fn int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)())
 * \brief Adds an object to the Global Refresh objects list.
 *
 * \param layer The layer on which the object will be added (LAYER_BG,
 *              LAYER_ACTIVE, LAYER_FG or LAYER_MENU).
 * \param object A pointer on the object to register.
 * \param callback The callback function that will be called for blitting the
 *                 object. This function must have a prototype that looks like
 *                 that:
 * \code
 * void function_name(void *object, SDL_Surface *screen);
 * \endcode
 *
 * \return Returns the id of the item (used by the Global Refresh for
 * identifying the object).
 */
int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)())
{
	DM_Refresh_Item *item = NULL;
	DM_Refresh_Item *current_item = NULL;
	//Memory allocation
	item = malloc(sizeof(DM_Refresh_Item));
	if (item == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//Set field
	item->id = _get_id();
	item->object = object;
	item->callback = callback;
	item->next = NULL;
	//
	if (layer->next == NULL)
	{
		layer->next = item;
	}
	else
	{
		//Search the last item of the list
		current_item = layer->next;
		while (current_item->next != NULL)
		{
			current_item = current_item->next;
		}
		current_item->next = item;
	}
	//Return the identifier
	return item->id;
}


/**
 * \fn void deref_object(DM_Refresh_Layer *layer, int id)
 * \brief Dereference an object of the Global Refresh list.
 *
 * \param layer The layer on which is the object (LAYER_BG, LAYER_ACTIVE,
 *              LAYER_FG or LAYER_MENU).
 * \param id The identifier of the object.
 */
void deref_object(DM_Refresh_Layer *layer, int id)
{
	DM_Refresh_Item *current_item = layer->next;
	while (current_item != NULL)
	{
		if (current_item->id == id)
		{
			current_item->callback = NULL;
			break;
		}
		else
		{
			current_item = current_item->next;
		}
	}
}


/**
 * \fn Uint32 refresh_cb(Uint32 interval, void *arg)
 * \brief The main timer callback (used for the Global Refresh).
 *
 * \param interval The timer interval.
 * \param args A DM_Refresh_Layer or NULL.
 *
 * \return The timer interval.
 */
Uint32 refresh_cb(Uint32 interval, void *arg)
{
	if (arg == NULL)
	{
		//Clear the screen
		SDL_FillRect(
				LAYER_BG.screen,
				NULL,
				SDL_MapRGB(LAYER_BG.screen->format, 0, 0, 0)
				);
		//Blit all layers
		refresh_cb(interval, &LAYER_BG);
		refresh_cb(interval, &LAYER_ACTIVE);
		refresh_cb(interval, &LAYER_FG);
		refresh_cb(interval, &LAYER_MENU);
		//Refresh the screen
		SDL_Flip(LAYER_BG.screen);
	}
	else
	{
		DM_Refresh_Layer *layer = arg;
		DM_Refresh_Item *prev_item = NULL;
		DM_Refresh_Item *current_item = layer->next;
		while (current_item != NULL)
		{
			if (current_item->callback != NULL)
			{
				current_item->callback(current_item->object, layer->screen);
				prev_item = current_item;
			}
			else //Remove the item
			{
				if (prev_item != NULL)
				{
					prev_item->next = current_item->next;
				}
				else
				{
					layer->next = current_item->next;
				}
				free(current_item);
			}
			current_item = current_item->next;
		}
	}
	return interval;
}


/**
 * \fn surface_refresh_cb(void *object, SDL_Surface *screen)
 * \brief Refreshes a DM_Surface.
 *
 * This is the callback function for the Global Refresh that handles
 * the DM_Surface refresh.
 *
 * \param object The DM_Surface to refresh.
 * \param screen The main surface (called screen in the main() function).
 */
void surface_refresh_cb(void *object, SDL_Surface *screen)
{
	DM_Surface *surface = object;
	SDL_BlitSurface(surface->surface, NULL, screen, &surface->rect);
}


/** \cond */ //Hide the "privates" functions for Doxygen

//This function returns a unique identifier used by the Global Refresh.
int _get_id()
{
	static int id = 0;
	id++;
	return id;
}

/** \endcond */


