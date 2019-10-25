#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv,char* env[])
{
	//1.通过命令行参数里的环境变量来显示变量内容以及变量名称
	/*
	for(int i = 0; env[i]!=NULL; i++)
	{
		printf("env[%d] = %s\n",i,env[i]);
	}
	*/
	//2.引入外部参数
	extern char** environ;
	for(int i = 0; environ[i]!=NULL; i++)
	{
		printf("env[%d] = %s\n",i,environ[i]);
	}
	//3.getenv() 通过环境变量名称来获取环境变量内容
	char* ptr = getenv("MYTEST");
	if(ptr == NULL)
	{
		printf("Haven't MYTEST\n");
		return -1;
	}
	printf("MYTEST=%s\n",ptr);
	return 0;
}
