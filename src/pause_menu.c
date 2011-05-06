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
 * \file pause_menu.c
 * \brief Contain the code for the pause menu
 */


#include "pause_menu.h"


/**
 * \fn int pause_menu(SDL_Surface *screen)
 * \brief Display the pause menu.
 *
 * \param screen The main surface.
 * \return The selected item id(0 = continue, 1 = return to main menu, 2 = quit the game).
 */
int pause_menu(SDL_Surface *screen)
{
	DM_Surface *shading_bg = load_resource_as_dm_surface("pause_menu.png");
	int shading_refresh = ref_object(&layer_menu, shading_bg, surface_refresh_cb);
	
	//Disable key repeat
	SDL_EnableKeyRepeat(0, 0);
	//Load sounds
	Mix_Chunk *sound_select = load_sound_resource("menu_select.wav");
	Mix_Chunk *sound_valid = load_sound_resource("menu_valid.wav");
		

	DM_Menu *menu = new_menu(
			 "Continue\nMain Menu\nQuit",
			 "font_menu.png",
			 "font_menu_hl.png",
			 "cursor.png"
			 );
	menu->menu_rect.x = screen->w /2.8;
	menu->menu_rect.y = screen->h /2.15;
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
					menu->selected = 0;
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

	deref_object(&layer_menu, menu_refresh);
	deref_object(&layer_menu, shading_refresh);
	SDL_Delay(20);
	free_dm_surface(shading_bg);
	free_menu(menu);

	return selected;
}


