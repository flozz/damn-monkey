#ifndef MAIN_FUNCTIONS_H_INCLUDED
#define MAIN_FUNCTIONS_H_INCLUDED


/**
 * \file main_functions.h
 * \brief The header file of main_functions.c.
 */


#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


/**
 * \struct DM_Surface
 * \brief Structure for refreshing SDL_Surface.
 */
typedef struct DM_Surface DM_Surface;
struct DM_Surface
{
	SDL_Surface *surface; /*!< The surface. */
	SDL_Rect rect;        /*!< The rectangle. */
};

/**
 * \struct DM_Splited
 * \brief Structure for parsing files.
 */
typedef struct DM_Splited DM_Splited;
struct DM_Splited
{
	int parameters_int;   /*!< The number of strings in the array */
	char **parameters;    /*!< The array of strings */
};


SDL_Surface* load_resource(char *resource_name);
DM_Surface* load_resource_as_dm_surface(char *resource_name);
void free_dm_surface(DM_Surface *surface);
SDL_Surface* str_to_surface(char *font_name, char *str);
Mix_Chunk* load_sound_resource(char *resource_name);
Mix_Music* load_music_resource(char *resource_name);
DM_Splited* split(char *string, char separator);

#endif //MAIN_FUNCTIONS_H_INCLUDED

