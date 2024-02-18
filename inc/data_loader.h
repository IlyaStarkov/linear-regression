#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct DATASET
{
	char **col_names;
	unsigned int num_col;
	unsigned int num_rows;
} DATASET;

#define NOT_EXIST 1
#define INVALID_SEPARATOR 2


int getDatasetInfo(DATASET *dataset, char *file_name, char *sep);
int findTarget(char **col_names, char *target);

#endif