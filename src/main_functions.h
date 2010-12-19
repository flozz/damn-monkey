#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED


#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"

#include "conf.h"


SDL_Surface* load_ressource(char *ressource_name);
SDL_Surface* str_to_surface(char *font_name, char *str);


#endif //MAIN_MENU_H_INCLUDED

