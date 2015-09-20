
#ifndef	_HEADER_H_
#define _HEADER_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINE_NUM 2000
#define STR_LENGTH 80

void generateRandStr(char *str);

void loadSelfSet(char *filename, char **selfSet);

float avgHDist(char **selfSet);

float avgHDistRand(char **selfSet, int iter);

int rAlgo(char *str, char **selfSet, int r1, int c);

#endif



