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
	dataset->file_name = file_name;
	dataset->separator = sep;

	fclose(fp);

	return 0;
}

int findTarget(DATASET *dataset, char *target)
{
	int match = 0;
	int number_target_col = 0;
	while (*(dataset->col_names) != NULL)
	{
		if (strcmp(target, *(dataset->col_names))==0)
		{
			match++;
			dataset->number_target_col = number_target_col;
		}
		number_target_col++;
		(dataset->col_names)++;
	}
	dataset->target_name = target;
	return match;
}

int loadData(DATASET *dataset, double ***X, double **y)
{
	FILE *fp;
	if ((fp = fopen(dataset->file_name, "r")) == NULL)
	{
		fclose(fp);
    	return NOT_EXIST;
	}

	double **_X = (double**)malloc(dataset->num_rows*sizeof(double*));
	double *_y = (double*)malloc(dataset->num_rows*sizeof(double));

	int len_string = dataset->num_col*NUMBER_LENGHT;
	char *string = (char*)malloc(len_string*sizeof(char));
	fgets(string, len_string, fp);

	int flag;
	int num_col = dataset->num_col;
	bool viseted = false;
	int j = 1;

	for (int i = 0; i < dataset->num_rows; ++i)
	{
		fgets(string, len_string, fp);
		_X[i] = (double*)malloc((dataset->num_col-1)*sizeof(double));

		viseted = false;
		num_col = dataset->num_col;
		j = 1;

		char *istr;
		istr = strtok (string, dataset->separator);

		if (dataset->number_target_col == 0)
		{
			flag = sscanf(istr, "%lf", &_y[i]);
			//_y[i] = atof(istr);
			num_col--;
			viseted = true;
			j--;
		}

		else
		{
			flag = sscanf(istr, "%lf", &_X[i][0]);
			//_X[i][0] = atof(istr);
		}

		if (flag == 0) return INVALID_DATA;

		for (; j < num_col; ++j)
		{
			istr = strtok(NULL, dataset->separator);

			if (j == dataset->number_target_col && viseted == false)
			{
				flag = sscanf(istr, "%lf", &_y[i]);
				//_y[i] = atof(istr);
				num_col--;
				j--;
				viseted = true;
			}

			else if (j != dataset->number_target_col || viseted == true)
			{
				flag = sscanf(istr, "%lf", &_X[i][j]);
				//_X[i][j] = atof(istr);
			}

			if (flag == 0) return INVALID_DATA;

		}
		memset(string, '\0', len_string);
	}

	(*X) = _X;
	(*y) = _y;

	return 0;

}