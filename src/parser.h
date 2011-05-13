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
 * \file parser.h
 * \brief The header file of parser.c.
 */


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED


#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \struct DM_Line_Splited
 * \brief Contains one splited line.
 */
typedef struct DM_Line_Splited DM_Line_Splited;
struct DM_Line_Splited
{
	int parameters_int; /*!< The number of items in the array. */
	char **parameters;  /*!< The array that contains the splited string. */
};


/**
 * \struct DM_Splited
 * \brief Contains all the splited lines of a file.
 */
typedef struct DM_Splited DM_Splited;
struct DM_Splited
{
	int items_int;                 /*!< The number of lines in the array. */
	DM_Line_Splited **lines_array; /*!< The array that contains all the splited lines of the file. */
};


DM_Line_Splited* split(char *str, char separator);
void free_dm_line_splited(DM_Line_Splited *line_splited);
DM_Splited* read_file(char *resource_path);
void free_dm_splited(DM_Splited *splited);
/** \cond */ //Hide the "privates" functions for Doxygen
int _is_white_char(char c);
/** \endcond */


#endif //PARSER_H_INCLUDED

