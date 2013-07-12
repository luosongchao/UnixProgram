
/**
 *	fork函数创建一个新的进程称为子进程（child process）
 *	fork函数被调用一次，但是返回两次。两次返回的唯一区别是子进程返回值是0
 *		父进程返回值则是新子进程的进程ID。
 *
 *	子进程是父进程的拷贝，子进程获得附近成的数据空间、堆、栈空间的副本。
 *	注意：
 *		子进程拥有的是父进程的副本，父子进程并不共享存储空间部分。父子进程
 *		共享正文段。
 *
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
	
	if((pid = fork()) < 0)
	{
		printf("fork child process error!\n");
		exit(0);
	}
	//子进程返回值为0
	else if(pid == 0)
	{
		global++;
		count++;		
	}
	//父进程返回子进程PID
	else
	{
		printf("child process id = %d\n",pid);
		
		//一般来说，fork之后是父进程先执行还是子进程先执行是不确定的，取决于内核的调度算法
		//这里使用sleep（3）；函数使得父进程休眠3秒钟，以使子进程先执行，但并不保证3秒钟已经足够
		sleep(3);
	}

	printf("global = %d, count = %d, pid = %d\n",global,count,getpid());
	return 0;
}
