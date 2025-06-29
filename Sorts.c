// Sorts.c		三种（冒泡、选择、快速）基本排序算法（升序）
#include <stdlib.h>
#include <time.h>
#include "MyRand.h"

double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t=0;						// 静态局部变量，存储计时起点
	if(restart||t==0) t = clock();			// 根据实参决定是否重新确定计时起点
	return c*(clock()-t);					// 从上一计时点到现在所经历的时间
}

void I_GetMemory(int **data, int **data0, int n)		// 分配堆内存空间，通过参数"返回"首地址
{													// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(*data0!=NULL) free(*data0);					// 先释放原先所"拥有"的堆空间资源
	if(*data !=NULL) free(*data);
	*data0 = (int*)calloc(n, sizeof(int));			// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (int*)calloc(n, sizeof(int));
}

void D_GetMemory(double **data, double **data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{													// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(*data0!=NULL) free(*data0);					// 先释放原先所"拥有"的堆空间资源
	if(*data !=NULL) free(*data);
	*data0 = (double*)calloc(n, sizeof(double));	// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (double*)calloc(n, sizeof(double));
}

void I_FreeMemory(int **data, int **data0)			// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// 这一条赋值语句非常重要！保持"隐含约定"
}

void D_FreeMemory(double **data, double **data0)	// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// 这一条赋值语句非常重要！保持"隐含约定"
}

void I_InitData(int *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;					break;	// 逆序（从大到小）
	case 0:	 for(i=0; i<n; i++) data[i] = i;						break;	// 顺序（从小到大）
	case 1:  for(i=0; i<n; i++) data[i] = (int)(0.5+UniformRand(54,90));break;	// [54,90]上的均匀分布
	default: for(i=0; i<n; i++) data[i] = (int)(0.5+GaussRand(72, 6*6));break;	// 正态分布，均值72，方差36（根方差6）
	}
}

void D_InitData(double *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;			break;	// 逆序（从大到小）
	case 0:	 for(i=0; i<n; i++) data[i] = i;				break;	// 顺序（从小到大）
	case 1:  for(i=0; i<n; i++) data[i] = UniformRand(54,90);break;	// [54,90]上的均匀分布
	default: for(i=0; i<n; i++) data[i] = GaussRand(72, 6*6);break;	// 正态分布，均值72，方差36（根方差6）
	}
}

void I_ReSet(int *data, const int *data0, int n)		// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

void D_ReSet(double *data, const double *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int I_Check(const int *a, int size)					// 检验数组元素是否已按升序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

int D_Check(const double *a, int size)				// 检验数组元素是否已按升序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

// 三种基本的（没有优化的）排序算法 - 包含统计功能
void I_Bubble(int *a, int size, unsigned long int *comparisons, unsigned long int *assignments)		// 冒泡排序
{
	int temp;								// 定义一个局部变量，数据类型与形式数据类型相同
	int i, j;
	*comparisons = *assignments = 0;		// 初始化统计计数器
	for(i=1; i<size; i++)					// 共进行 size-1 轮比较和交换
	{
		for(j=0; j<size-i; j++)
		{
			(*comparisons)++;				// 统计比较次数
			if(a[j] > a[j+1])				// 相邻元素之间比较，必要时
			{
				temp = a[j];				// 交换 a[j] 与 a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
				*assignments += 2;			// 两个数组元素交换
			}
		}
	}
}

void D_Bubble(double *a, int size, unsigned long int *comparisons, unsigned long int *assignments)	// 冒泡排序
{
	double temp;							// 定义一个局部变量，数据类型与形式数据类型相同
	int i, j;
	*comparisons = *assignments = 0;
	for(i=1; i<size; i++)					// 共进行 size-1 轮比较和交换
	{
		for(j=0; j<size-i; j++)
		{
			(*comparisons)++;
			if(a[j] > a[j+1])				// 相邻元素之间比较，必要时
			{
				temp = a[j];				// 交换 a[j] 与 a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
				*assignments += 2;			// 两个数组元素交换
			}
		}
	}
}

void I_Select(int *a, int size, unsigned long int *comparisons, unsigned long int *assignments)		// 选择排序
{
	int temp;
	int i, j, k=0;
	*comparisons = *assignments = 0;
	for(i=1; i<size; i++)					// 循环size-1次
	{
		k = i-1;
		for(j=i; j<size; j++)
		{
			(*comparisons)++;
			if(a[j] < a[k])
				k = j;						// 找出当前范围内"最小"元素的下标
		}
		if(k!=i-1)							// 若"最小"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
			*assignments += 2;				// 两个数组元素交换
		}
	}
}

void D_Select(double *a, int size, unsigned long int *comparisons, unsigned long int *assignments)	// 选择排序
{
	double temp;
	int i, j, k=0;
	*comparisons = *assignments = 0;
	for(i=1; i<size; i++)					// 循环size-1次
	{
		k = i-1;
		for(j=i; j<size; j++)
		{
			(*comparisons)++;
			if(a[j] < a[k])
				k = j;						// 找出当前范围内"最小"元素的下标
		}
		if(k!=i-1)							// 若"最小"元素不是a[i-1]，则交换之
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
			*assignments += 2;				// 两个数组元素交换
		}
	}
}

