#include "data_loader.h"

int getColNames(char ***col, const char *file_name, const char *sep)
{
	FILE *fp;
	if ((fp = fopen(file_name, "r")) == NULL)
	{
		fclose(fp);
    	return NOT_EXIST;
	}

	int num_sym_in_header, col_num, c;
	num_sym_in_header = -1; //without CRLF
	col_num = 1;
	c = '\0';

	while (c != '\n')
	{
		c = fgetc(fp);
		num_sym_in_header++;
		if (c == sep[0]) col_num++;
	}

	if (col_num == 1)
	{
		fclose(fp);
		return INVALID_SEPARATOR;
	}

	char *header = (char*)malloc(num_sym_in_header*sizeof(char));
	char **col_name = (char**)malloc(col_num*sizeof(char*));

	fseek(fp , 0, SEEK_SET);
	fgets(header, num_sym_in_header, fp);

	char *istr;
	istr = strtok(header, sep);
	int name_index = 0;
	while (istr != NULL)
	{
		col_name[name_index] = istr;
		istr = strtok (NULL,sep);
		name_index++;
	}

	*col = col_name;

	fclose(fp);

	return 0;
}

/*int getDatasetInfo(DATASET *dataset, char *file_name)
{

}*/