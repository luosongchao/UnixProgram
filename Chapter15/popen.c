#include<stdlib.h>
#include<stdio.h>

#define MAXLINE 1024

int main()
{
	char line[MAXLINE];
	FILE *filein;

	/**
	 * 调用自定义可执行文件toUpper，
	 * 读取toUpper命令的输出
	 */ 
	if((filein=popen("toUpper","r"))==NULL)
	{
		printf("popen error!\n");
		exit(0);
	}

	for(;;)
	{
		/**
		 * fflush(int）立即刷新流
		 */
		fputs("prompt>",stdout);
		fflush(stdout);

		/**
		 * 读取toUpper命令输出到pipe中的值
		 */ 
		if(fgets(line,MAXLINE,filein)==NULL)
		{
			break;
		}

		if(fputs(line,stdout)==EOF)
		{
			printf("fputs error!\n");
			exit(0);
		}
	}

	/**
	 * 等待命令执行完毕并关闭管道及文件指针
	 */ 
	if(pclose(filein)==-1)
	{
		printf("pclose error!\n");
		exit(0);
	}
	putchar('\n');
	exit(0);
}
