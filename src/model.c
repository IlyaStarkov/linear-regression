#include "model.h"


void setMethod(LR_PARAMS *params, const char *method)
{
	params->method = method;
	return;
}

void setFitIntercept(LR_PARAMS *params, bool fit_intercept)
{
	params->fit_intercept = fit_intercept;
	return;
}

void setPositive(LR_PARAMS *params, bool positive)
{
	params->positive = positive;
	return;
}

/*void setNjobs(LR_PARAMS *params, bool n_jobs)
{
	params->positive = n_jobs;
	return;
}*/

void defaultInit(LR_PARAMS *params)
{
	setMethod(params, "least squares");
	setFitIntercept(params, true);
	setPositive(params, false);
	return;
}

int loadConfig(FILE **fp, LR_PARAMS *params)
{
	fprintf(*fp, "%s = %s\n", "METHOD", params->method);
	fprintf(*fp, "%s = %s\n", "FIT_INTERCEPT", params->fit_intercept ? "TRUE" : "FALSE");
	fprintf(*fp, "%s = %s\n", "POSITIVE", params->positive ? "TRUE" : "FALSE");
	//fprintf(*fp, "%s = %s\n", "N_JOBS", params->n_jobs ?  iota(params->n_jobs): "NONE");
	return 0;
}



