
/**
 *	vfork函数用于创建一个新进程，该新进程的目的是exec一个新程序，
 *	vfork函数不同于fork函数，主要区别在于：
 *		（1）vfork函数在父进程的空间中运行，而fork会将父进程的地址空间完全复制到子进程中。
 *		（2）vfork函数保证子进程先运行，在子进程调用exec或者exit之后父进程才可能被调度运行。
 */ 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int global = 11;

int main(int argc,char *argv[])
{
	char *buf="hello world";
	pid_t pid;
	int count = 3;

	printf("before vfork ,global = %d , count = %d\n",global,count);	

	if((pid = vfork()) < 0)
	{
		printf("vfork child process error!\n");
		exit(0);
	}
	//子进程返回值为0
	else if(pid == 0)
	{
		global++;
		count++;	
		printf("in child process,global = %d ,count = %d\n",global,count);

		//vfork保证子进程先运行，在子进程调用exec或exit之后父进程才能够被调度运行。
		//在子进程调用exec或exit之前，内核会使父进程处于休眠状态。
		//_exit()不同于exit()，_exit()并不执行标准I/O缓冲的冲洗操作，如果通过exit程序的输出是不确定的。	
		_exit(0);
	}
	//父进程返回子进程PID
	else
	{
		printf("child process id = %d\n",pid);
	}

	printf("global = %d, count = %d,current process pid = %d\n",global,count,getpid());
	return 0;
}
