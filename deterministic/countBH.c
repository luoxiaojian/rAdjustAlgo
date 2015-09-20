#include <stdio.h>
#include <stdlib.h>

#define NS_SIZE 868264
#define S_SIZE 150
#define STR_LENGTH 22
#define TOTAL_NUM 1<<STR_LENGTH
#define R1 8
#define C 5
int selfSet[S_SIZE];
int *nSelfSet, *rNums;
int *tokens, *rVals, tokenNum;
int **lists, *count;


int transferInput(char *str)
{
	int i=STR_LENGTH-1;
	int num=0, bit;
	for(;i>=0; i--)
	{
		bit=(int)(str[i]-'0');
		num=num<<1;
		num=num|bit;
	}
	return num;
}

void sortSelfSet()
{
	int i, j, tmp;
	for(i=0; i<S_SIZE-1; i++)
		for(j=i+1; j<S_SIZE; j++)
		{
			if(selfSet[i]>selfSet[j])
			{
				tmp=selfSet[i];
				selfSet[i]=selfSet[j];
				selfSet[j]=tmp;
			}
		}
}

int inSortedSet(int *array, int size, int value)
{
	int low=0, high=size-1;
	int mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(array[mid]>value)
			high=mid-1;
		else if(array[mid]<value)
			low=mid+1;
		else
			return 1;
	}
	return 0;
}

void loadSets(char *sfilename, char *nfilename)
{
	FILE *fin1, *fin2;
	int i;
	char temp[STR_LENGTH+1];
	nSelfSet=(int *)malloc(sizeof(int)*NS_SIZE);
	rNums=(int *)malloc(sizeof(int)*NS_SIZE);
	fin1=fopen(sfilename, "r");
	for(i=0; i<S_SIZE; i++)
	{
		fscanf(fin1, "%s", temp);
		selfSet[i]=transferInput(temp);
	}
	sortSelfSet();
	fin2=fopen(nfilename, "r");
	for(i=0; i<NS_SIZE; i++)
		fscanf(fin2, "%d%d",&rNums[i], &nSelfSet[i]);
}

void tagOn(int r, int detector)
{
	int ord=r-R1;
	int *list=lists[ord];
	int key=(1<<r)-1;
	int index;
	int i;
	for(i=0; i<STR_LENGTH-r; i++)
	{
		index=(detector>>i)&key;
		if(r==8 && index==127)
			printf("%d\n", detector);
		if(list[index]==0)
		{
			count[ord]++;
			list[index]=1;
		}
	}
}

void tagToken()
{
	int i, j, len, r, detector;
	lists=(int **)malloc(sizeof(int *)*C);
	count=(int *)malloc(sizeof(int)*C);
	for(i=0; i<C; i++)
	{
		r=R1+i;
		len=1<<r;
		lists[i]=(int *)malloc(sizeof(int)*len);
		for(j=0; j<len; j++)
			lists[i][j]=0;
		count[i]=0;
	}
	for(i=0; i<NS_SIZE; i++)
	{
		r=rNums[i];
		detector=nSelfSet[i];
		tagOn(r, detector);
	}
}

void generateTokens()
{
	int i, j, r, len, ind=0;
	tokenNum=0;
	for(i=0; i<C; i++)
		tokenNum+=count[i];
	tokens=(int *)malloc(sizeof(int)*tokenNum);
	rVals=(int *)malloc(sizeof(int)*tokenNum);
	for(i=0; i<C; i++)
	{
		r=R1+i;
		len=1<<r;
		for(j=0; j<len; j++)
		{
			if(lists[i][j]==1)
			{
				tokens[ind]=j;
				rVals[ind]=r;
				ind++;
			}
		}
	}
}

int matchint(int num1, int num2, int r)
{
	int tester=(1<<r)-1;
	int key1, key2;
	int i, j;
	for(i=0; i<STR_LENGTH-r; i++)
	{
		key1=num1>>i;
		key1=key1&tester;
		for(j=0; j<STR_LENGTH-r; j++)
		{
			key2=num2>>j;
			key2=key2&tester;
			if(key1==key2)
			{
				return 1;
			}			
		}
	}
	return 0;
}

int checkBH(int num)
{
	int i;
	for(i=0; i<tokenNum; i++)
	{
		if(matchint(num, tokens[i], rVals[i]))
			return 0;
	}
	return 1;
}

void generateBH(char *filename)
{
	FILE *fout;
	int i, count=0;
	fout=fopen(filename, "w");
	for(i=0; i<TOTAL_NUM; i++)
	{
		if(i%10000==0)
			printf("%d of %d\n", i, TOTAL_NUM);
		if(inSortedSet(selfSet, S_SIZE, i) || inSortedSet(nSelfSet, NS_SIZE, i))
			continue;
		if(checkBH(i))
		{
			fprintf(fout, "%d\n", i);
			count=count+1;
			if(count%1024==0)
				fflush(fout);
		}
	}
	printf("Total num is %d\n", count);
}

int main()
{
	int i, j, len, r;
	FILE *fout;
	loadSets("sample.out", "output_0_4194304.dat");
	tagToken();
	generateTokens();
	generateBH("bhList.dat");
	return 0;
}
