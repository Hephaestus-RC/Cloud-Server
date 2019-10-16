#include<stdio.h>
#include<signal.h>

void handler(int signo)
{
	printf("signo : %d\n",signo);
}
int main()
{
	signal(2,handler);
	while(1)
	{
		printf("Test...\n");
		sleep(1);
	}
	return 0;  
}
