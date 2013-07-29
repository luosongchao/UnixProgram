#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 1024

int main(int argc,char *argv[])
{
	int fd[2];
	pid_t pid;
	char *pager;
	FILE *file;

	if(argc!=2)
	{
		printf("usage: a.out <pathname>\n");
		exit(0);
	}

	if(pipe(fd)<0)
	{
		printf("pipe create error!\n");
		exit(0);
	}

	if((pid=fork())<0)
	{
		printf("fork error!\n");
		exit(0);
	}

	if(pid>0)
	{
		close(fd[0]);
		file=fopen(argv[1],"r");
		if(file==NULL)
		{
			printf("file open error!\n");
			exit(0);
		}

		char line[MAXLINE];
			while(fgets(line,MAXLINE,file)!=NULL)
			{
				int n=strlen(line);
				if(write(fd[1],line,n)!=n)
				{
					printf("write error!\n");
					exit(0);
				}

			}	

		if(ferror(file))
		{
			printf("file gets error!\n");
			exit(0);
		}
		close(fd[1]);

		if(waitpid(pid,NULL,0)<0)
		{
			printf("waitpid error!\n");
			exit(0);
		}
		exit(0);
	}
	else
	{
		close(fd[1]);

		if(fd[0]!=STDIN_FILENO)
		{
			if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO)
			{
				printf("dup2 error !\n");
				exit(0);
			}
			
			close(fd[0]);
		}

		if((pager=getenv("PAGER"))==NULL)
		{
			pager=DEF_PAGER;
		}
		
		char *argv0;
		if((argv0=strrchr(pager,'/'))!=NULL)
		{
			argv0++;
		}
		else
		{
			argv0=pager;
		}

		if(execl(pager,argv0,(char *)0)<0)
		{
			printf("execl error!\n");
			exit(0);
		}
		exit(0);
	}
}

