#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main()
{
	int c;

	while((c=getchar())!=EOF)
	{
		if(islower(c))
		{
			c=toupper(c);
		}

		if(putchar(c)==EOF)
		{
			printf("output error!\n");
		}

		if(c=='\n')
		{
			fflush(stdout);
		}
	}
	exit(0);
}
