#include "common.h"

int getFileStatus(FILE **fp, const char *name)
{
	if ((*fp = fopen(name, "r")) == NULL)
	{
    	return 1;
	}
	fclose(*fp);
	return 0;
}

int fileCreate(FILE **fp, const char *name)
{
	*fp = fopen(name, "w");
	return 0;
}

void saveStringArg(char **dist, char* arg)
{
	int len_name = strlen(arg)+1;	//with '\0'
	char *name = (char*)malloc(len_name*sizeof(char));
	strcpy(name, arg);
	*dist = name;
	return;
}

void error(const char *report)
{
	printf("%s\n", report);
	exit(EXIT_SUCCESS);
}
