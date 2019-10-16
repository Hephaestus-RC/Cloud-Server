#include<stdio.h>
#include<unistd.h>

int main()
{
	char bar[100] = {'\0'};
	int i;
	const char* laber = "/|-\\";
	for( i = 0;i<=100;i++)
	{
		printf("[%3d%%][%-100s][%c]\r",i,bar,laber[i%4]);
		fflush(stdout);
		bar[i] = '#';
		usleep(10000);
	}
	printf("\n");
	return 0;
}
