#include "data_loader.h"

int getDatasetInfo(DATASET *dataset, char *file_name, char *sep)
{
	FILE *fp;
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		fclose(fp);
    	return NOT_EXIST;
	}

	int num_sym_in_header, c;
	num_sym_in_header = -1; //without CRLF
	unsigned int num_col = 1;
	unsigned int num_rows = 0;
	c = '\0';

	while (c != '\n')
	{
		c = fgetc(fp);
		num_sym_in_header++;
		if (c == sep[0]) num_col++;
	}
	if (num_col == 1)
	{
		fclose(fp);
		return INVALID_SEPARATOR;
	}


	while (c != EOF)
	{
		c = fgetc(fp);
		if (c == '\n') num_rows++;
	}

	char *header = (char*)malloc(num_sym_in_header*sizeof(char));
	char **col_names = (char**)malloc(num_col*sizeof(char*));
	fseek(fp , 0, SEEK_SET);
	fgets(header, num_sym_in_header, fp);
	char *istr;
	istr = strtok(header, sep);
	int name_index = 0;
	while (istr != NULL)
	{
		col_names[name_index] = istr;
		istr = strtok (NULL,sep);
		name_index++;
	}

	col_names[num_col] = NULL;	//???

	dataset->col_names = col_names;
	dataset->num_col = num_col;
	dataset->num_rows = num_rows;

	fclose(fp);

	return 0;
}

int findTarget(char **col_names, char *target)
{
	int match = 0;
	while (*col_names != NULL)
	{
		if (strcmp(target, *col_names)==0) match++;
		col_names++;
	}
	return match;
}