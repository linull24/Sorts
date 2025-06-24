// Score.c
#include <stdio.h>
#include <stdlib.h>
#include "Score.h"
#include "Sorts.h"
#include "MyRand.h"

void GetMemory(Score **data, Score **data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{													// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(*data0!=NULL) free(*data0);					// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(*data !=NULL) free(*data);
	*data0 = (Score*)calloc(n, sizeof(Score));		// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (Score*)calloc(n, sizeof(Score));
}

void FreeMemory(Score **data, Score **data0)		// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void InitScore(struct Score *data, int n)
{
	double mean=72, variance=6*6;
	int i;
	for(i=0; i<n; i++)
	{
		sprintf(data[i].Id, "%08d", i+1);			// ����ѧ sprintf ��������ע�⣺ԭʼ�����У�ѧ������ȫ˳�����еģ�
		data[i].Total  = data[i].Chinese   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Math      = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].English   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Physics   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = (int)(0.5+GaussRand(mean, variance));
	}
}

void ReSet(Score *data, const Score *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int Check(const Score *a, int size)					// δ������ȫ����ȷ�Լ��飬����������Ԫ���Ƿ��Ѱ���������
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
		m = size;							// ��������
	printf("\t����������ݣ����ܷ�ǰ�����������ݣ�\n");
	printf("\tѧ��\t�ܷ�\t����\t��ѧ\t����\t����\t��ѧ\n");
	for(i=0; i<m; i++)
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", data[i].Id,
			data[i].Total, data[i].Chinese, data[i].Math, 
			data[i].English, data[i].Physics, data[i].Chemistry);
}

// ���ֻ����ģ�û���Ż��ģ������㷨
void Bubble(Score *a, int size)						// ð������(���ֽܷ�������)
{
	Score temp;										// ����һ���ֲ�������������������ʽ����������ͬ
	int i, j;
	for(i=1; i<size; i++)							// ������ size-1 �ֱȽϺͽ���
	{
		for(j=0; j<size-i; j++)
		{
			if(a[j].Total < a[j+1].Total)			// ����Ԫ��֮��Ƚ��ֵܷĴ�С����Ҫʱ
			{
				temp = a[j];						// ���� a[j] �� a[j+1]
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void Select(Score *a, int size)						// ѡ������
{
	Score temp;
	int i, j, k=0;
	for(i=1; i<size; i++)							// ѭ��size-1��
	{
		for(j=i; j<size; j++)
			if(a[j].Total > a[k].Total)
				k = j;								// �ҳ���ǰ��Χ��"���"Ԫ�ص��±�
		if(k!=i-1)									// ��"���"Ԫ�ز���a[i-1]���򽻻�֮
		{
			temp = a[k];
			a[k] = a[i-1];
			a[i-1] = temp;
		}
		k = i;
	}
}

void Qsort(Score *a, int size)						// ��������
{
	Score pivot, temp;
	int left=0, right=size-1;						// �±꣨������

	if(size<=1) return;

	pivot = a[right];								// ѡ�����һ��ֵΪ�ֽ�ֵ
	do
	{
		while(left<right && a[left].Total>=pivot.Total) left++;	// �˴� "<=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		while(left<right && a[right].Total<=pivot.Total)right--;// �˴� ">=" ������ֽ�ֵ��ȵ�Ԫ����ʱ����ԭ��
		if(left < right)
		{
			temp=a[left]; a[left]=a[right]; a[right]=temp;
		}
	}while(left < right);
	a[size-1] = a[left]; a[left] = pivot;			// �ҵ��ֽ�� left
	Qsort(a, left);									// �ݹ����(��ಿ��)
	Qsort(a+left+1, size-left-1);					// �ݹ����(�Ҳಿ��)
}
