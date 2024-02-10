#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <ctype.h>

#define INIT_PATH "cache/init.init"
#define FIT_PATH "cache/fit.fit"

#define NO_INIT_NO_FIT (init_status == 1 && fit_status == 1)
#define INIT_DONE_NO_FIT (init_status == 0 && fit_status == 1)
#define INIT_DONE_FIT_DONE (init_status == 0 && fit_status == 0)

int getFileStatus(FILE **fp, const char *name);
int fileCreate(FILE **fp, const char *name);

#endif