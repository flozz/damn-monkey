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
	DM_Menu *menu = new_menu(
			"Play\nCredits\nQuit",
			"font_menu.png",
			"cursor.png"
			);
	menu->menu_rect.x = (screen->w - menu->menu->w) / 4;
	menu->menu_rect.y = (screen->h - menu->menu->h - 270) / 2 + 270;
	SDL_Surface *background = load_resource("menu_bg.png");
	SDL_Surface *title = load_resource("main_menu_title.png");
	SDL_Surface *version = str_to_surface("font_main.png", VERSION);
	SDL_Rect version_rect = {5, screen->h - version->h - 5, 0, 0};
	SDL_Event event;
	//Disable key repeat
	SDL_EnableKeyRepeat(0, 0);
	//
	while (1)
	{
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(title, NULL, screen, NULL);
		SDL_BlitSurface(version, NULL, screen, &version_rect);
		draw_menu(screen, menu);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		int selected;
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					menu->selected = menu->numb_of_items - 1;
					break;
				case SDLK_UP:
					menu_change_selected(menu, -1);
					break;
				case SDLK_DOWN:
					menu_change_selected(menu, +1);
					break;
				case SDLK_SPACE:
					selected = menu->selected;
					free_menu(menu);
					return selected;
					break;
				case SDLK_RETURN:
					selected = menu->selected;
					free_menu(menu);
					return selected;
					break;
				case SDLK_KP_ENTER:
					selected = menu->selected;
					free_menu(menu);
					return selected;
					break;
			}
		}
	}
}


