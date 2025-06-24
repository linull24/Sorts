// Test.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"

void I_Test()
{
	int *data0=NULL, *data=NULL;								// 指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组（数据分布方式）
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};		// C-字符串数组（排序算法名称）
	void (*f[])(int*, int) = {I_Bubble, I_Select, I_Qsort};		// 函数指针数组（元素为一系列函数的入口地址）
	int i, j, n, m = sizeof(f)/sizeof(*f);						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	int flag[20];												// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];												// 同上。记录不同算法的执行时间

	for(j=2; j>=-1; j--)										// 数据分布方式
	{
		printf("\n整型数据(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			I_GetMemory(&data, &data0, n);						// 申请分配堆空间
			I_InitData(data0, n, j);							// 设置原始数据
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					break;
				I_ReSet(data, data0, n);						// 恢复原始数据
				gettime(1);										// 设置计时起点
				f[i](data, n);									// 第 i 种排序算法
				t[i] = gettime(0);								// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = I_Check(data, n);						// 检验排序的正确性
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t快速排序：由于递归层次太深，可能导致栈溢出，故跳过。");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"正确":"错误"));
			}
			printf("\n");
			I_FreeMemory(&data, &data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

void D_Test()
{
	double *data0=NULL, *data=NULL;								// 指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组（数据分布方式）
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};		// C-字符串数组（排序算法名称）
	void (*f[])(double*, int) = {D_Bubble, D_Select, D_Qsort};	// 函数指针数组（元素为一系列函数的入口地址）
	int i, j, n, m = sizeof(f)/sizeof(*f);						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	int flag[20];												// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];												// 同上。记录不同算法的执行时间
	
	for(j=2; j>=-1; j--)										// 数据分布类型
	{
		printf("\n双精度浮点型数据(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			D_GetMemory(&data, &data0, n);						// 申请分配堆空间
			D_InitData(data0, n, j);							// 设置原始数据
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					break;
				D_ReSet(data, data0, n);							// 恢复原始数据
				gettime(1);										// 设置计时起点
				f[i](data, n);									// 第 i 种排序算法
				t[i] = gettime(0);								// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = D_Check(data, n);						// 检验排序的正确性
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t快速排序：由于递归层次太深，可能导致栈溢出，故跳过。");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"正确":"错误"));
			}
			printf("\n");
			D_FreeMemory(&data, &data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

void Score_Test()
{
	Score *data0=NULL, *data=NULL;							// 两个指针初始化为NULL非常重要！
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};	// C-字符串数组（排序算法名称）
	void (*f[])(Score*, int) = {Bubble, Select, Qsort};		// 函数指针数组（元素为一系列函数的入口地址）
	int i, n, m = sizeof(f)/sizeof(*f);
	int flag;
	double t;
	
	printf("\n结构体(Score)类型数据 (正态分布)\n");
	for(n=1024; n<=65536; n*=2)
	{
		GetMemory(&data, &data0, n);						// 申请分配堆空间
		InitScore(data0, n);								// 设置原始数据
		for(i=0; i<m; i++)
		{
			ReSet(data, data0, n);							// 恢复原始数据
			gettime(1);										// 设置计时起点
			f[i](data, n);									// 第 i 种排序算法
			t = gettime(0);									// 返回从计时起点到目前所经历的时间（秒）
			flag = Check(data, n);							// 检验排序的正确性
			printf("%d\t%lf\t%s: %s\n", n, t, algo[i], (flag?"正确":"错误"));
			ShowScore(data, n, 10);							// 倒序输出最后10项（由于按升序排列，最高分第一名在最后）
		}
		FreeMemory(&data, &data0);							// 释放堆空间资源，并使指针为空
	}
}

int main()					// 主函数
{
//	void TestStrCmp();	TestStrCmp();	return 0;

	srand(time(NULL));		// 设置随机数发生器的种子
	
	I_Test();				// 测试int类型数据
	D_Test();				// 测试double类型数据
	Score_Test();			// 测试Score类型数据

                        	// 调式下面的函数时，建议将上面的3行语句注释起来，以节省时间
	void TestString();		// 函数原型，用于函数声明
	TestString();			// 函数调用

	return 0;
}
