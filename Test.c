// Test.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sorts.h"
#include "Score.h"
#include "MyRand.h"

void I_Test()
{
	int *data0=NULL, *data=NULL;								// ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = {"��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�"};	// C-�ַ������飨���ݷֲ���ʽ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};		// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(int*, int) = {I_Bubble, I_Select, I_Qsort};		// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, j, n, m = sizeof(f)/sizeof(*f);						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	int flag[20];												// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];												// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��

	for(j=2; j>=-1; j--)										// ���ݷֲ���ʽ
	{
		printf("\n��������(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			I_GetMemory(&data, &data0, n);						// �������ѿռ�
			I_InitData(data0, n, j);							// ����ԭʼ����
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					break;
				I_ReSet(data, data0, n);						// �ָ�ԭʼ����
				gettime(1);										// ���ü�ʱ���
				f[i](data, n);									// �� i �������㷨
				t[i] = gettime(0);								// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i] = I_Check(data, n);						// �����������ȷ��
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t�����������ڵݹ���̫����ܵ���ջ�������������");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"��ȷ":"����"));
			}
			printf("\n");
			I_FreeMemory(&data, &data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

void D_Test()
{
	double *data0=NULL, *data=NULL;								// ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = {"��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�"};	// C-�ַ������飨���ݷֲ���ʽ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};		// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(double*, int) = {D_Bubble, D_Select, D_Qsort};	// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, j, n, m = sizeof(f)/sizeof(*f);						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	int flag[20];												// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];												// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��
	
	for(j=2; j>=-1; j--)										// ���ݷֲ�����
	{
		printf("\n˫���ȸ���������(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			D_GetMemory(&data, &data0, n);						// �������ѿռ�
			D_InitData(data0, n, j);							// ����ԭʼ����
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					break;
				D_ReSet(data, data0, n);							// �ָ�ԭʼ����
				gettime(1);										// ���ü�ʱ���
				f[i](data, n);									// �� i �������㷨
				t[i] = gettime(0);								// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i] = D_Check(data, n);						// �����������ȷ��
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t�����������ڵݹ���̫����ܵ���ջ�������������");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"��ȷ":"����"));
			}
			printf("\n");
			D_FreeMemory(&data, &data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

void Score_Test()
{
	Score *data0=NULL, *data=NULL;							// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};	// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(Score*, int) = {Bubble, Select, Qsort};		// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, n, m = sizeof(f)/sizeof(*f);
	int flag;
	double t;
	
	printf("\n�ṹ��(Score)�������� (��̬�ֲ�)\n");
	for(n=1024; n<=65536; n*=2)
	{
		GetMemory(&data, &data0, n);						// �������ѿռ�
		InitScore(data0, n);								// ����ԭʼ����
		for(i=0; i<m; i++)
		{
			ReSet(data, data0, n);							// �ָ�ԭʼ����
			gettime(1);										// ���ü�ʱ���
			f[i](data, n);									// �� i �������㷨
			t = gettime(0);									// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
			flag = Check(data, n);							// �����������ȷ��
			printf("%d\t%lf\t%s: %s\n", n, t, algo[i], (flag?"��ȷ":"����"));
			ShowScore(data, n, 10);							// ����������10����ڰ��������У���߷ֵ�һ�������
		}
		FreeMemory(&data, &data0);							// �ͷŶѿռ���Դ����ʹָ��Ϊ��
	}
}

int main()					// ������
{
//	void TestStrCmp();	TestStrCmp();	return 0;

	srand(time(NULL));		// ���������������������
	
	I_Test();				// ����int��������
	D_Test();				// ����double��������
	Score_Test();			// ����Score��������

                        	// ��ʽ����ĺ���ʱ�����齫�����3�����ע���������Խ�ʡʱ��
	void TestString();		// ����ԭ�ͣ����ں�������
	TestString();			// ��������

	return 0;
}
