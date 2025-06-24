// Sorts.c		���֣�ð�ݡ�ѡ�񡢿��٣����������㷨������
#include <stdlib.h>
#include <time.h>
#include "MyRand.h"

double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t=0;						// ��̬�ֲ��������洢��ʱ���
	if(restart||t==0) t = clock();			// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c*(clock()-t);					// ����һ��ʱ�㵽������������ʱ��
}

void I_GetMemory(int **data, int **data0, int n)		// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{														// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(*data0!=NULL) free(*data0);						// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(*data !=NULL) free(*data);
	*data0 = (int*)calloc(n, sizeof(int));				// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (int*)calloc(n, sizeof(int));
}

void D_GetMemory(double **data, double **data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{														// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(data0!=NULL) free(*data0);						// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(data !=NULL) free(*data);
	*data0 = (double*)calloc(n, sizeof(double));		// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (double*)calloc(n, sizeof(double));
}

void I_FreeMemory(int **data, int **data0)				// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void D_FreeMemory(double **data, double **data0)		// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void I_InitData(int *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;						break;	// ���򣨴Ӵ�С��
	case 0:	 for(i=0; i<n; i++) data[i] = i;							break;	// ˳�򣨴�С����
	case 1:  for(i=0; i<n; i++) data[i] = (int)(0.5+UniformRand(54,90));break;	// [54,90]�ϵľ��ȷֲ�
	default: for(i=0; i<n; i++) data[i] = (int)(0.5+GaussRand(72, 6*6));break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

void D_InitData(double *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;			break;	// ���򣨴Ӵ�С��
	case 0:	 for(i=0; i<n; i++) data[i] = i;				break;	// ˳�򣨴�С����
	case 1:  for(i=0; i<n; i++) data[i] = UniformRand(54,90);break;	// [54,90]�ϵľ��ȷֲ�
	default: for(i=0; i<n; i++) data[i] = GaussRand(72, 6*6);break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

void I_ReSet(int *data, const int *data0, int n)		// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

void D_ReSet(double *data, const double *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int I_Check(const int *a, int size)						// ��������Ԫ���Ƿ��Ѱ���������
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

int D_Check(const double *a, int size)					// ��������Ԫ���Ƿ��Ѱ���������
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

// ���ֻ����ģ�û���Ż��ģ������㷨
void I_Bubble(int *a, int size)						// ð������
{
	int temp;										// ����һ���ֲ�������������������ʽ����������ͬ
	int i, j;
	for(i=1; i<size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		for(j=0; j<size-i; j++)
		{
			if(a[j] > a[j+1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			{
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void D_Bubble(double *a, int size)					// ð������
{
	double temp;									// ����һ���ֲ�������������������ʽ����������ͬ
	int i, j;
	for(i=1; i<size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		for(j=0; j<size-i; j++)
		{
			if(a[j] > a[j+1])						// ����Ԫ��֮��Ƚϣ���Ҫʱ
			{
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void I_Select(int *a, int size)						// ѡ������
{
	int temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// ѭ��size-1��
	{
		for(j=i; j<size; j++)
			if(a[j] < a[k])
				k = j;								// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
		if(k!=i-1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
		}
		k = i;
	}
}

void D_Select(double *a, int size)					// ѡ������
{
	double temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// ѭ��size-1��
	{
		for(j=i; j<size; j++)
			if(a[j] < a[k])
				k = j;								// �ҳ���ǰ��Χ��"��С"Ԫ�ص��±�
		if(k!=i-1)									// ��"��С"Ԫ�ز���a[i-1]���򽻻�֮
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
		}
		k = i;
	}
}

void I_Qsort(int *a, int size)						// ��������
{
	int pivot, temp;
	int left=0, right=size-1;						// �±꣨������

	if(size<=1) return;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while(left<right && a[left]<=pivot) left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while(left<right && a[right]>=pivot)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	I_Qsort(a, left);								// �ݹ����(��ಿ��)
	I_Qsort(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
}

void D_Qsort(double *a, int size)					// ��������
{
	double pivot, temp;
	int left=0, right=size-1;						// �±꣨������

	if(size<=1) return;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while(left<right && a[left]<=pivot) left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while(left<right && a[right]>=pivot)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	D_Qsort(a, left);								// �ݹ����(��ಿ��)
	D_Qsort(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
}
