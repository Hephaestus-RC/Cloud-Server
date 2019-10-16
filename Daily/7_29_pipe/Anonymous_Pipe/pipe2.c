#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

//child keep write , father just read once 
int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret > 0)
	{
		perror("pipe\n");
		exit(0);
	}
	else if(ret == 0)
	{
		pid_t id = fork();
		if(id < 0)
		{
			perror("fork");
			exit(1);
		}
		else if(id == 0)
		{
			//child write
			close(fd[0]);
			char buf[1024]="This is child massage";
			while(1)
			{
				printf("child massage:%s\n",buf);
				write(fd[1],buf,sizeof(buf));
			}
			close(fd[1]);
		}
		else
		{
			//father read
			close(fd[1]);
			char buf[1024];
			sleep(0.5);
			read(fd[0],buf,sizeof(buf));
			printf("\nfather read:%s\n",buf);
			close(fd[0]);
		}

	}
}