// 三数取中法选择基准
static int I_MedianOfThree(int *a, int *b, int *c, unsigned long int *comparisons) {
	(*comparisons) += 2;
	if ((*a <= *b && *b <= *c) || (*c <= *b && *b <= *a)) return *b;
	if ((*b <= *a && *a <= *c) || (*c <= *a && *a <= *b)) return *a;
	return *c;
}

void I_Qsort(int *a, int size, unsigned long int *comparisons, unsigned long int *assignments)		// 快速排序
{
	int pivot, temp;
	int *left_ptr, *right_ptr;				// 使用指针而非索引
	static int first_call = 1;
	static int depth = 0;

	if(size<=1) return;

	if(first_call) {
		*comparisons = *assignments = 0;
		first_call = 0;
	}

	depth++;
	
	// 对于较大数组使用三数取中法选择基准
	if(size >= 10) {
		pivot = I_MedianOfThree(a, a + size/2, a + size - 1, comparisons);
		// 将基准移到末尾
		if(pivot == a[size/2]) {
			temp = a[size/2]; a[size/2] = a[size-1]; a[size-1] = temp;
			*assignments += 2;
		} else if(pivot == a[0]) {
			temp = a[0]; a[0] = a[size-1]; a[size-1] = temp;
			*assignments += 2;
		}
		pivot = a[size-1];
	} else {
		pivot = a[size-1];					// 小数组直接选择最后一个值为分界值
	}
	(*assignments)++;
	
	left_ptr = a;
	right_ptr = a + size - 1;
	
	do
	{
		while(left_ptr < right_ptr && ((*comparisons)++, *left_ptr <= pivot)) left_ptr++;
		while(left_ptr < right_ptr && ((*comparisons)++, *right_ptr >= pivot)) right_ptr--;
		if(left_ptr < right_ptr)
		{
			temp = *left_ptr; *left_ptr = *right_ptr; *right_ptr = temp;
			*assignments += 2;
		}
	}while(left_ptr < right_ptr);
	
	a[size-1] = *left_ptr; *left_ptr = pivot;	// 找到分界点
	*assignments += 2;
	
	int left_size = left_ptr - a;
	I_Qsort(a, left_size, comparisons, assignments);					// 递归调用(左侧部分)
	I_Qsort(left_ptr + 1, size - left_size - 1, comparisons, assignments);	// 递归调用(右侧部分)
	
	depth--;
	if(depth == 0) first_call = 1;
}

// 三数取中法选择基准（double版本）
static double D_MedianOfThree(double *a, double *b, double *c, unsigned long int *comparisons) {
	(*comparisons) += 2;
	if ((*a <= *b && *b <= *c) || (*c <= *b && *b <= *a)) return *b;
	if ((*b <= *a && *a <= *c) || (*c <= *a && *a <= *b)) return *a;
	return *c;
}

void D_Qsort(double *a, int size, unsigned long int *comparisons, unsigned long int *assignments)	// 快速排序
{
	double pivot, temp;
	double *left_ptr, *right_ptr;			// 使用指针而非索引
	static int first_call = 1;
	static int depth = 0;

	if(size<=1) return;

	if(first_call) {
		*comparisons = *assignments = 0;
		first_call = 0;
	}

	depth++;
	
	// 对于较大数组使用三数取中法选择基准
	if(size >= 10) {
		pivot = D_MedianOfThree(a, a + size/2, a + size - 1, comparisons);
		// 将基准移到末尾
		if(pivot == a[size/2]) {
			temp = a[size/2]; a[size/2] = a[size-1]; a[size-1] = temp;
			*assignments += 2;
		} else if(pivot == a[0]) {
			temp = a[0]; a[0] = a[size-1]; a[size-1] = temp;
			*assignments += 2;
		}
		pivot = a[size-1];
	} else {
		pivot = a[size-1];					// 小数组直接选择最后一个值为分界值
	}
	(*assignments)++;
	
	left_ptr = a;
	right_ptr = a + size - 1;
	
	do
	{
		while(left_ptr < right_ptr && ((*comparisons)++, *left_ptr <= pivot)) left_ptr++;
		while(left_ptr < right_ptr && ((*comparisons)++, *right_ptr >= pivot)) right_ptr--;
		if(left_ptr < right_ptr)
		{
			temp = *left_ptr; *left_ptr = *right_ptr; *right_ptr = temp;
			*assignments += 2;
		}
	}while(left_ptr < right_ptr);
	
	a[size-1] = *left_ptr; *left_ptr = pivot;	// 找到分界点
	*assignments += 2;
	
	int left_size = left_ptr - a;
	D_Qsort(a, left_size, comparisons, assignments);					// 递归调用(左侧部分)
	D_Qsort(left_ptr + 1, size - left_size - 1, comparisons, assignments);	// 递归调用(右侧部分)
	
	depth--;
	if(depth == 0) first_call = 1;
}