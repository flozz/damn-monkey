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


#include "main_menu.h"


void corp_logo(SDL_Surface *screen)
{
	//Load the logo
	SDL_Surface *logo = load_ressource("corp_logo.png");
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


