#include<stdio.h>
#include<unistd.h>

int main()
{
	char bar[100] = {'\0'};
	int i;
	for( i = 0;i<=100;i++)
	{
		printf("\033[41m\033[37m\033[1m[%-3d%%]%s\033[0m \r",i,bar);
		fflush(stdout);
		bar[i] = '#';
		usleep(50000);
	}
	printf("\n");
	return 0;
}
