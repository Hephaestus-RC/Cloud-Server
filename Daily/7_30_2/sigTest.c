#include<stdio.h>
#include<unistd.h>


void handler(int a)
{
	printf("catch is sig : %d\n",a);
}
int main()
{
#if 0
	int* p;
	p = (int*)100;
	*p = 100;
	

	while(1)
	{
		printf("I am a process...\n");
		sleep(1);
	}
---------------------------------	
	int a = 1/0;
#endif
	printf("pid = %d\n",getpid());
	signal(2,handler);
	while(1)
	{
		printf("Running ...\n");
		sleep(1);
	}

	return 0;
}
