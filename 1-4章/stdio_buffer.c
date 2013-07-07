/*
 *说明：函数从标准输入中读取字符，返回到标准输出
 *用法：编译后的程序名  输入的字符（单个）  
 *返回值：  返回输入的字符（单个）
 *注意事项：需要包含头文件#include<unistd.h>使用read返回读取到的字节数，正常结束返回0，文件出错返回-1
 * */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//read 函数读指定的字节数，不便于扩展，使用标准IO不需要担心选择最佳的缓冲区
#define  BUFFSIZE 1024
int main()
{
	int n;
	char buf[BUFFSIZE];
	//read 函数返回读得的字节数，到达文件结束时返回0，文件出错时返回-1
	while(n=read(STDIN_FILENO,buf,BUFFSIZE)>0)
	{
		if(write(STDOUT_FILENO,buf,n)!=n)
		{
			printf("%s\n","Write error!");
		}
	}
	if(n<0)
	{
		printf("%s\n","Read error!");
	}
}
