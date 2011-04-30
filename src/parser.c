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


/**
 * \fn DM_Line_Splited* split(char *string, char separator)
 * \brief Parse the line considered and return an array of string.
 *
 * This function read the string in order to create an array of string
 *
 * \param string The string to split.
 * \param separator The separator char (ex : ';').
 * \return A DM_Line_Splited containing the array.
 */
DM_Line_Splited* split(char *string, char separator)
{
	//Future return initialization
	DM_Line_Splited *splited = malloc(sizeof(DM_Line_Splited));
	if (splited == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//Some variables initialization
	int counter = 0;
	int items_int = 0;
	char buffer_c;
	//String buffer initialization
	char *buffer = malloc(strlen(string) * sizeof(char));
	if (buffer == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//First loop allowing the counting of items for allocations operations
	for (counter=0 ; counter<strlen(string) ; counter++)
	{
		if (string[counter] == separator)
		{
			items_int++;
		}
		else if (string[counter] == ' ' || string[counter] == '\t' || string[counter] == '\r' || string[counter] == '\n')
		{
			continue;
		}
		else
		{
			continue;
		}
	}
	
	//Allocation of the first dimension of the parameters array
	splited->parameters = malloc(items_int * sizeof(char*));
	if (splited->parameters == NULL)
	{
		fprintf(stderr, "E: Cannot allocate memory.");
		exit(EXIT_FAILURE);
	}
	//Assignation of the parameters_int thanks to the first loop
	splited->parameters_int = items_int;
	
	items_int = 0;
	
	//Second loop allowing the buffering and the creation of the second dimension of the parameters array
	buffer_c = string[0];
	//Detects if we have a common char and start buffering -> We got a new item
	if (buffer_c != ' ' && buffer_c != '\t' && buffer_c != '\r' && buffer_c != '\n' && buffer_c != separator)
	{
		strcpy(buffer, &buffer_c);	
	}
	for (counter=1 ; counter<strlen(string) ; counter++)
	{
		if (string[counter-1] == separator)
		{
			//Detects if we have an "uncommon" char just after the separator
			if (string[counter] == ' ' || string[counter] == '\t' || string[counter] == '\r' || string[counter] == '\n')
			{
				continue;
			}
			//Start of a new buffering -> We got a new item
			buffer_c = string[counter];
			strcpy(buffer, &buffer_c);
			continue;
		}
		//Separator found
		if (string[counter] == separator)
		{
			splited->parameters[items_int] = malloc(strlen(buffer) * sizeof(char)); //Allocatation of a new item in the array
			if (splited->parameters[items_int] == NULL)
			{
				fprintf(stderr, "E: Cannot allocate memory.");
				exit(EXIT_FAILURE);
			}
			strcpy(splited->parameters[items_int], buffer); //Assignation of the new item
			memset(buffer, '\0', strlen(buffer)); //Empty the buffer
			items_int++; //Incrementation of the parameters array "counter"
		}
		//Skip white spaces
		else if (string[counter] == ' ' || string[counter] == '\t' || string[counter] == '\r' || string[counter] == '\n')
		{
			continue;
		}
		//Buffer the char
		else
		{
			buffer_c = string[counter];
			strcat(buffer, &buffer_c);
		}
	}
	
	return splited;
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
	char *buffer = malloc(1000 * sizeof(char));
	memset(buffer, '\0', strlen(buffer));
	char filepath[255];
	char *buffer_c = malloc(sizeof(char));
	int items_int = 0;
	FILE *file = NULL;
	
	#ifdef LINUX
	strcpy(filepath, "/usr/share/games/");
	strcat(filepath, APP_NAME);
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
	}
	if (file == NULL)
	{
		strcpy(filepath, "../");
		strcat(filepath, resource_path);
	}
	//If the resource can not be loaded, display an error and exit
	if (file == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		*buffer_c = fgetc(file);
		while (*buffer_c != EOF)
		{
			if (*buffer_c == '#') //We got a comment
			{
				while (*buffer_c != '\n' && *buffer_c != '\r') //We read the entire line
				{
					*buffer_c = fgetc(file);
					
				}
				*buffer_c = fgetc(file);
				continue;
			}
			else if (*buffer_c == '\n' || *buffer_c == '\r') //We got a blank line
			{
				*buffer_c = fgetc(file);
			}
			else //Valid line
			{
				while (*buffer_c != '\n' && *buffer_c != '\r')
				{
					*buffer_c = fgetc(file);
				}
				items_int++;
				*buffer_c = fgetc(file);
			}
		}
	}
	
	rewind(file);
	
	DM_Splited *splited = malloc(sizeof(DM_Splited));
	if (splited == NULL)
	{
		fprintf(stderr, "E: Can not load the resource: %s\n", resource_path);
		exit(EXIT_FAILURE);
	}
	splited->items_int = items_int;
	splited->lines_array = malloc(items_int * sizeof(DM_Line_Splited));
	items_int = 0;
	
	*buffer_c = fgetc(file);
	while (*buffer_c != EOF)
	{
		if (*buffer_c == '#') //We got a comment
		{
			while (*buffer_c != '\n' && *buffer_c != '\r') //We read the entire line
			{
				*buffer_c = fgetc(file);
			}
			*buffer_c = fgetc(file);
			continue;
		}
		else if (*buffer_c == '\n' || *buffer_c == '\r') //We got a blank line
		{
			*buffer_c = fgetc(file);
			continue;
		}
		else //Valid line
		{
			strcpy(buffer, buffer_c);
			*buffer_c = fgetc(file);
			while (*buffer_c != '\n' && *buffer_c != '\r')
			{
				strcat(buffer, buffer_c);
				*buffer_c = fgetc(file);
			}
			splited->lines_array[items_int] = split(buffer, ';');
			items_int++;
			memset(buffer, '\0', strlen(buffer));
			*buffer_c = fgetc(file);
		}
	}
	
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

