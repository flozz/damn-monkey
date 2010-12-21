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
	int numb_of_items;     /*!< Number of items in the menu. */
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


/**
 * \struct DM_Menu_effect
 * \brief Contain all the informations for add effect and refresh a DM_Menu.
 */
typedef struct DM_Menu_effect DM_Menu_effect;
struct DM_Menu_effect
{
	SDL_Surface *bg;     /*!< The menu background. */
	DM_Menu *menu;       /*!< The DM_Menu to refresh. */
	SDL_Surface *screen; /*!< The main surface on which to draw. */
	SDL_TimerID timer;   /*!< The SDL Timer id. (SDL_AddTimer()) */
};


DM_Menu* new_menu(char *items, char *font_name, char *hl_font_name, char *cursor);
void free_menu(DM_Menu *menu);
void draw_menu(SDL_Surface *screen, DM_Menu *menu);
void menu_change_selected(DM_Menu *menu, int increment);
Uint32 menu_glow_effect_cb(Uint32 interval, void *arg);
Uint32 menu_blink_effect_cb(Uint32 interval, void *arg);


#endif //MENU_H_INCLUDED

