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
 * \file main_menu.c
 * \brief Contains all the functions for the main menu.
 */


#include "main_menu.h"


/**
 * \fn void corp_logo(SDL_Surface *screen)
 * \brief Display the corporation logo.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 */
void corp_logo(SDL_Surface *screen)
{
	//Load the logo
	SDL_Surface *logo = load_resource("corp_logo.png");
	//Calculate the position of the logo
	SDL_Rect logo_rect;
	logo_rect.x = (screen->w - logo->w) / 2;
	logo_rect.y = (screen->h - logo->h) / 2;
	//Logo animation
	int alpha;
	//Fade in
	for (alpha = 0 ; alpha<=255 ; alpha+=5)
	{
		SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(logo, NULL, screen, &logo_rect);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	//Wait
	SDL_Delay(2000);
	//Fade out
	for (alpha = 255 ; alpha>=0 ; alpha-=5)
	{
		SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(logo, NULL, screen, &logo_rect);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	//Wait
	SDL_Delay(100);
	//Free the memory
	SDL_FreeSurface(logo);
}


/**
 * \fn int main_menu(SDL_Surface *screen)
 * \brief The main menu.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 * \return The index of the selected item: 0 = Play, 1 = Credits,
 *         2 = Quit.
 */
int main_menu(SDL_Surface *screen)
{
	//Disable key repeat
	SDL_EnableKeyRepeat(0, 0);
	//Load sounds
	Mix_Chunk *sound_select = load_sound_resource("menu_select.wav");
	Mix_Chunk *sound_valid = load_sound_resource("menu_valid.wav");
	//Background
	DM_Surface *bg = load_resource_as_dm_surface("menu_bg.png");
	int bg_refresh = ref_object(&layer_bg, bg, surface_refresh_cb);
	//Title
	DM_Surface *title = load_resource_as_dm_surface("main_menu_title.png");
	int title_refresh = ref_object(&layer_bg, title, surface_refresh_cb);
	//version
	DM_Surface version;
	version.surface = str_to_surface("font_main.png", VERSION);
	version.rect.x = 5;
	version.rect.y = screen->h - version.surface->h - 5;
	int version_refresh = ref_object(&layer_bg, &version, surface_refresh_cb);
	//Create the menu
	DM_Menu *menu = new_menu(
							 "Play\nCredits\nQuit",
							 "font_menu.png",
							 "font_menu_hl.png",
							 "cursor.png"
							 );
	menu->menu_rect.x = (screen->w - menu->menu->w) / 4;
	menu->menu_rect.y = (screen->h - menu->menu->h - 270) / 2 + 270;
	int menu_refresh = ref_object(&layer_menu, menu, menu_glow_effect_cb);
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
					menu->selected = menu->numb_of_items - 1;
					selected = menu->selected;
					break;
				case SDLK_UP:
					menu_change_selected(menu, -1);
					Mix_PlayChannel(-1, sound_select, 0);
					break;
				case SDLK_DOWN:
					menu_change_selected(menu, +1);
					Mix_PlayChannel(-1, sound_select, 0);
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
	deref_object(&layer_bg, version_refresh);
	deref_object(&layer_menu, menu_refresh);
	SDL_Delay(20);
	free_dm_surface(bg);
	free_dm_surface(title);
	SDL_FreeSurface(version.surface);
	free_menu(menu);
	//Free sounds memory
	Mix_FreeChunk(sound_select);
	Mix_FreeChunk(sound_valid);
	return selected;
}


