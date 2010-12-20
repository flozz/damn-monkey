#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/**
 * \file menu.h
 * \brief The header file of menu.c.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"

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
void free_menu(DM_Menu *menu);


#endif //MENU_H_INCLUDED

