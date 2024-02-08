#include <stdio.h>
#include <string.h>
#include "common.h"
#include "getopt.h"
#include "model.h"

FILE *cache;
LR_PARAMS params;

int c;
int longindex = 0;
const char short_options[] = "hipm:";

const struct option long_options[] =
{
	{"help", no_argument, NULL, 'h'},
 	{"method", required_argument, NULL, 'm'},
 	{"intercept", no_argument, NULL, 'i'},
 	{"positive", no_argument, NULL, 'p'},
 	{"clear", no_argument, NULL, '1'},
 	{"njobs", required_argument, NULL, '2'},
 	{NULL, 0, NULL, 0}
};

char type[49] = "unknown";

int main(int argc, char *const *argv)
{

	defaultInit(&params);
	
	/*int file_status = */fileOpen(&cache, CACHE_PATH);

	do
	{
		c = getopt_long(argc, argv, short_options, long_options, &longindex);

		switch(c)
		{
			case 'h':
			{
				printf("%s\n", "_help_");
				break;
			}
			
			case 'm':
			{
				if (strcmp("grad", optarg))
				{
					setMethod(&params, "Gradient descent");
				}
				break;
			}

			case 'i':
			{
				setFitIntercept(&params, false);
				break;
			}

			case 'p':
			{
				setPositive(&params, true);
				break;
			}

			case '1':
			{
				fclose(cache);
				if (remove(CACHE_PATH))
				{
					printf("%s\n", "The cache not exist");
				}
				else
				{
					printf("%s\n", "The cache has been cleared");
				}

				return 0;
			}

			case '2':
			{
				printf("%s\n", "_n_jobs_");
				break;
			}

		}

	} while (c != -1);

	fileCreate(&cache, CACHE_PATH);
	loadConfig(&cache, &params);
	fclose(cache);
	/*
	defaultInit(&params);

	int file_status = fileOpen(&cache, CACHE_PATH);

	if (argc == 1)
	{
		if (file_status)
		{
			//no arguments, no file
			//argHandler()
			printf("%s\n", "The default configuration has been loaded");
			fileCreate(&cache, CACHE_PATH);
			loadConfig(&cache, &params);
		}
		
		else if (!file_status)
		{
			//no arguments, file exist
			//argHandler()
			printf("%s\n", "Linear Regression is ready to fit");
		}
	}
	if (argc > 1)
	{
		if (argc == 2 && !strcmp(argv[1], "-clear"))
		{
			fclose(cache);
			if (remove(CACHE_PATH))
			{
				printf("%s\n", "The cache not exist");
			}
			else
			{
				printf("%s\n", "The cache has been cleared");
			}
			
			return 0;
		}
		if (file_status)
		{
			//few arguments, no file
			//argHandler()
			printf("%s\n", "The configuration has been loaded");
			fileCreate(&cache, CACHE_PATH);
			//loadConfig();
		}

		else if (!file_status)
		{
			///few arguments, file exist
			//argHandler()
			printf("%s\n", "Start to fit");
		}
	}

	fclose(cache);*/

	return 0;
}