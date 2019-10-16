#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

//child write once and close,father keep read
int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret > 0)
	{
		perror("pipe");
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
			//child 
			close(fd[0]);
			char buf[1024] = "This is child massage";
			printf("child write : %s\n",buf);
			write(fd[1],buf,sizeof(buf));
			close(fd[1]);
			exit(2);
		}
		else
		{
			//father
			int st = 0;
			close(fd[1]);
			char* buf;
			while(1)
			{
				read(fd[0],buf,sizeof(buf));
				if(buf!= NULL)
				{
					printf("father read : %s\n",buf);
					buf = NULL;	
				}
				else
					break;
			}
			close(fd[0]);
			waitpid(id,&st,NULL);
			printf("code : %d ,sig : %d\n",(st>>8)&0XFF,st&0X7F);
			exit(3);
		}
	}
}
