#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

//child keep write, father keep read
int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret > 0)
	{
		//pipe failed
		perror("pipe failed\n");
		exit(0);
	}
	else if(ret == 0)
	{
		//pipe success
		pid_t id = fork();
		if(id<0)
		{
			perror("fork failed\n");
			exit(0);
		}
		else if(id == 0)
		{
			//child write
			close(fd[0]);
			char buf[1024] = "This is child massage";
			while(1)
			{
				printf("child write:%s\n",buf);
				write(fd[1],buf,sizeof(buf));
				sleep(2);
			}
			close(fd[1]);
		}
		else
		{
			//father read
			close(fd[1]);
			sleep(1);
			char buf[1024];
			while(1)
			{
				read(fd[0],buf,sizeof(buf));
				printf("father read:%s\n",buf);
			}
			close(fd[0]);
		}
	}
	return 0;
}
