#include "rAlgo.h"

int generateRand(int start, int end)
{
	srand((unsigned)time(NULL));
	return (rand()%(end-start)+start);
}

void generateRandStr(char *str)
{
	int bit, i;
	for(i=0; i<STR_LENGTH; i++)
	{
		bit=generateRand(0,2);
		str[i]=bit+'0';
	}
}

void loadSelfSet(char *filename, char **selfSet)
{
	FILE *fin;
	int i;
	fin=fopen(filename, "r");
	for(i=0; i<LINE_NUM; i++)
		fscanf(fin, "%s", selfSet[i]);
}

int hDist(char *s1, char *s2)
{
	int i, res=0;
	for(i=0; i<STR_LENGTH; i++)
		if(s1[i]!=s2[i])
			res+=1;
	return res;
}

float avgHDist(char **selfSet)
{
	int i, j;
	int total=0;
	int count=LINE_NUM*(LINE_NUM-1)/2;
	for(i=0; i<LINE_NUM-1; i++)
		for(j=i+1; j<LINE_NUM; j++)
			total+=hDist(selfSet[i], selfSet[j]);
	return ((float)total)/((float)count);
}

float avgHDistRand(char **selfSet, int iter)
{
	int i, src, tar;
	int count;
	for(i=0; i<iter; i++)
	{
		src=tar=0;
		while(src==tar)
		{
			src=generateRand(0, LINE_NUM);
			tar=generateRand(0, LINE_NUM);
		}
		count+=hDist(selfSet[src], selfSet[tar]);
	}
	return ((float)count)/((float)iter);
}

int strequal(char *str1, char *str2, int len)
{
	int i=0;
	for(i=0; i<len; i++)
		if(str1[i]!=str2[i])
			return 0;
	return 1;
}

int match(char *str1, char *str2, int r)
{
	int i, j;
	for(i=0; i<STR_LENGTH-r; i++)
		for(j=0; j<STR_LENGTH-r; j++)
			if(strequal(str1+i, str2+j, r))
				return 1;
	return 0;
}

int rAlgo(char *str, char **selfSet, int r1, int c)
{
	int i;
	int flag=0, r=r1;
	while(flag==0)
	{
		flag=1;
		for(i=0; i<LINE_NUM; i++)
		{
			if(match(str, selfSet[i], r))
			{
				flag=0;
				r=r+1;
				break;
			}
		}
		if(r==r1+c)
			break;
	}
	return r;
}

