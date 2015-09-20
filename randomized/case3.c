#include "rAlgo.h"

#define EXP_TIME 1000

char **selfSet;
char **detector;
int *rvals;
int *dnum={200, 400, 600, 800, 1100, 1200}, dtimes=6;

int getDetector(int r1, int rc, char *str)
{
	int r;
	while(1)
	{
		generateRandStr(str);
		r=rAlgo(str, selfSet, r1, rc+1-r1);
		if(r!=rc+1)
			return r;
	}
}

void initDet(int r1, int rc)
{
	int i, r;
	for(i=0; i<1200; i++)
	{
		r=getDetector(r1, rc, detector[i]);
		rvals[i]=r;
	}
}

int checkSelfSet(char *str)
{
	int i, j, flag;
	for(i=0; i<LINE_NUM; i++)
	{
		flag=1;
		for(j=0; j<STR_LENGTH; j++)
		{
			if(str[j]!=selfSet[i][j])
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
			return 1;
	}
	return 0;
}

float calcPs(int num)
{
	char temp[STR_LENGTH+1];
	int i, j, count=0, flag;
	for(i=0; i<EXP_TIME; i++)
	{
		flag=0;
		generateRandStr(temp);
		for(j=0; j<num; j++)
		{
			if(match(detector[i], temp, rvals[i]))
			{
				count+=1;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			if(checkSelfSet(temp))
				count+=1;
		}
	}
	return ((float)count)/((float)EXP_TIME);
}

int main(int argc, char **argv)
{
	int i, r, tag, rc, rcmin, rcmax;
	FILE *fout;

	if(argc<3)
	{
		printf("Usage: ./case2 <rc_min> <rc_max>\n");
		exit(0);
	}


	rcmin=atoi(argv[1]);
	rcmax=atoi(argv[2]);

	selfSet=(char **)malloc(sizeof(char *)*LINE_NUM);
	for(i=0; i<LINE_NUM; i++)
		selfSet[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));
	detector=(char **)malloc(sizeof(char *)*1200);
	rvals=(int *)malloc(sizeof(int)*1200);
	for(i=0; i<1200; i++)
		detector[i]=(char *)malloc(sizeof(char)*(STR_LENGTH+1));

	loadSelfSet("sample_80_2000.out", selfSet);

	for(rc=rcmin; rc<rcmax; rc++)
	{
		initDet(rcmin, rc);
		for(j=0; j<dtimes; j++)
			printf("rc=%d, nr0=%d, ps=%f\n", rc, dnum[j], calcPs(dnum[j]));

	}


	return 0;
}
