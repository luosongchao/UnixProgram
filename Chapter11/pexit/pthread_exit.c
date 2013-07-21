#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void *thr_fn1();
void *thr_fn2();

int main()
{
	int err;
	pthread_t pid_1,pid_2;

	/**
	 * pthread_create() 创建进程
	 */ 
	err=pthread_create(&pid_1,NULL,thr_fn1,NULL);
	if(err!=0)
	{
		printf("create pthread error!\n");
	}
	
	err=pthread_create(&pid_2,NULL,thr_fn2,NULL);
	if(err!=0)
	{
		printf("create pthread error!\n");
	}
	
	/**
	 * 线程一直阻塞，直到线程调用pthread_exit（）从启动例程中返回或者被取消
	 */ 
	err=pthread_join(pid_1,&tret);
	if(err!=0)
	{
		printf("thread_1 exit error!,error code: %d\n",err);
	}
	else
	{
		printf("pthread_1 exit code:%d\n",(int)tret);
	}

	err=pthread_join(pid_2,&tret);
	if(err!=0)
	{
		printf("thread_1 exit error!,error code: %d\n",err);
	}
	else
	{
		printf("pthread_2 exit code:%d\n",(int)tret);
	}
}

/**
 * 线程1调用执行函数
 */ 
void *thr_fn1()
{
	printf("thread_1 returnning...\n");
	return ((void *)1);
}

/**
 * 线程2调用执行函数
 */ 
void *thr_fn2()
{
	printf("thread_2 returnning...\n");
	return ((void *)2);
}
