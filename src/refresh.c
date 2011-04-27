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
 * \file refresh.c
 * \brief TODO.
 */


#include "refresh.h"


/**
 * \fn void refresh_init(SDL_Surface *screen)
 * \brief Initialize the refresh
 *
 * \param screen The main SDL_Surface.
 */
void refresh_init(SDL_Surface *screen)
{
	main_timer = SDL_AddTimer(20, refresh_cb, NULL);
	layer_bg.screen = screen;
	layer_bg.next = NULL;
	layer_active.screen = screen;
	layer_active.next = NULL;
	layer_fg.screen = screen;
	layer_fg.next = NULL;
	layer_menu.screen = screen;
	layer_menu.next = NULL;
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
	item->id = get_id();
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
 * \brief Dereference an object.
 *
 * \param layer The layer where is the object.
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
 * \brief The main timer callback (used for refresh).
 *
 * \param interval The timer interval.
 * \param args A DM_Refresh_Layer or NULL.
 * \return The timer interval.
 */
Uint32 refresh_cb(Uint32 interval, void *arg)
{
	if (arg == NULL)
	{
		//Clear the screen
		SDL_FillRect(layer_bg.screen, NULL, SDL_MapRGB(layer_bg.screen->format, 0, 0, 0));
		//Blit all layers
		refresh_cb(interval, &layer_bg);
		refresh_cb(interval, &layer_active);
		refresh_cb(interval, &layer_fg);
		refresh_cb(interval, &layer_menu);
		//Refresh the screen
		SDL_Flip(layer_bg.screen);
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


/**
 * \fn surface_refresh_cb(void *object, SDL_Surface *screen)
 * \brief Blit a DM_Surface.
 *
 * \param object The DM_Surface to blit.
 * \param screen The main surface.
 */
void surface_refresh_cb(void *object, SDL_Surface *screen)
{
	DM_Surface *surface = object;
	SDL_BlitSurface(surface->surface, NULL, screen, &surface->rect);
}


