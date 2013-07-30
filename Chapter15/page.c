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

	/**
	 * 创建管道
	 */
	if(pipe(fd)<0)
	{
		printf("pipe create error!\n");
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

	/**
	 * 父进程读取文件，写入管道
	 */ 
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

		/**
		 * 判断fgets是否出错
		 */ 
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
			/**
			 * dup2(int filed,int field2)复制一个现有的文件描述符
			 * 用filed2指定新描述符的数值
			 *   @return  成功返回新的文件文件描述符，出错返回-1
			 */ 
			if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO)
			{
				printf("dup2 error !\n");
				exit(0);
			}

			close(fd[0]);
		}

		/**
		 * getenv(const char* name)获取环境变量的值
		 */ 
		if((pager=getenv("PAGER"))==NULL)
		{
			pager=DEF_PAGER;
		}

		char *argv0;

		/**
		 * 从字符串的最后开始查找字符，并返回字符所在位置到最末尾的所有字符
		 */
		if((argv0=strrchr(pager,'/'))!=NULL)
		{
			argv0++;	//删除strrchr返回字符串中的'/'
		}
		else
		{
			argv0=pager;
		}

		/**
		 * pager默认值为/bin/more是系统中的分页程序
		 * 下面的函数execl(const char *pathname,const char *arg0,....(char *)0)
		 * 其中第一个参数，pathname是一个可执行文件
		 * 注：
		 *      可以直接到/bin 目录下，查看并运行more可执行文件
		 */ 
		if(execl(pager,argv0,(char *)0)<0)
		{
			printf("execl error!\n");
			exit(0);
		}
		exit(0);
	}
}

