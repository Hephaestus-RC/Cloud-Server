#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#define PATH "./myfifo"
#define SIZE 1024

//This is Read
int main()
{
	int fd = open(PATH,O_RDONLY);
	if(fd<0)
	{
		printf("open file error!\n");
		exit(0);
	}
	else
	{
		char buf[SIZE];
		memset(buf,'\0',sizeof(buf));
		while(1)
		{
			int a = read(fd,buf,sizeof(buf));
			//int a = read(fd,buf,sizeof(buf));
			if(a <= 0)
			{
				perror("read error or end\n");
				break;
			}
			printf("read massage : %s\n",buf);
		}
		close(fd);
	}
	return 0;
}
