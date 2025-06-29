// Test.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"

void I_Test()
{
	int *data0=NULL, *data=NULL;
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};
	void (*f[])(int*, int, unsigned long int*, unsigned long int*) = {I_Bubble, I_Select, I_Qsort};
	int i, j, n, m = sizeof(f)/sizeof(*f);
	int flag[20];
	double t[20];
	unsigned long int comparisons[20], assignments[20];

	printf("整型数据排序算法性能测试\n");
	printf("数据规模\t数据分布\t冒泡时间\t冒泡比较\t冒泡赋值\t选择时间\t选择比较\t选择赋值\t快速时间\t快速比较\t快速赋值\t冒泡正确\t选择正确\t快速正确\n");

	for(j=2; j>=-1; j--)
	{
		for(n=1024; n<=65536; n*=2)
		{
			I_GetMemory(&data, &data0, n);
			I_InitData(data0, n, j);
			printf("%d\t%s\t", n, InitConf[j+1]);
			
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)
				{
					printf("跳过\t跳过\t跳过\t");
					continue;
				}
				I_ReSet(data, data0, n);
				gettime(1);
				f[i](data, n, &comparisons[i], &assignments[i]);
				t[i] = gettime(0);
				flag[i] = I_Check(data, n);
				printf("%.6f\t%lu\t%lu\t", t[i], comparisons[i], assignments[i]);
			}
			
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)
					printf("跳过\t");
				else
					printf("%s\t", (flag[i]?"正确":"错误"));
			}
			printf("\n");
			
			I_FreeMemory(&data, &data0);
		}
	}
}

void D_Test()
{
	double *data0=NULL, *data=NULL;
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};
	void (*f[])(double*, int, unsigned long int*, unsigned long int*) = {D_Bubble, D_Select, D_Qsort};
	int i, j, n, m = sizeof(f)/sizeof(*f);
	int flag[20];
	double t[20];
	unsigned long int comparisons[20], assignments[20];
	
	printf("\n双精度浮点型数据排序算法性能测试\n");
	printf("数据规模\t数据分布\t冒泡时间\t冒泡比较\t冒泡赋值\t选择时间\t选择比较\t选择赋值\t快速时间\t快速比较\t快速赋值\t冒泡正确\t选择正确\t快速正确\n");
	
	for(j=2; j>=-1; j--)
	{
		for(n=1024; n<=65536; n*=2)
		{
			D_GetMemory(&data, &data0, n);
			D_InitData(data0, n, j);
			printf("%d\t%s\t", n, InitConf[j+1]);
			
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)
				{
					printf("跳过\t跳过\t跳过\t");
					continue;
				}
				D_ReSet(data, data0, n);
				gettime(1);
				f[i](data, n, &comparisons[i], &assignments[i]);
				t[i] = gettime(0);
				flag[i] = D_Check(data, n);
				printf("%.6f\t%lu\t%lu\t", t[i], comparisons[i], assignments[i]);
			}
			
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)
					printf("跳过\t");
				else
					printf("%s\t", (flag[i]?"正确":"错误"));
			}
			printf("\n");
			
			D_FreeMemory(&data, &data0);
		}
	}
}

void Score_Test()
{
	Score *data0=NULL, *data=NULL;
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};
	void (*f[])(Score*, int, unsigned long int*, unsigned long int*) = {Bubble, Select, Qsort};
	int i, n, m = sizeof(f)/sizeof(*f);
	int flag[20];
	unsigned long int comparisons[20], assignments[20];
	double t[20];
	
	printf("\n结构体Score类型数据排序算法性能测试\n");
	printf("数据规模\t冒泡时间\t冒泡比较\t冒泡赋值\t选择时间\t选择比较\t选择赋值\t快速时间\t快速比较\t快速赋值\t冒泡正确\t选择正确\t快速正确\n");
	
	for(n=1024; n<=65536; n*=2)
	{
		GetMemory(&data, &data0, n);
		InitScore(data0, n);
		printf("%d\t", n);
		
		for(i=0; i<m; i++)
		{
			ReSet(data, data0, n);
			gettime(1);
			f[i](data, n, &comparisons[i], &assignments[i]);
			t[i] = gettime(0);
			flag[i] = Check(data, n);
			printf("%.6f\t%lu\t%lu\t", t[i], comparisons[i], assignments[i]);
		}
		
		for(i=0; i<m; i++)
			printf("%s\t", (flag[i]?"正确":"错误"));
		printf("\n");
		
		FreeMemory(&data, &data0);
	}
}

void PrintAnalysis()
{
	printf("\n算法性能分析总结\n");
	printf("算法\t最好时间复杂度\t平均时间复杂度\t最坏时间复杂度\t空间复杂度\t稳定性\n");
	printf("冒泡排序\tO(n)\tO(n²)\tO(n²)\tO(1)\t稳定\n");
	printf("选择排序\tO(n²)\tO(n²)\tO(n²)\tO(1)\t不稳定\n");
	printf("快速排序\tO(nlogn)\tO(nlogn)\tO(n²)\tO(logn)\t不稳定\n");
}

int main()
{
	srand(time(NULL));
	
	I_Test();
	D_Test();
	Score_Test();
	PrintAnalysis();

	return 0;
}