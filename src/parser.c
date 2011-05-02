/****************************************************************************
 *                                                                          *
 *  This file is part of Damn Monkey                                        *
 *                                                                          *
 *  Copyright (C) 2010 - 2011  Fabien LOISON, Mathilde BOUTIGNY,            *
 *  Vincent PEYROUSE, Germain CARRÉ and Matthis FRENAY                      *
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
 * \file parser.c
 * \brief Contains all functions needed to parse csv files (map, collides, sprites,...)
 */


#include "parser.h"


int is_white_char(char c) {
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/**
 * \fn DM_Line_Splited* split(char *str, char separator)
 * \brief Parse the line considered and return an array of string.
 *
 * This function read the string in order to create an array of string
 *
 * \param string The string to split.
 * \param separator The separator char (ex : ';').
 * \return A DM_Line_Splited containing the array.
 */
DM_Line_Splited* split(char *str, char separator)
{
	//Variables declaration
	char *buffer = malloc(sizeof(char) * strlen(str));
	DM_Line_Splited *splited_line = malloc(sizeof(DM_Line_Splited));
	if (splited_line == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	int numb_fields = 0;
	int field_size = 0;
	int field = 0;
	//Count the number of fields
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == separator)
		{
			numb_fields++;
		}
		i++;
	}
	//Allocate the memory in the DM_Line_Splited struct
	splited_line->parameters_int = numb_fields;
	splited_line->parameters = malloc(numb_fields * sizeof(char*));
	if (splited_line->parameters == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//Get the fields content
	i = 0;
	while (str[i] != '\0')
	{
		field_size = 0;
		while (str[i] != '\0')
		{
			if (str[i] != separator)
			{
				if (!is_white_char(str[i]))
				{
					buffer[field_size] = str[i];
					field_size++;
				}
			}
			else
			{
				buffer[field_size] = '\0';
				field_size++;
				splited_line->parameters[field] = malloc(field_size * sizeof(char));
				if (splited_line->parameters[field] == NULL)
				{
					fprintf(stderr, "E: Cannot allocate memory.");
					exit(EXIT_FAILURE);
				}
				strcpy(splited_line->parameters[field], buffer);
				break;
			}
			i++;
		}
		i++;
		field++;
	}
	return splited_line;
}


/**
 * \fn void free_dm_line_splited(DM_Line_Splited *line_splited)
 * \brief Releases the memory allowed to the DM_Line_Splited.
 *
 * This function releases the memory allowed to the DM_Line_Splited.
 *
 * \param surface The DM_Line_Splited name. 
 * \return Nothing.
 */
void free_dm_line_splited(DM_Line_Splited *line_splited)
{
	int i;
	for (i=0 ; i<line_splited->parameters_int ; i++)
	{
		free(line_splited->parameters[i]);
	}
	free(line_splited->parameters);	
	free(line_splited);
}


/**
 * \fn DM_Splited* read_file(char *resource_path)
 * \brief Read a csv file.
 *
 * This function read the csv file in order to create an array of string
 *
 * \param resource_path The file path.
 * \return A DM_Splited structure.
 */
DM_Splited* read_file(char *resource_path)
{
	char buffer[1024];
	DM_Splited *splited = malloc(sizeof(DM_Splited));
	if (splited == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	FILE *file = NULL;
	int numb_lines = 0;
	int line = 0;
	char filepath[128];
	//Open the file
	#ifdef LINUX
	strcpy(filepath, "/usr/share/games/");
	strcat(filepath, APP_NAME);
	strcat(filepath, "/");
	strcat(filepath, resource_path);
	#endif
	#ifdef WINDOWS
 	//TODO
	#endif
	#ifdef MAC_OS
	strcpy(filepath, "./Damn Monkey.app/Contents/Resources");
	strcat(filepath, resource_path);
	#endif
	file = fopen(filepath,"r");
	//Try to load from local path (devel)
	if (file == NULL)
	{
		strcpy(filepath, "./");
		strcat(filepath, resource_path);
		file = fopen(filepath,"r");
	}
	if (file == NULL)
	{
		strcpy(filepath, "../");
		strcat(filepath, resource_path);
		file = fopen(filepath,"r");
	}
	//If the resource can not be loaded, display an error and exit
	if (file == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_path);
		exit(EXIT_FAILURE);
	}
	//Count the number of interresting lines
	while (fgets(buffer, 1024, file) != NULL)
	{
		if (buffer[0] != '#' && buffer[0] != '\r' && buffer[0] != '\n')
		{
			numb_lines++;
		}
	}
	//Allocate the memory of the DM_Splited
	splited->items_int = numb_lines;
	splited->lines_array = malloc(numb_lines * sizeof(DM_Line_Splited*));
	//Let's go ! (get the lines)
	rewind(file);
	while (fgets(buffer, 1024, file) != NULL)
	{
		if (buffer[0] != '#' && buffer[0] != '\r' && buffer[0] != '\n')
		{
			splited->lines_array[line] = split(buffer, ';');
			line++;
		}
	}
	//Close the file
	fclose(file);
	return splited;
}


/**
 * \fn void free_dm_splited(DM_Splited *splited)
 * \brief Releases the memory allowed to the DM_Splited.
 *
 * This function releases the memory allowed to the DM_Splited.
 *
 * \param surface The DM_Splited name. 
 * \return Nothing.
 */
void free_dm_splited(DM_Splited *splited)
{
	int i;
	for (i=0 ; i<splited->items_int ; i++)
	{
		free_dm_line_splited(splited->lines_array[i]);
	}
	free(splited->lines_array);	
	free(splited);
}


