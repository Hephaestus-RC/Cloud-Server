#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	//child write
	pid_t id = fork();
	if(id == 0)
	{
		close(fd[0]);
		char buf[1024];
		while(1)
		{
			printf("Please Enter some message:#");
			fgets(buf,100,stdin);
			write(fd[1], buf, strlen(buf));
			break;
		}
		close(fd[1]);
		exit(0);
	}
	//father read
	else
	{
		close(fd[1]);
		char buf[1024];
		while(1)
		{
			if(read(fd[0],buf,100)>0)
				printf("pipe message is :%s\n",buf);
			else
				break;
		}
		close(fd[0]);
		int st = 0;
		waitpid(id,&st,0);
		if(st>0)
			printf("code : %d,sig : %d\n",(st>>8)&0xFF,st&0x7F);
		
	}
	return 0;
}


