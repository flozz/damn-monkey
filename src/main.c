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
 * \file main.c
 * \brief The main file.
 */


#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#ifdef LINUX
#include "SDL.h"
#include "SDL_image.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#endif

#ifdef WINDOWS
//TODO
#endif

#include "main_menu.h"


/**
 * \fn int main(int argc, char *argv[])
 * \brief The main function.
 */
int main(int argc, char *argv[])
{
	//Print informations about the software
	printf("%s, version %s\n", APP_PR_NAME, VERSION);
	//Initialize the SDL library
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "E: Can not initialize the SDL library: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//Register the SDL_Quit() function to be called at normal process termination
	atexit(SDL_Quit);
	//Configure the window
	SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL)
	{
		fprintf(stderr, "E: Can not set the video mode: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption(APP_PR_NAME, NULL);
	SDL_ShowCursor(SDL_DISABLE);
	//Display the corporation logo
	corp_logo(screen);
	//Main menu
	int selected;
	while (1)
	{
		selected = main_menu(screen);
		switch (selected)
		{
			case 0:
				printf("Main menu > Play\n"); //TODO
				break;
			case 1:
				printf("Main menu > Credits\n"); //TODO
				break;
			case 2:
				exit(EXIT_SUCCESS);
				break;
		}
	}
}


