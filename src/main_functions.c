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
 * \file main_functions.c
 * \brief Contains generic functions, like resource loading,
 *        text generation,...
 */


#include "main_functions.h"


/**
 * \fn SDL_Surface* load_resource(char *resource_name)
 * \brief Loads an image resource.
 *
 * Searches the resource in different paths and loads it. If it can not find or
 * load the resource, it stops the program and displays an error.
 *
 * \param resource_name The resource name (ex. "logo.png").
 *
 * \return A pointer on a SDL_Surface containing the resource.
 */
SDL_Surface* load_resource(char *resource_name)
{
	SDL_Surface *img = NULL;
	char filepath[255];
	//Try to load form the installation path
	#ifdef LINUX
	sprintf(
			filepath,
			"/usr/share/games/%s/pixmaps/%s",
			APP_NAME,
			resource_name
			);
	#endif
	#ifdef MAC_OS
	sprintf(
			filepath,
			"./%s.app/Contents/Resources/pixmaps/%s",
			APP_PR_NAME,
			resource_name
			);
	#endif
	img = IMG_Load(filepath);
	//Try to load from local path
	if (img == NULL)
	{
		sprintf(filepath, "./pixmaps/%s", resource_name);
		img = IMG_Load(filepath);
	}
	if (img == NULL)
	{
		sprintf(filepath, "../pixmaps/%s", resource_name);
		img = IMG_Load(filepath);
	}
	//If the resource can not be loaded, display an error and exit
	if (img == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_name);
		exit(EXIT_FAILURE);
	}
	//Return the surface
	return img;
}


/**
 * \fn DM_Surface* load_resource_as_dm_surface(char *resource_name)
 * \brief Creates a DM_Surface from an image resource.
 *
 * Creates a DM_Surface from a image resource that can be used
 * with the global refresh.
 *
 * \param resource_name The resource name (ex. "font_main.png").
 *
 * \return A pointer on a DM_Surface containing the image.
 */
