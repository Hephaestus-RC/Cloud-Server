#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t id = fork();
    if(id<0)
	{
		perror("fork failed!\n");
		return 1;
	}
	else if(id == 0)
	{
		printf("child is Running,pid:[%d]\n",getpid());
		sleep(3);
		exit(257);
	}
	else
	{
		int st;
		pid_t ret = waitpid(-1,&st,0);
		printf("It's test is for Hangwaiting\n",getpid());
		if( ret == id  && ((st&0X7F)==0))
		{
		    printf("running success ,child exit code = %d\n",(st>>8)&0XFF);
			return 0;
		}
		else
		{
		    printf("child signed code = %d\n",st&0X7F);
			return 0;
		}	
    }
}
