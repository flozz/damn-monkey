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
 * \file main_menu.c
 * \brief Contains all the functions for the main menu.
 */


#include "main_menu.h"


/**
 * \fn void corp_logo(SDL_Surface *screen)
 * \brief Display the corporation logo.
 *
 * WARNING: This function does not use the global refresh, so it must not be
 * called after the initialisation of the global refresh (it can crash The
 * application) !
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
 * \brief Displays the main menu.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 *
 * \return Returns the selected item (MAIN_MENU_PLAY, MAIN_MENU_CREDITS
 *         or MAIN_MENU_QUIT).
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
	int bg_refresh = ref_object(&LAYER_BG, bg, surface_refresh_cb);
	//Title
	DM_Surface *title = load_resource_as_dm_surface("main_menu_title.png");
	int title_refresh = ref_object(&LAYER_BG, title, surface_refresh_cb);
	//Version
	DM_Surface version;
	version.surface = str_to_surface("font_main.png", VERSION);
	version.rect.x = 5;
	version.rect.y = screen->h - version.surface->h - 5;
	int version_refresh = ref_object(&LAYER_BG, &version, surface_refresh_cb);
	//Create the menu
	DM_Menu *menu = new_menu(
			"Play\nCredits\nQuit",
			"font_menu.png",
			"font_menu_hl.png",
			"cursor.png"
			);
	menu->menu_rect.x = (screen->w - menu->menu->w) / 4;
	menu->menu_rect.y = (screen->h - menu->menu->h - 270) / 2 + 270;
	int menu_refresh = ref_object(&LAYER_MENU, menu, menu_glow_effect_cb);
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
					menu->selected = MAIN_MENU_QUIT;
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
			menu->selected = MAIN_MENU_QUIT;
			selected = menu->selected;
		}
	}
	while (selected < 0);
	//Play a confirmation sound and change the menu effect
	Mix_PlayChannel(-1, sound_valid, 0);
	deref_object(&LAYER_MENU, menu_refresh);
	menu_refresh = ref_object(&LAYER_MENU, menu, menu_blink_effect_cb);
	SDL_Delay(500);
	//Dereference the objects
	deref_object(&LAYER_BG, bg_refresh);
	deref_object(&LAYER_BG, title_refresh);
	deref_object(&LAYER_BG, version_refresh);
	deref_object(&LAYER_MENU, menu_refresh);
	SDL_Delay(50);
	//Free the memory
	free_dm_surface(bg);
	free_dm_surface(title);
	SDL_FreeSurface(version.surface);
	free_menu(menu);
	//Free sounds memory
	Mix_FreeChunk(sound_select);
	Mix_FreeChunk(sound_valid);
	//Return the selected item
	return selected;
}


