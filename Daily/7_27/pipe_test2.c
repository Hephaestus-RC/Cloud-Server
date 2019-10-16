#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret>0)
	{
		perror("pipe faild\n");
		exit(1);
	}
	else if(ret == 0)
	{
		int st = 0;
		pid_t id = fork();
		if(id == 0)
		{
			//child write
			close(fd[0]);
			char buf[1024] = "this is child buff\n";
			while(1)
			{	
				write(fd[1],buf,strlen(buf));
			}
			close(fd[0]);
			exit(0);
		}
		else
		{
			//father read
			close(fd[1]);
			char buf[1024];
			read(fd[0],buf,sizeof(buf));
			printf("child buf:%s\n",buf);
			close(fd[0]);
		}
	}
	return 0;
}
