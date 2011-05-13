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
 * \file menu.h
 * \brief The header file of menu.c.
 */


#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


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
#include <SDL.h>
#endif

#include "main_functions.h"


/**
 * \struct DM_Menu
 * \brief Contains all the informations needed for building a menu.
 */
typedef struct DM_Menu DM_Menu;
struct DM_Menu
{
	int numb_of_items;     /*!< The number of items in the menu. */
	int selected;          /*!< The index of the selected item. */
	char items[250];       /*!< A string that list the menu items (separated by a '\\n'). */
	SDL_Surface *menu;     /*!< The image of the menu. */
	SDL_Rect menu_rect;    /*!< The position of the menu. */
	SDL_Surface *cursor;   /*!< The cursor that point on the selected item. */
	SDL_Rect cursor_rect;  /*!< The position of the cursor. */
	SDL_Surface *menu_hl;  /*!< The highlighted version of the menu. */
	SDL_Rect menu_hl_rect; /*!< The coordinate of the selected item. */
	int hl_alpha;          /*!< The current alpha value of the hl. WARNING: can be negative. */
};


DM_Menu* new_menu(char *items, char *font_name, char *hl_font_name, char *cursor);
void free_menu(DM_Menu *menu);
void draw_menu(SDL_Surface *screen, DM_Menu *menu);
void menu_change_selected(DM_Menu *menu, int increment);
void menu_glow_effect_cb(void *object, SDL_Surface *screen);
void menu_blink_effect_cb(void *object, SDL_Surface *screen);


#endif //MENU_H_INCLUDED

