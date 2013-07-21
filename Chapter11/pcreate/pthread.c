#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

pthread_t ntid;
void printids();
void *thr_fn();

int main()
{
	int err;
	err=pthread_create(&ntid,NULL,thr_fn,NULL);
	if(err != 0)
	{
		printf("create thread error!\n");		
		exit(-1);
	}
	printids("main thread:");
	sleep(1);
	exit(0);
}

void printids(const char  *msg)
{
	pid_t pid;
	pthread_t tid;
	
	pid=getpid();
	tid=pthread_self();

	printf("%s pid: %u tid: %u (0x%x)\n",msg,(unsigned int)pid,(unsigned int)tid,(unsigned int )tid);
}

void *thr_fn()
{
	printids("new thread:");
	return ((void*)0) ;
}

