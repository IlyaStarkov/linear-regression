#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <ctype.h>

#define CACHE_PATH "save/.lrcache"

int fileOpen(FILE **fp, const char *name);
int fileCreate(FILE **fp, const char *name);

#endif