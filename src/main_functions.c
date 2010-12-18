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


#include "main_functions.h"


SDL_Surface* load_ressource(char *ressource_name)
{
	SDL_Surface *img = NULL;
	SDL_Surface *surface = NULL;
	char filepath[255];
	//Try to load form the installation path
	#ifdef LINUX
	strcpy(filepath, "/usr/share/games/");
	strcat(filepath, APP_NAME);
	strcat(filepath, "/pixmaps/");
	strcat(filepath, ressource_name);
	img = IMG_Load(filepath);
	#endif
	#ifdef WINDOWS
	//TODO
	#endif
	#ifdef MAC_OS
	//TODO
	#endif
	//Try to load from local path (devel)
	if (img == NULL)
	{
		strcpy(filepath, "./pixmaps/");
		strcat(filepath, ressource_name);
		img = IMG_Load(filepath);
	}
	if (img == NULL)
	{
		strcpy(filepath, "../pixmaps/");
		strcat(filepath, ressource_name);
		img = IMG_Load(filepath);
	}
	//If the ressource can not be loaded, display an error and exit
	if (img == NULL)
	{
		fprintf(stderr, "E: Can not load the ressource: %s\n", ressource_name);
		exit(EXIT_FAILURE);
	}
	//Blit img in surface
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE, img->w, img->h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(img, NULL, surface, NULL);
	//Free the img memory
	SDL_FreeSurface(img);
	//Return the surface
	return surface;
}


