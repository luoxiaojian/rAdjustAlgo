#include "rAlgo.h"

#define DET_NUM 20000

char **selfSet;
int *matrix, ma, r1min, rcmax;

void initMat()
{
	int i, j;
	matrix=(int *)malloc(sizeof(int)*ma);
	for(i=0; i<ma; i++)
		matrix[i]=0;
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
	int i, r, tag;
	FILE *fout;

	if(argc<3)
	{
		printf("Usage: ./case2 <r1_min> <r2_max>\n");
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

	for(i=0; DET_NUM; i++)
	{
		tag=getDetector(r1min, rcmax);
		matrix[tag[i]-r1min]+=1;
	}

	fout=fopen("case2.out","w");
	for(r=r1min; r<=rcmax; r++)
		printf("r=%d      %d\n", r, matrix[r-r1min]);
	for(r=r1min; r<=rcmax; r++)
		fprintf(fout, "r=%d      %d\n", r, matrix[r-r1min]);
	fflush(fout);
	fclose(fout);

	return 0;
}
