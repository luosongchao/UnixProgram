/*
 *说明:函数用来输入指定目录的目录项
 *用法：编译后的文件名   目录名
 *注意事项：包含头文件#include<dirent.h>其中包含DIR / dirent/ opendir（）/
 *closedir()/readdir()方法用来读取目录和目录项
 * */
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	DIR *dir;
	struct dirent  *dirp;
	//参数个数其中./a.out  /home 第一个参数是./a.out第二个参数是/home
	if(argc!=2)
	{
		printf("%s\n","Usage ls directory_name");
	}
	if(dir=opendir(argv[1]),dir==NULL)
	{
		printf("%s\n","Can't Open file ");
	}
	while(dirp=readdir(dir),dirp!=NULL)
	{
		printf("%s\n",dirp->d_name);
	}
	closedir(dir);
	return 0;
}
