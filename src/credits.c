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
 * \file credits.c
 * \brief Contains all the functions for credits page.
 */


#include "credits.h"


/**
 * \fn void credits(SDL_Surface *screen)
 * \brief Display the credits.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 */
void credits(SDL_Surface *screen)
{
	//Create the menu
	DM_Menu *menu = new_menu(
			"Back",
			"font_menu.png",
			"font_menu_hl.png",
			"cursor.png"
			);
	menu->menu_rect.x = screen->w - menu->menu->w - 20;
	menu->menu_rect.y = screen->h - menu->menu->h - 15;
	//Create the menu background
	SDL_Surface *background_tmp = load_resource("menu_bg.png");
	SDL_Surface *background = SDL_ConvertSurface(background_tmp, screen->format, NULL);
	SDL_FreeSurface(background_tmp);
	SDL_Surface *title = load_resource("main_menu_title.png");
	SDL_BlitSurface(title, NULL, background, NULL);
	SDL_FreeSurface(title);
	//credits
	SDL_Surface *credits_text = str_to_surface(
			"font_main.png",
			"DEVELOPERS:\n\n\
			  Fabien LOISON\n\
			  Mathilde BOUTIGNY\n\
			  Vincent PEYROUSE\n\
			  Germain CARRE\n\n\n\
			GRAPHISTS:\n\n\
			  Fabien LOISON\n\
			  Mathilde BOUTIGNY\n\n\n\
			Sounds:\n\n\
			  Fabien LOISON"
			);
	SDL_Rect credits_text_rect = {
		(screen->w - credits_text->w) / 4, //x
		(screen->h - credits_text->h - 270 ) / 2 +270, //y
		0, //w
		0  //h
		};
	SDL_BlitSurface(credits_text, NULL, background, &credits_text_rect);
	SDL_FreeSurface(credits_text);
	//Sounds
	Mix_Chunk *sound_valid = load_sound_resource("menu_valid.wav");
	//Menu refresh and effects
	DM_Menu_effect menu_effect;
	menu_effect.bg = background;
	menu_effect.menu = menu;
	menu_effect.screen = screen;
	menu_effect.timer = SDL_AddTimer(20, menu_glow_effect_cb, &menu_effect);
	//Disable key repeat
	SDL_EnableKeyRepeat(0, 0);
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
			}
		}
	}
	while (selected < 0);
	//Change the menu_effect (blink)
	SDL_RemoveTimer(menu_effect.timer);
	menu_effect.timer = SDL_AddTimer(20, menu_blink_effect_cb, &menu_effect);
	//Play the validation sound
	Mix_PlayChannel(-1, sound_valid, 0);
	SDL_Delay(500);
	//Stop the menu_effect
	SDL_RemoveTimer(menu_effect.timer);
	//Free the memory
	free_menu(menu);
	SDL_FreeSurface(background);
	Mix_FreeChunk(sound_valid);
}


