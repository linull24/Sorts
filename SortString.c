// SortString.c
/* 思考题
1.	下面的测试函数中，
	(1) 请先思考然后进行程序验证sizeof(strA), sizeof(strB), sizeof(strC), sizeof(strD)各为多少字节，这些字节位于内存什么区域（代码区、全局数据区、栈区、堆区）？
	(2) strA、strB、strC、strD联系的C-字符串数组的内容存储在内存的什么区域？它们的读/写属性（是否可读、可写）如何？
2.	设计BubbleA，BubbleB两个函数之前，思考
	(1) 如何比较两个字符串的内容？
	(2) 存储在什么区域的字符串能交换其内容？
	(3) 若不能交换字符串的内容，排序操作中交换什么？
3.	GetStringsA和GetStringB函数的第一个形式参数为什么需要用到三级指针，如果仅用二级指针会怎样？
	GetStringsA1函数应该如何使用？
4.	FreeStrings函数的形式参数为什么需要用到三级指针？（或回答如下问题）
	如果仅用二级指针（见FreeStrings1函数），能否释放所申请的堆内存资源？FreeStrings函数与FreeStrings1函数的关键不同点是什么？
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 20

// 函数声明
int StrCmp(const char *str1, const char *str2);

void BubbleA(char (*str)[NUM], int size)			// 数组指针
{
	int i, j;
	char temp[NUM];
	
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1 - i; j++)
		{
			if (StrCmp(str[j], str[j + 1]) > 0)
			{
				// 交换字符串
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
		}
	}
}

void BubbleB(char *str[], int size)					// 指针数组
{
	int i, j;
	char *temp;
	
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1 - i; j++)
		{
			if (StrCmp(str[j], str[j + 1]) > 0)
			{
				// 交换指针
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}
}

int StrCmp(const char *str1, const char *str2)
{
	unsigned char *p1 = (unsigned char*)str1;			// 思考题：为什么需要进行强制转换成unsigned char*
	unsigned char *p2 = (unsigned char*)str2;
	while(*p1 && *p2 && *p1++==*p2++)					// 思考题：有哪些情况使本循环结束
		;
	return *p1 > *p2 ? 1 : (*p1<*p2 ? -1 : 0); 
}

void TestStrCmp()
{
	char *str[] = {"abc", "abcd", "上海大学", "", "上海"};
	int n = sizeof(str)/sizeof(*str), i, j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			printf("strcmp(\"%s\", \"%s\") = %d\nStrCmp(\"%s\", \"%s\") = %d\n\n",
					str[i], str[j], strcmp(str[i], str[j]), str[i], str[j], StrCmp(str[i], str[j]));
}

//void ShowStringsA(const char *prompt, char (* const strs)[NUM], int n)
void ShowStringsA(const char *prompt, char (*strs)[NUM], int n)
{
	int i;
	if(n>0)
		printf("%s %s", prompt, strs[0]);
	for(i=1; i<n; i++)
		printf(", %s", strs[i]);
	printf("\n");
}

void ShowStringsB(const char *prompt, char *strs[], int n)
{
	int i;
	if(n>0)
		printf("%s %s", prompt, strs[0]);
	for(i=1; i<n; i++)
		printf(", %s", strs[i]);
	printf("\n");
}

void GetStringsA(char ***dest, char (*source)[NUM], int n)
{
	*dest = (char**)calloc(sizeof(char*), n); 
	if(*dest == NULL) return;
	int i, len;
	for(i=0; i<n; i++)
	{
		len = strlen(source[i]);
		(*dest)[i] = (char*)calloc(sizeof(char), len+1);
		strcpy((*dest)[i], source[i]);
	}
}

char **GetStringsA1(char (*source)[NUM], int n)		// 思考题：本函数与上面的GetStringSA函数的功能是否相同？调用本函数时，应该用何种表达式？
{
	char **dest;
	dest = (char**)calloc(sizeof(char*), n); 
	if(dest == NULL) return dest;
	int i, len;
	for(i=0; i<n; i++)
	{
		len = strlen(source[i]);
		dest[i] = (char*)calloc(sizeof(char), len+1);
		strcpy(dest[i], source[i]);
	}
	return dest;
}

void GetStringsB(char ***dest, char *source[], int n)
{
	*dest = (char**)calloc(sizeof(char*), n); 
	if(*dest == NULL) return;
	int i, len;
	for(i=0; i<n; i++)
	{
		len = strlen(source[i]);
		(*dest)[i] = (char*)calloc(sizeof(char), len+1);
		strcpy((*dest)[i], source[i]);
	}
}

void FreeStrings(char ***strs, int n)
{
	int i;
	if(*strs!=NULL)
	{
		for(i=0; i<n; i++)
			if((*strs)[i]!=NULL)
				free((*strs)[i]);
		free(*strs);
		*strs = NULL;
	}
}

void FreeStrings1(char **strs, int n)		// 思考题：本函数能否完成释放堆内存资源的任务？有何缺陷？
{
	int i;
	if(strs!=NULL)
	{
		for(i=0; i<n; i++)
			if(strs[i]!=NULL)
				free(strs[i]);
		free(strs);
	}
}

void TestString()
{
	char strA[][NUM]= {"enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "a", "cake", "side"};
	char *strB[]    = {"enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "an", "cake", "side"};
	char **strC=NULL, **strD=NULL;
	int n1 = sizeof(strA)/sizeof(*strA), n2 = sizeof(strB)/sizeof(*strB);
	GetStringsA(&strC, strA, n1);			// 如果换成 GetStringsA1 函数，则调用语句应该是怎样的？
	GetStringsB(&strD, strB, n2);			// 请画出strC或strD的结构图

	printf("\n\t*** 多种不同存储方式的C-字符串数组的排序 ***\n");
	ShowStringsA("\n原始数据: ", strA, n1);
	BubbleA(strA, n1);
	ShowStringsA("\n排序结果: ", strA, n1);
	
	ShowStringsB("\n原始数据: ", strB, n2);
	BubbleB(strB, n2);
	ShowStringsB("\n排序结果: ", strB, n2);
	
	ShowStringsB("\n原始数据: ", strC, n1);
	BubbleB(strC, n1);						// 此处能否调用BubbleA函数对strC进行排序？如果要用BubbleA函数，需要对GetStringsA函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strC, n1);

	ShowStringsB("\n原始数据: ", strD, n2);
	BubbleB(strD, n2);						// 此处能否调用BubbleA函数对strD进行排序？如果要用BubbleA函数，需要对GetStringsB函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strD, n2);

	FreeStrings(&strC, n1);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？
	FreeStrings(&strD, n2);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？
}