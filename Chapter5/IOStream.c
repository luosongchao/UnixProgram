#include<stdio.h>
#include<stdlib.h>

//函数声明 
FILE  *OpenFile(const char *filepath,const char *type);
char  *Read(FILE *file,const int length);
int   Write(FILE *file,char *data);
int   CloseFile(FILE *file);
int   Check(int argc,char *argv);
void  *GetSpace(const int length);
#define BUFLENGTH 1024

#define RW "r+"
#define RWA "a+"

int main(int argc,char *argv[])
{
	FILE *file;
	const char *type = RWA;

	if(Check(argc,argv[1]) != 0)
	{
		exit(0);
	}

	file=OpenFile(argv[1],type); 

	char *buf;
	const int length = BUFLENGTH;
	buf = GetSpace(length);
	buf = Read(file,length);
	printf("read string://%s\n",buf);

	char *data="hello world!\n";
	if(Write(file,data) == EOF)
	{
		printf("write error!\n");
	}	
	CloseFile(file);
}

//说明：打开文件
//输入：文件对应路径filepath
//输出：文件流FILE指针
//fopen(const char  *filepath,const char *type) 以指定方式打开文件
FILE *OpenFile(const char *filepath,const char *type)
{
	FILE *file;
	file=fopen(filepath,type);
	if(file == NULL)
	{
		printf("file open error!\n");
		exit(0);
	}
	return file;
}

//说明：参数检查
//输入：获取的是程序运行是main函数的参数
//输出：int 值为-1 表示异常，值为0表示正常
int Check(int argc,char *argv)
{
	if(argc!=2 || argv == "")
	{
		printf("usage:./a.out filepath\n");
		return -1;
	}
	return 0;
}

//说明：分配指定长度空间
//输入：分配空间长度
//输出：分配空间地址
void *GetSpace(const int length)
{
	void *space;
	space= malloc(length);
	if(space == NULL)
	{
		printf("malloc error!\n");
		exit(0);
	}
	return space;
}

//说明：读取文件中指定长度的数据
//输入：文件流、读取文件长度
//输出：读取字符地址
char *Read(FILE *file,const int length)
{
	char *buf;
	buf = (char *)GetSpace(length);

	char *result = fgets(buf,length,file);
	if(result == NULL)
	{
		printf("fgets error!\n");
		exit(0);
	}
	return buf;
}

int Write(FILE *file,char *data)
{
	int result=fputs(data,file);
	if(result == EOF)
	{
		printf("write error!");
	}
	
	return result;
}

//说明：关闭文件流
//输入：文件流
//输出：关闭返回值 -1表示关闭异常，0表示正常关闭
int CloseFile(FILE *file)
{
	int result = fclose(file);
	if(result == EOF)
	{
		printf("close file error!\n");
		exit(0);
	}
	return result;
}
