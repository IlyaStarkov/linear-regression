#include "common.h"

int fileOpen(FILE **fp, const char *name)
{
	if ((*fp = fopen(name, "r")) == NULL)
	{
    	return 1;
	}

	return 0;
}

int fileCreate(FILE **fp, const char *name)
{
	*fp = fopen(name, "w");
	return 0;
}
