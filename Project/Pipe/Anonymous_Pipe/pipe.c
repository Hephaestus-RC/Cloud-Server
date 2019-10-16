#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe error\n");
		exit(0);
	}

	pid_t id = fork();
	if(id<0)
	{
		perror("fork error\n");
		exit(0);
	}
	else if(id == 0)
	{
		//chidl wirte
		close(fd[0]);
		char buf[1024]= {0};
		printf("Please enter massage: ");
		fgets(buf,sizeof(buf),stdin);
		write(fd[1],buf,strlen(buf));
		close(fd[1]);
	}
	else
	{
		//father read
		close(fd[1]);
		int st = 0;
		char msg[1024];
		read(fd[0],msg,sizeof(msg));
		printf("child massage : %s",msg);
		close(fd[0]);
		waitpid(id,&st,0);
		printf("child code : %d , sig: %d \n",(st>>8)&0xFF,st&0x7F);
		exit(0);
	}
}
