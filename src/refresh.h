#ifndef REFRESH_H_INCLUDED
#define REFRESH_H_INCLUDED


/**
 * \file refresh.h
 * \brief The header file of refresh.c.
 */


#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#ifdef LINUX
#include "SDL.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#endif

#ifdef WINDOWS
#include <SDL.h>
#endif

#include "main_functions.h"


/**
 * \struct DM_Refresh_Layer
 * \brief A Layer.
 */
typedef struct DM_Refresh_Layer DM_Refresh_Layer;
struct DM_Refresh_Layer
{
	SDL_Surface *screen;          /*!< The main SDL_Surface. */
	struct DM_Refresh_Item *next; /*!< Pointer on the first item of the list */
};


/**
 * \struct DM_Refresh_Item
 * \brief An object to refresh.
 */
typedef struct DM_Refresh_Item DM_Refresh_Item;
struct DM_Refresh_Item
{
	int id;                       /*!< A unique identifier for the item. */
	void *object;                 /*!< Pointer on the object. */
	void (*callback)();           /*!< The callback function that blit the object. */
	struct DM_Refresh_Item *next; /*!< Pointer on the next item of the list. */
};


void refresh_init(SDL_Surface *screen);
void refresh_destroy();
int ref_object(DM_Refresh_Layer *layer, void *object, void (*callback)());
void deref_object(DM_Refresh_Layer *layer, int id);
Uint32 refresh_cb(Uint32 interval, void *arg);
int get_id();


#endif //REFRESH_H_INCLUDED

