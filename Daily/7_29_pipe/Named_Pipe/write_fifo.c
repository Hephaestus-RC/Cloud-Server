#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define PATH "./myfifo"
#define SIZE 1024

int main()
{
	int a = mkfifo(PATH,0644);
	if(a == -1)
	{
		perror("mkfifo error\n");
		exit(0);
	}
	int fd = open(PATH,O_WRONLY);
	if(fd<0)
	{
		printf("open myfifo failed\n");
		return 0;
	}
	char buf[SIZE];
	memset(buf,'\0',sizeof(buf));
	while(1)
	{
		read(0,buf,sizeof(buf));
		int b = write(fd,buf,strlen(buf));
		//buf[b]='\0';
		if(b<0)
		{
			printf("write error!\n");
			break;
		}
	}
	close(fd);
	return 0;
}
