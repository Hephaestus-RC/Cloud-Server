#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(int signo)
{
	printf("signo is %d \n",signo);
	exit(0);
}

int main()
{
	int i = 1,j = 1;
	sigset_t set,oset,set1;
	sigemptyset(&set);
	sigaddset(&set,2);
	//set Block
	sigprocmask(SIG_BLOCK,&set,&oset);
	signal(2,handler);
	while(j++)
	{
		printf("Block:  ");
		for(i = 1;i<=31;++i)
		{
			if(sigismember(&set,i) == 1)
				printf("1 ");
			else
				printf("0 ");
		}	
		printf("\n");
		//printf("Pending:");
		//sigpending(&set1);
		//for(i = 1;i<=31;++i)
		//{
		//	if(sigismember(&set1,i) == 1)
		//		printf("1 ");
		//	else
		//		printf("0 ");
		//}	
		//printf("\n\n");
		if(j == 10)
		{
			//sigprocmask(SIG_BLOCK,&oset,&set);
			sigemptyset(&set);
			sigprocmask(SIG_SETMASK,&oset,&set);
		}
		sleep(1);
	}
	return 0;
}
