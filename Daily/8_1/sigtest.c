#include<stdio.h>
#include<signal.h>

int volatile flag = 0;
void handler(int signo)
{
	flag = 1;
	printf("flag changs : flag = %d\n",flag);
}
int main()
{
	signal(2,handler);
	while(!flag);

	return 0;
}
