//pipe管道，创建一个父进程与子进程之间的通信，
//父进程向子进程发送消息

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int fd[2];
	pid_t pid;

	/**
	 * #include<unistd.h>
	 * int pipe(filed[2]);
	 * pipe函数用户创建管道，经由参数fileds 返回这两个文件描述符，
	 * fileds[0]为读而打开
	 * fileds[1]为写而打开，fileds[1]的输出是fields[0]的输入
	 */ 
	int status=pipe(fd);
	if(status!=0)
	{
		printf("pipe error!\n");
		exit(0);
	}

	/**
	 * 创建进程
	 */ 
	if((pid=fork())<0)
	{
		printf("fork error!\n");
		exit(0);
	}

	if(pid==0)
	{
		printf("in child process...\n");
		close(fd[1]);
		char line[1024];
		int n=read(fd[0],line,1024);
		write(STDOUT_FILENO,line,n);

	}
	else
	{
		printf("in parent process...\n");
		close(fd[0]);
		write(fd[1],"hello world!\n",20);
	}

	exit(0);
}
