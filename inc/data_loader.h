#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#define NOT_EXIST 1
#define INVALID_SEPARATOR 2

int getColNames(char ***col, const char *dataset, const char *sep);

#endif