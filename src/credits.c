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
 * \file credits.c
 * \brief Contains all the functions for the credits page.
 */


#include "credits.h"


/**
 * \fn DM_Credits* new_credits(int numb_pages)
 * \brief Creates a new DM_Credits.
 *
 * \param numb_page The number of pages.
 *
 * \return A pointer on the new DM_Credits.
 */
DM_Credits* new_credits(int numb_pages)
{
	DM_Credits *credits = malloc(sizeof(DM_Credits));
	if (credits == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	credits->pages = malloc(numb_pages * sizeof(SDL_Surface*));
	credits->titles = malloc(numb_pages * sizeof(SDL_Surface*));
	credits->numb_pages = numb_pages;
	credits->current_page = -1;
	credits->speed = 20;
	return credits;
}


/**
 * \fn void free_credits(DM_Credits *credits)
 * \brief Frees the memory of a DM_Credits.
 *
 * \param credits The DM_Credits to free.
 */
void free_credits(DM_Credits *credits)
{
	int i;
	for (i=0 ; i<credits->numb_pages ; i++)
	{
		SDL_FreeSurface(credits->pages[i]);
		SDL_FreeSurface(credits->titles[i]);
	}
	free(credits->pages);
	free(credits->titles);
	free(credits);
}


/**
 * \fn void credits_cb(void *object, SDL_Surface *screen)
 * \brief Refreshes callback for the DM_Credits.
 *
 * \param object The DM_Credits to refresh.
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 */
void credits_cb(void *object, SDL_Surface *screen)
{
	DM_Credits *credits = object;
	//Init a new page
	if (credits->current_page < 0)
	{
		credits->current_page = 0 - credits->current_page;
		credits->page_rect.x = screen->w;
		credits->page_rect.y = 440;
		credits->title_rect.x = 0 - credits->titles[credits->current_page-1]->w;
		credits->title_rect.y = 400;
		credits->speed = 20;
	}
	//Blit
	if (credits->page_rect.x < 0)
	{
		credits->page_rect.x = -800;
	}
	SDL_BlitSurface(
			credits->pages[credits->current_page-1],
			NULL,
			screen,
			&credits->page_rect
			);
	SDL_BlitSurface(
			credits->titles[credits->current_page-1],
			NULL,
			screen,
			&credits->title_rect
			);
	//Move
	credits->page_rect.x -= credits->speed;
	credits->title_rect.x += credits->speed / 2.5 + 1;
	//Change speed
	if (credits->page_rect.x > screen->w / 3)
	{
		credits->speed = (credits->page_rect.x - screen->w / 3) \
						 * 30 / (2 * screen->w / 2) + 1;
	}
	if (credits->page_rect.x < screen->w / 4)
	{
		credits->speed = (3* screen->w / 4 - credits->page_rect.x) \
						 * 20 / (screen->w / 2) + 1;
	}
	//Change of layer
	if (credits->title_rect.x > screen->w - 50)
	{
		credits->current_page += 1;
		if (credits->current_page > credits->numb_pages)
		{
			credits->current_page = 1;
		}
		credits->current_page = 0 - credits->current_page;
	}
}


/**
 * \fn void credits(SDL_Surface *screen)
 * \brief Displays the credits page.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 */
void credits(SDL_Surface *screen)
{
	//Disable key repeat
	SDL_EnableKeyRepeat(0, 0);
	//Load sound
	Mix_Chunk *sound_valid = load_sound_resource("menu_valid.wav");
	//Background
	DM_Surface *bg = load_resource_as_dm_surface("menu_bg.png");
	int bg_refresh = ref_object(&layer_bg, bg, surface_refresh_cb);
	//Title
	DM_Surface *title = load_resource_as_dm_surface("main_menu_title.png");
	int title_refresh = ref_object(&layer_bg, title, surface_refresh_cb);
	//Create the menu
	DM_Menu *menu = new_menu(
			"Back",
			"font_menu.png",
			"font_menu_hl.png",
			"cursor.png"
			);
	menu->menu_rect.x = screen->w - menu->menu->w - 20;
	menu->menu_rect.y = screen->h - menu->menu->h - 15;
	int menu_refresh = ref_object(&layer_menu, menu, menu_glow_effect_cb);
	//Credits
	DM_Credits *credits = new_credits(4);
	credits->titles[0] = str_to_surface("font_main.png", "- DEVELOPERS -");
	credits->pages[0] = str_to_surface(
			"font_main.png",
			"Fabien LOISON\n\
			Mathilde BOUTIGNY\n\
			Vincent PEYROUSE\n\
			Germain CARRE\n\
			Matthis FRENAY"
			);
	credits->titles[1] = str_to_surface("font_main.png", "- GRAPHISTS -");
	credits->pages[1] = str_to_surface(
			"font_main.png",
			"Fabien LOISON\n\
			Mathilde BOUTIGNY\n\
			Matthis FRENAY"
			);
	credits->titles[2] = str_to_surface("font_main.png", "- SOUNDS -");
	credits->pages[2] = str_to_surface(
			"font_main.png",
			"Fabien LOISON"
			);
	credits->titles[3] = str_to_surface("font_main.png", "- MUSICS -");
	credits->pages[3] = str_to_surface(
			"font_main.png",
			"Andrey Avkhimovich"
			);
	int credits_refresh = ref_object(&layer_active, credits, credits_cb);
	//Main loop
	SDL_Event event;
	int selected = -1;
	do
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					selected = menu->selected;
					break;
				case SDLK_SPACE:
					selected = menu->selected;
					break;
				case SDLK_RETURN:
					selected = menu->selected;
					break;
				case SDLK_KP_ENTER:
					selected = menu->selected;
					break;
				default:
					break;
			}
		}
		else if (event.type == SDL_QUIT)
		{
			menu->selected = menu->numb_of_items - 1;
			selected = menu->selected;
		}
	}
	while (selected < 0);
	//Play a confirmation sound and change the menu effect
	Mix_PlayChannel(-1, sound_valid, 0);
	deref_object(&layer_menu, menu_refresh);
	menu_refresh = ref_object(&layer_menu, menu, menu_blink_effect_cb);
	SDL_Delay(500);
	//Dereference objects and free the memory
	deref_object(&layer_bg, bg_refresh);
	deref_object(&layer_bg, title_refresh);
	deref_object(&layer_menu, menu_refresh);
	deref_object(&layer_active, credits_refresh);
	SDL_Delay(50);
	free_dm_surface(bg);
	free_dm_surface(title);
	free_menu(menu);
	free_credits(credits);
	//Free sound memory
	Mix_FreeChunk(sound_valid);
}


