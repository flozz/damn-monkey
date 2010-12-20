#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/**
 * \file menu.h
 * \brief The header file of menu.c.
 */


#include <stdio.h>
#include <stdio.h>

#ifdef LINUX
#include "SDL.h"
#endif

#ifdef MAC_OS
#include <SDL/SDL.h>
#endif

#ifdef WINDOWS
//TODO
#endif

#include "main_functions.h"


/**
 * \struct DM_Menu
 * \brief Contain all the informations needed for building a menu.
 */
typedef struct DM_Menu DM_Menu;
struct DM_Menu
{
	int numb_of_items;   /*!< Number of items in the menu. */
	int selected;        /*!< The index of the selected item. */
	char items[250];     /*!< A string that list the menu items (separated by a '\\n'). */
	SDL_Surface *menu;   /*!< The image of the menu. */
	SDL_Surface *cursor; /*!< The cursor that point on the selected item. */
};


DM_Menu* new_menu(char *items, char *font_name, char *cursor);


#endif //MENU_H_INCLUDED

