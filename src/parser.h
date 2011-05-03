#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED


/**
 * \file parser.h
 * \brief The header file of parser.c.
 */


#include "conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \struct DM_Line_Splited
 * \brief Structure for parsing files.
 */
typedef struct DM_Line_Splited DM_Line_Splited;
struct DM_Line_Splited
{
	int parameters_int;   /*!< The number of strings in the array */
	char **parameters;    /*!< The array of strings */
};


/**
 * \struct DM_Splited
 * \brief Structure for parsing files.
 */
typedef struct DM_Splited DM_Splited;
struct DM_Splited
{
	int items_int;                    /*!< The number of DM_Line_Splited in the array */
	DM_Line_Splited **lines_array;    /*!< The array of DM_Line_Splited */
};


int is_white_char(char c);
DM_Line_Splited* split(char *str, char separator);
void free_dm_line_splited(DM_Line_Splited *line_splited);
DM_Splited* read_file(char *resource_path);
void free_dm_splited(DM_Splited *splited);

#endif //PARSER_H_INCLUDED

