// Score.c
#include <stdio.h>
#include <stdlib.h>
#include "Score.h"
#include "Sorts.h"
#include "MyRand.h"

void GetMemory(Score **data, Score **data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{													// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(*data0!=NULL) free(*data0);					// 先释放原先所"拥有"的堆空间资源
	if(*data !=NULL) free(*data);
	*data0 = (Score*)calloc(n, sizeof(Score));		// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (Score*)calloc(n, sizeof(Score));
}

void FreeMemory(Score **data, Score **data0)		// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// 这一条赋值语句非常重要！保持"隐含约定"
}

void InitScore(struct Score *data, int n)
{
	double mean=72, variance=6*6;
	int i;
	for(i=0; i<n; i++)
	{
		sprintf(data[i].Id, "%08d", i+1);			// 请自学 sprintf 函数。请注意：原始数据中，学号是完全顺序排列的！
		data[i].Total  = data[i].Chinese   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Math      = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].English   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Physics   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = (int)(0.5+GaussRand(mean, variance));
	}
}

void ReSet(Score *data, const Score *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int Check(const Score *a, int size)					// 未进行完全的正确性检验，仅检验数组元素是否已按降序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1].Total < a[i].Total)
			return 0;
	return 1;
}

void ShowScore(const Score *data, int size, int m)
{
	int i;
	if(m<=0 || m>=size)
		m = size;							// 所有数据
	printf("\t输出部分数据（即总分前若干名的数据）\n");
	printf("\t学号\t总分\t语文\t数学\t外语\t物理\t化学\n");
	for(i=0; i<m; i++)
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", data[i].Id,
			data[i].Total, data[i].Chinese, data[i].Math, 
			data[i].English, data[i].Physics, data[i].Chemistry);
}

// 三种基本的（没有优化的）排序算法
void Bubble(Score *a, int size)						// 冒泡排序(按总分降序排序)
{
	Score temp;										// 定义一个局部变量，数据类型与形式数据类型相同
	int i, j;
	for(i=1; i<size; i++)							// 共进行 size-1 轮比较和交换
	{
		for(j=0; j<size-i; j++)
		{
			if(a[j].Total < a[j+1].Total)			// 相邻元素之间比较总分的大小，必要时
			{
				temp = a[j];						// 交换 a[j] 与 a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void Select(Score *a, int size)						// 选择排序
{
	Score temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// 循环size-1次
	{
		for(j=i; j<size; j++)
			if(a[j].Total > a[k].Total)
				k = j;								// 找出当前范围内"最大"元素的下标
		if(k!=i-1)									// 若"最大"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
		}
		k = i;
	}
}

void Qsort(Score *a, int size)						// 快速排序
{
	Score pivot, temp;
	int left=0, right=size-1;						// 下标（整数）

	if(size<=1) return;

	pivot = a[right];								// 选择最后一个值为分界值
	do
	{
		while(left<right && a[left].Total>=pivot.Total) left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
		while(left<right && a[right].Total<=pivot.Total)right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// 找到分界点 left
	Qsort(a, left);									// 递归调用(左侧部分)
	Qsort(a+left+1, size-left-1);					// 递归调用(右侧部分)
}
