#include <stdio.h>
#include <string.h>
#include "common.h"
#include "getopt.h"
#include "model.h"
#include "data_loader.h"

FILE *init;
FILE *fit;

int c;
int longindex = 0;

//init options
const char short_init_options[] = "hipm:";
const struct option long_init_options[] =
{
	{"help", no_argument, NULL, 'h'},
 	{"method", required_argument, NULL, 'm'},
 	{"intercept", no_argument, NULL, 'i'},
 	{"positive", no_argument, NULL, 'p'},
 	{"njobs", required_argument, NULL, '2'},
 	{NULL, 0, NULL, 0}
};

//fit options
const char short_fit_options[] = "hy:s:";
const struct option long_fit_options[] =
{
	{"help", no_argument, NULL, 'h'},
 	{"target", required_argument, NULL, 'y'},
	{"separator", required_argument, NULL, 's'},
 	{"clear", no_argument, NULL, '1'},
 	{"dataset", required_argument, NULL, '2'},
 	{NULL, 0, NULL, 0}
};

//predict options


int main(int argc, char *const *argv)
{

	int init_status = getFileStatus(&init, INIT_PATH);
	int fit_status = getFileStatus(&fit, FIT_PATH);
	int check_invalid_argument = 0;

	if (NO_INIT_NO_FIT)	// init
	{

		LR_PARAMS params;
		defaultInit(&params);

		if (argc == 1)
		{
			fileCreate(&init, INIT_PATH);
			loadConfig(&init, &params);
			fclose(init);
			printf("%s\n", "linreg: default configuration has been loaded");
			return 0;
		}

		do
		{
			c = getopt_long(argc, argv, short_init_options, long_init_options, &longindex);

			switch(c)
			{
				case 'h':
				{
					printf("%s\n", "_help_");
					return 0;
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

				case '2':
				{
					printf("%s\n", "_n_jobs_");
					break;
				}

				default:
				{
					check_invalid_argument++;
				}

			}

		} while (c != -1);

		if (check_invalid_argument > 1)
		{
			error("linreg: param is invalid");
		}
		fileCreate(&init, INIT_PATH);
		loadConfig(&init, &params);
		fclose(init);
		printf("%s\n", "linreg: configuration has been loaded");
		return 0;
	}

	else if (INIT_DONE_NO_FIT)	// fit
	{
		
		FILE *input_file;
		DATASET dataset;
		char *dataset_name, *target_name, *separator = NULL;

		double **X = NULL;
		double *y = NULL;

		if (argc == 1)
		{
			printf("%s\n", "__help__");
			return 0;
		}

		do
		{

			c = getopt_long(argc, argv, short_fit_options, long_fit_options, &longindex);

			switch(c)
			{
				case 'h':
				{
					printf("%s\n", "_help_");
					break;
				}

				case 'y':
				{
					saveStringArg(&target_name, optarg);
					//printf("%s\n", target_name);
					break;
				}

				case 's':
				{
					saveStringArg(&separator, optarg);
					//printf("%s\n", separator);
					break;
				}

				case '1':
				{
					if (remove(INIT_PATH))
					{
						printf("%s\n", "linreg: the configuration not exist");
					}
					else
					{
						printf("%s\n", "linreg: the model configuration has been cleared");
					}

					return 0;
				}

				case '2':
				{

					if (getFileStatus(&input_file, optarg))
					{
						error("linreg: cannot open the file");
					}
					else
					{
						saveStringArg(&dataset_name, optarg);				
					}

					break;
				}

				default:
				{
					check_invalid_argument++;
				}

			}

		} while (c != -1);

		if (check_invalid_argument > 1)
		{
			error("linreg: param is invalid");
		}

		/*check dataset*/
		if (getDatasetInfo(&dataset, dataset_name, separator) == INVALID_SEPARATOR)
		{
			error("linreg: separator is invalid");
		}

		int is_target = findTarget(&dataset, target_name);

		if (is_target == 0)
		{
			error("linreg: target not found");
		}

		else if (is_target > 1)
		{
			error("linreg: there must be only one target column");
		}
		
		//LOAD DATA

		int loader_report = loadData(&dataset, &X, &y);

		if (loader_report == INVALID_DATA)
		{
			error("linreg: there must be no text data in the input file");
		}

		//START FIT

		//CREATE CACHE-FILE
	}

	else if (INIT_DONE_FIT_DONE)	//predict
	{
		/* code */
	}

	return 0;
}