DM_Surface* load_resource_as_dm_surface(char *resource_name)
{
	DM_Surface *surface;
	surface = malloc(sizeof(DM_Surface));
	if (surface == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	surface->surface = load_resource(resource_name);
	surface->rect.x = 0;
	surface->rect.y = 0;
	surface->rect.w = surface->surface->w;
	surface->rect.h = surface->surface->h;
	return surface;
}


/**
 * \fn void free_dm_surface(DM_Surface *surface)
 * \brief Releases the memory of the DM_Surface.
 *
 * \param surface The DM_Surface to free.
 */
void free_dm_surface(DM_Surface *surface)
{
	SDL_FreeSurface(surface->surface);
	free(surface);
}


/**
 * \fn SDL_Surface* str_to_surface(char *font_name, char *str)
 * \brief Makes a surface from a string.
 *
 * Transforms a string into a SDL_Surface that can be used
 * with the SDL.
 *
 * \param font_name The font name (ex. "font_main.png").
 * \param str The string containing the wanted text. WARNING: only ASCII
 *            chars can be handled.
 *
 * \return A pointer on a SDL_Surface containing the text.
 */
SDL_Surface* str_to_surface(char *font_name, char *str)
{
	SDL_Surface *font = load_resource(font_name);
	SDL_SetAlpha(font, 0, SDL_ALPHA_OPAQUE);
	SDL_Surface *text = NULL;
	int char_width = font->w / 10;
	int char_height = font->h / 10;
	int columns = 0;
	int lines = 1;
	int counter = 0;
	int i;
	SDL_Rect font_rect;
	SDL_Rect text_rect;
	//Count the number of columns and lines
	for (i=0 ; i<strlen(str) ; i++)
	{
		//If it is not a printable char, skip it
		if ((str[i] < '!' || str[i] > '~') && str[i] != ' ' && str[i] != '\n')
		{
			continue;
		}
		//Number of lines
		if (str[i] == '\n')
		{
			lines++;
			counter = 0;
			continue;
		}
		//Columns is equal to the largest line
		counter++;
		if (counter > columns)
		{
			columns = counter;
		}
	}
	//Initialize the text surface
	text = SDL_CreateRGBSurface(
			SDL_HWSURFACE,
			char_width * columns,
			char_height * lines,
			32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
			);
	SDL_FillRect(text, 0, SDL_MapRGBA(text->format, 0, 0, 0, 0));
	//Blit chars
	text_rect.x = 0;
	text_rect.y = 0;
	font_rect.w = char_width - 1;
	font_rect.h = char_height;
	for (i=0 ; i<strlen(str) ; i++)
	{
		//If it is not a printable char, skip it
		if ((str[i] < '!' || str[i] > '~') && str[i] != ' ' && str[i] != '\n')
		{
			continue;
		}
		//Newline
		if (str[i] == '\n')
		{
			text_rect.y += char_height;
			text_rect.x = 0;
			continue;
		}
		//Calculate the char places in the font sprite, and blit it
		if (str[i] >= '!' && str[i] <= '~')
		{
			font_rect.x = ((str[i] - '!') % 10) * char_width;
			font_rect.y = ((str[i] - '!') / 10) * char_height;
			SDL_BlitSurface(font, &font_rect, text, &text_rect);
		}
		text_rect.x += char_width;
	}
	//Free the memory
	SDL_FreeSurface(font);
	//Return the surface
	return text;
}


/**
 * \fn Mix_Chunk* load_sound_resource(char *resource_name)
 * \brief Loads a sound resource.
 *
 * Searches the sound in different paths and loads it. If it can not find
 * or load the resource, it stops the program and displays an error.
 *
 * NOTE: Only the PCM (.wav) format is supported.
 *
 * \param resource_name The resource name (ex. "sound.wav").
 *
 * \return Returns a pointer on a Mix_Chunk containing the sound.
 */
Mix_Chunk* load_sound_resource(char *resource_name)
{
	Mix_Chunk *sound = NULL;
	char filepath[255];
	//Try to load form the installation path
	#ifdef LINUX
	sprintf(
			filepath,
			"/usr/share/games/%s/sounds/%s",
			APP_NAME,
			resource_name
			);
	#endif
	#ifdef MAC_OS
	sprintf(
			filepath,
			"./%s.app/Contents/Resources/sounds/%s",
			APP_PR_NAME,
			resource_name
			);
	#endif
	sound = Mix_LoadWAV(filepath);
	//Try to load from local path
	if (sound == NULL)
	{
		sprintf(filepath, "./sounds/%s", resource_name);
		sound = Mix_LoadWAV(filepath);
	}
	if (sound == NULL)
	{
		sprintf(filepath, "../sounds/%s", resource_name);
		sound = Mix_LoadWAV(filepath);
	}
	//If the resource can not be loaded, display an error and exit
	if (sound == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_name);
		exit(EXIT_FAILURE);
	}
	//Return the sound
	return sound;
}


/**
 * \fn Mix_Music* load_music_resource(char *resource_name)
 * \brief Loads a music resource.
 *
 * Searches the music in different paths and loads it. If it can not find
 * or load the resource, it stops the program and displays an error.
 *
 * NOTE: OGG/Vorbis (.ogg), PCM (and maybe MP3) formats are supported.
 *
 * \param resource_name The resource name (ex. "music.ogg").
 *
 * \return Returns a pointer on a Mix_Music containing the music.
 */
Mix_Music* load_music_resource(char *resource_name)
{
	Mix_Music *music = NULL;
	char filepath[255];
	//Try to load form the installation path
	#ifdef LINUX
	sprintf(
			filepath,
			"/usr/share/games/%s/musics/%s",
			APP_NAME,
			resource_name
			);
	#endif
	#ifdef MAC_OS
	sprintf(
			filepath,
			"./%s.app/Contents/Resources/musics/%s",
			APP_PR_NAME,
			resource_name
			);
	#endif
	music = Mix_LoadMUS(filepath);
	//Try to load from local path (devel)
	if (music == NULL)
	{
		sprintf(filepath, "./musics/%s", resource_name);
		music = Mix_LoadMUS(filepath);
	}
	if (music == NULL)
	{
		sprintf(filepath, "../musics/%s", resource_name);
		music = Mix_LoadMUS(filepath);
	}
	//If the resource can not be loaded, display an error and exit
	if (music == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_name);
		exit(EXIT_FAILURE);
	}
	//Return the music
	return music;
}


