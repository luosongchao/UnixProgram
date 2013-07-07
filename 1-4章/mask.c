#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

#define RWXR ( S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP)
#define RWRWRW (S_IRUSR | S_IWUSR |S_IRGRP |S_IWGRP |S_IROTH |S_IWOTH)

int main()
{
	//设置mask掩码，这里是允许创建文件的所有掩码设置
	umask(0);
	//创建文件，文件的执行权限为RWRWRW
	if(creat("maskTest_1",RWRWRW) ==-1)
	{
		printf("create file error!\n");
	}
	else
	{
		//显示所有文件信息
		//printf("文件信息如下：\n");
		//execlp("ls","ls","-il",(char *)0);
		
		//更改文件的权限, 删除已有的权限
		if(chmod("maskTest_1",S_IXUSR|S_IXGRP|S_IXOTH)==-1)
		{
			printf("chmod error\n");
		}
	}

	/*
	 * 注：这里没有报错。但是执行完上一个语句之后，没有继续往下执行
	 * 这是因为execlp函数调用成功，进程自己的执行代码就会变成加载程序的代码
	 * execlp后边的代码也就不会执行
	 * */	

	//设置掩码为RWXR
	umask(RWXR);
	int ID;
	//创建文件，文件执行权限是RWRWRW
	if((ID=creat("maskTest_2",RWRWRW))==-1)
	{
		printf("create file error!\n");
	}
	else
	{
		struct stat fileinfo;
		//在已有文件权限的基础上对文件权限进行更改
		if(fstat(ID,&fileinfo)!=-1)
		{
			fchmod(ID,fileinfo.st_mode | S_IRUSR);
		}
		else
		{
			printf("get makeTest_2 stat error\n");
			return -1;
		}
		//显示所有文件信息
		execlp("ls","ls","-il",(char *)0);
	}
	return 0;
}
