/*
 *说明：(1)文件描述符于标准输入/标准输出/标准出错相关联，分别由常量0/1/2定义
		相应的定义在#include<unistd.h>中定义为符号常量 STDIN_FILENO /
		STDOUT_FILENO / STDERR_FILENO 
 *		(2)OPEN_SIZE返回文件描述符的最大值（每个进程的最大打开文件数），使用sysconf（）函数获取，参数使用_SC_OPEN_MAX
		(3)PAGE_SIZE表示系统存储页长度 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>

int main()
{
	printf("Page_Size:%ld\n",sysconf(_SC_PAGE_SIZE));
	printf("OPEN_MAX:%ld\n",sysconf(_SC_OPEN_MAX));
	printf("STDIN_FILENO:%d\t STDOUT_FILENO:%d\t STDERR_FILENO:%d\n"
			,STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO);
	//定义在#include<limits.h>中包含了字符的最大值与最小值
	printf("CHAR_MIN:%d\tCHAR_MAX:%d\n",CHAR_MIN,CHAR_MAX); 
	printf("_POSIX_OPEN_MAZ:%d\n",_POSIX_OPEN_MAX); //POSIX标准的OPEN_MAX

}

