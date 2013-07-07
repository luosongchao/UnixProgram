#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define BUFFSIZE 1024
int main()
{
	printf("%s%d\n","Get PID:",getpid());
	pid_t pid;
	int status;
	char buf[BUFFSIZE];
	printf("%% ");
	while(fgets(buf,BUFFSIZE,stdin)!=NULL)
	{
		if(buf[BUFFSIZE-1]=='\n')
		{
			buf[BUFFSIZE-1]=0;
		}
		if(pid=fork(),pid<0)
		{
			printf("fork error");
		}
		else if(pid==0)
		{
			execlp(buf,buf,(char *)0);
			printf("can't exe %s",buf);
			exit(127);	
		}
		if(pid=waitpid(pid,&status,0),pid<0)
		{
			printf("status :%d,waitpid error",status);
		}
	}
	return 0;
}
