#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
//write

#define PATH "./myfifo"
#define SIZE 1024
int  main()
{
	int ret = mkfifo(PATH,0644);
	if(ret == -1 )
	{
		perror("mkfifo error\n");
		exit(0);
	}
	int fd = open(PATH,O_WRONLY);
	if(fd < 0)
	{
		perror("open error\n");
		exit(1);
	}
	char buf[SIZE]={0};
	while(1)
	{
		printf("write : ");
		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,strlen(buf));
		memset(buf,'\0',strlen(buf));
	}
	close(fd);
	return 0;
	

}
