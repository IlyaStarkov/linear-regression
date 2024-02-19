#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct DATASET
{
	char *file_name;
	char *separator;
	char *target_name;
	char **col_names;
	unsigned int number_target_col;
	unsigned int num_col;
	unsigned int num_rows;

} DATASET;

#define NOT_EXIST 1
#define INVALID_SEPARATOR 2
#define INVALID_DATA 3
#define NUMBER_LENGHT 32


int getDatasetInfo(DATASET *dataset, char *file_name, char *sep);
int loadData(DATASET *dataset, double ***X, double **y);
int findTarget(DATASET *dataset, char *target);

#endif