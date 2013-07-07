#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	struct stat fileinfo;
	int mode;
	if(argc!=2)
	{
		printf("Usage ./a.out <pathname>\n");
		return -1;
	}
	//测试文件的访问方式	
	if((mode=fcntl(atoi(argv[1]),F_GETFL,(char *)0))==-1)
	{
		printf("fcntl error!\n");
		return -1;
	}
	else
	{
		switch(mode & O_ACCMODE)
		{
			case O_RDONLY:
				printf("mode readonly\n");
				break;
			case O_WRONLY:
				printf("mode writeonly\n");
				break;
			case O_RDWR:
				printf("mode read & write\n");
				break;
			default:
				printf("mode others\n");
				break;
		}
	}

	//测试文件的类型
	if(lstat(argv[1],&fileinfo)==-1)
	{
		printf("lstat error!\n");
		return -1;
	}
	else
	{
		if(S_ISREG(fileinfo.st_mode)!=-1)
		{
			printf("regular file\n");
		}
		else if(S_ISDIR(fileinfo.st_mode)!=-1)
		{
			printf("directory file\n");
		}
		else if(S_ISCHR(fileinfo.st_mode)!=-1)
		{
			printf("character file\n");
		}
		else if(S_ISBLK(fileinfo.st_mode)!=-1)
		{
			printf("block file\n");
		}
		else
		{
			printf("other file\n");
		}
	}

	//测试文件所有者ID(即是ll查看中的user权限)权限检查, 这里需要注意文件包括所有者ID和用户组ID，进行文件检查时如果是当前用户的话，就是ll第一项所看到的权限，如果用户ID和组ID不是同一个的话，这里检查的权限是以组ID的权限所看到的权限
	if(access(argv[1],R_OK)!=-1)
	{
		printf("Read access\n");
	}
	else
	{
		printf("no read access\n");
	}

	if(access(argv[1],W_OK)!=-1)
	{
		printf("Write access\n");
	}
	else 
	{
		printf("no write access\n");
	}

	if(access(argv[1],X_OK)!=-1)
	{
		printf("execute access\n");
	}
	else
	{
		printf("no execute access\n");
	}

	if(access(argv[1],F_OK)!=-1)
	{
		printf("file exsit\n");
	}
	else
	{
		printf("file not exsit\n");
	}

	return 0;
}

