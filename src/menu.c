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
 * \file menu.c
 * \brief Contains all the functions for manipulating menus.
 */


#include "menu.h"


/**
 * \fn DM_Menu* new_menu(char *items, char *font_name, char *cursor)
 * \brief Create a new menu.
 *
 * \param items a string that contain the list of the items separated by a '\\n'
 *        (ex. "Start\nOptions\nQuit").
 * \param font_name The font resource name (ex. "font_main.png").
 * \param cursor the name of the resource that will be use as a cursor.
 * \return A pointer on a DM_Menu.
 */
DM_Menu* new_menu(char *items, char *font_name, char *cursor)
{
	DM_Menu *menu = malloc(sizeof(DM_Menu));
	//Count the number of items in the menu
	menu->numb_of_items = 1;
	int i;
	for (i=0 ; i<strlen(items) ; i++)
	{
		if (items[i] == '\n')
		{
			menu->numb_of_items += 1;
		}
	}
	//Select the first item by default
	menu->selected = 0;
	//Copy the item list
	strcpy(menu->items, items);
	//Generate the menu image
	menu->menu = str_to_surface(font_name, items);
	//Load the cursor image
	menu->cursor = load_resource(cursor);
	//Return the menu
	return menu;
}


/**
 * \fn void free_menu(DM_Menu *menu)
 * \brief Free the memory of a menu structure.
 *
 * \param screen The main surface (called screen in the main() function)
 *               on which to draw.
 * \param menu The DM_Menu to free.
 */
void free_menu(DM_Menu *menu)
{
	SDL_FreeSurface(menu->menu);
	SDL_FreeSurface(menu->cursor);
	free(menu);
}


/**
 * \fn void draw_menu(SDL_Surface *screen, DM_Menu *menu)
 * \brief Draw the menu with its cursor.
 *
 * \param menu The DM_Menu to draw.
 */
void draw_menu(SDL_Surface *screen, DM_Menu *menu)
{
	int item_height = menu->menu->h / menu->numb_of_items;
	menu->cursor_rect.x = menu->menu_rect.x - menu->cursor->w - 5;
	menu->cursor_rect.y = menu->menu_rect.y + menu->selected * item_height;
	SDL_BlitSurface(menu->menu, NULL, screen, &menu->menu_rect);
	SDL_BlitSurface(menu->cursor, NULL, screen, &menu->cursor_rect);
}


/**
 * \fn void menu_change_selected(DM_Menu *menu, int increment)
 * \brief Change the selected item of a menu.
 *
 * \param menu The DM_Menu.
 * \param increment The increment (+1 or -1).
 */
void menu_change_selected(DM_Menu *menu, int increment)
{
	menu->selected += increment;
	if (menu->selected < 0)
	{
		menu->selected = 0;
	}
	else if (menu->selected >= menu->numb_of_items)
	{
		menu->selected = menu->numb_of_items -1;
	}
}


