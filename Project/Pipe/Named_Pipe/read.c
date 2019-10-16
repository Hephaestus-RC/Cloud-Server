#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

//read
#define PATH "./myfifo"
#define SIZE 1024

int main()
{
	int fd = open(PATH,O_RDONLY);
	if(fd < 0)
	{
		perror("open error\n");
		exit(0);
	}
	char msg[SIZE];
	memset(msg,'\0',sizeof(msg));
	while(1)
	{
		ssize_t num = read(fd,msg,sizeof(msg));
		if(num <= 0)
		{
			perror("read error or end \n");
			break;
		}
		printf("read : %s ",msg);
	}
	close(fd);
	return 0;

	
}
