#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("PID:%d UID:%d,GID:%d\n",getpid(),getuid(),getgid());
	execlp("ls","ls","-il",(char *)0);
	return 0;
}
