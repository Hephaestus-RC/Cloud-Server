#include<stdio.h>
#include"div.h"
#include"mul.h"

int main()
{
	int a = 20;
	int b = 10;
	printf("a * b = %d\n",mul(a,b));
	printf("a / b = %d\n",div(a,b));
	
	return 0;
}
