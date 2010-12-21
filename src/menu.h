#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/**
 * \file menu.h
 * \brief The header file of menu.c.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conf.h"

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
	int numb_of_items;    /*!< Number of items in the menu. */
	int selected;         /*!< The index of the selected item. */
	char items[250];      /*!< A string that list the menu items (separated by a '\\n'). */
	SDL_Surface *menu;    /*!< The image of the menu. */
	SDL_Rect menu_rect;   /*!< The position of the menu */
	SDL_Surface *cursor;  /*!< The cursor that point on the selected item. */
	SDL_Rect cursor_rect; /*!< The position of the cursor */
};


DM_Menu* new_menu(char *items, char *font_name, char *cursor);
void free_menu(DM_Menu *menu);
void draw_menu(SDL_Surface *screen, DM_Menu *menu);
void menu_change_selected(DM_Menu *menu, int increment);


#endif //MENU_H_INCLUDED

