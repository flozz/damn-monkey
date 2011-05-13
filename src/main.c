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
 * \file main.c
 * \brief The main file.
 */


#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#ifdef LINUX
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_mixer/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#endif

#include "refresh.h"
#include "main_menu.h"
#include "credits.h"
#include "game.h"
#include "levels/level_01.h"



/**
 * \fn int main(int argc, char *argv[])
 * \brief The main function.
 */
int main(int argc, char *argv[])
{
	//Print informations about the software
	#ifdef LINUX
	printf("%s, version %s\n", APP_PR_NAME, VERSION);
	#endif
	//Initialize the SDL library
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		fprintf(
				stderr,
				"E: Can not initialize the SDL library: %s\n",
				SDL_GetError()
				);
		exit(EXIT_FAILURE);
	}
	//Initialize the SDL_mixer library
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) != 0)
	{
		fprintf(
				stderr,
				"E: Can not initialize the SDL_mixer library: %s\n",
				Mix_GetError()
				);
		exit(EXIT_FAILURE);
	}
	//Register the SDL_Quit() and the Mix_CloseAudio() functions to be
	//called at normal process termination
	atexit(SDL_Quit);
	atexit(Mix_CloseAudio);
	//Add icon
	#ifdef LINUX
	SDL_WM_SetIcon(load_resource("icon16.png"),NULL);
	#endif
	#ifdef WINDOWS
	SDL_WM_SetIcon(load_resource("icon32.png"),NULL);
	#endif
	#ifdef MAC_OS
	SDL_WM_SetIcon(load_resource("icon64.png"),NULL);
	#endif
	//Configure the window
	SDL_Surface *screen = SDL_SetVideoMode(
			800, //Witdh
			600, //Height
			32,  //Depth
			SDL_HWSURFACE | SDL_DOUBLEBUF
			);
	if (screen == NULL)
	{
		fprintf(stderr, "E: Can not set the video mode: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption(APP_PR_NAME, NULL);
	SDL_ShowCursor(SDL_DISABLE);
	//Display the corporation logo
	corp_logo(screen);
	//Menus music
	Mix_Music *menu_music = load_music_resource("menu.ogg");
	Mix_PlayMusic(menu_music, -1);
	//Init refresh
	refresh_init(screen);
	//Init game
	init_game();
	//Main menu
	int selected;
	while (1)
	{
		selected = main_menu(screen);
		switch (selected)
		{
			case MAIN_MENU_PLAY:
				Mix_HaltMusic();
				level_01(screen);
				Mix_PlayMusic(menu_music, -1);
				break;
			case MAIN_MENU_CREDITS:
				credits(screen);
				break;
			case MAIN_MENU_QUIT:
				Mix_HaltMusic();
				exit(EXIT_SUCCESS);
				break;
			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}


