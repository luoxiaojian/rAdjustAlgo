#include "rAlgo.h"

#define DET_NUM 20000

char **selfSet;

int **matrix, ma, r1min, rcmax;

void initMat()
{
	int i, j;
	matrix=(int **)malloc(sizeof(int *)*ma);
	for(i=0; i<ma; i++)
		matrix[i]=(int *)malloc(sizeof(int)*ma);
	for(i=0; i<ma; i++)
		for(j=0; j<ma; j++)
			matrix[i][j]=0;
}

int getDetector(int r1, int rc)
{
	char temp[STR_LENGTH+1];
	int r;
	while(1)
	{
		generateRandStr(temp);
		r=rAlgo(temp, selfSet, r1, rc+1-r1);
		if(r!=rc+1)
			return r;
	}
}

int main(int argc, char **argv)
{
	int i, j, rc, r1, count, r;

	FILE *fout;
	if(argc<3)
	{
		printf("Usage: ./case1 <r1_min> <r2_max>\n");
		exit(0);
	}

	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));

	loadSelfSet("sample_80_2000.out", selfSet);
	r1min=atoi(argv[1]);
	rcmax=atoi(argv[2]);
	ma=rcmax-r1min+1;

	initMat();

	for(rc=r1min; rc<=rcmax; rc++)
	{
		printf("rc=%d\n", rc);
		r1=r1min;
		count=0;
		while(count!=DET_NUM)
		{
			r=getDetector(r1, rc);
			matrix[r-r1min][rc-r1min]+=1;
			count+=1;
			printf("\t%d of %d\n", count, DET_NUM);
		}
	}

	fout=fopen("case1.out","w");
	for(rc=r1min; rc<=rcmax; rc++)
		for(r=r1min; r<=rc; r1++)
			printf("r=%d, rc=%d      %d\n", r, rc, matrix[r-r1min][rc-r1min]);
	for(rc=r1min; rc<=rcmax; rc++)
		for(r=r1min; r<=rc; r1++)
			fprintf(fout, "r=%d, rc=%d      %d\n", r, rc, matrix[r-r1min][r-r1min]);
	fflush(fout);
	fclose(fout);

	return 0;
}
