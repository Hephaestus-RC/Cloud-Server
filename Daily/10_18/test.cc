#include<stdio.h>
#include<unistd.h>
int main()
{
	char buf[101] = {0};
	char stat[] = {'-','\\','|','/'};
	for(int i = 0;i<=100;++i)
	{
		buf[i] = '*';
		usleep(50000);
		printf("[%-101s] [%3d%] [%c]\r",buf,i,stat[i%4]);
		fflush(stdout);
	}
	printf("\n");
	return 0;
}
