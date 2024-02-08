#ifndef MODEL_H_
#define MODEL_H_

#include <stdbool.h>
#include <stdio.h>

typedef struct LR_PARAMS
{
	const char *method;
	bool fit_intercept;
	bool positive;
	int n_jobs;

} LR_PARAMS;

/* SETTERS */
void setMethod(LR_PARAMS *params, const char *method);
void setFitIntercept(LR_PARAMS *params, bool fit_intercept);
void setPositive(LR_PARAMS *params, bool positive);
void setNjobs(LR_PARAMS *params, bool n_jobs);


void defaultInit(LR_PARAMS *params);
int loadConfig(FILE **fp, LR_PARAMS *params);


#endif