#include<iostream>
using namespace std;

int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int loacl = 1;

	int num1[10] = {1,2,3,4};
	char char2[] = "abcd";
	char* pchar3 = "abcd";
	int* ptr1 = (int*)malloc(sizeof(int)*4);
	int* ptr2 = (int*)calloc(4,sizeof(int));
	int* ptr3 = (int*)realloc(ptr2,sizeof(int)*4);
	
	cout<<"globalVar   "<<&globalVar <<endl;
	cout<<"staticGloablVar   "<<&staticGlobalVar<<endl;
	cout<<"staticVar   "<<&staticVar <<endl;
	cout<<"local   "<<&loacl <<endl;
	cout<<"num1   "<<&num1 <<endl;
	cout<<"char2   "<<&char2 <<endl;
	cout<<"pchar3   "<<&pchar3 <<endl;
	cout<<"ptr1   "<<&ptr1 <<endl;
	cout<<"ptr2   "<<&ptr2 <<endl;
	cout<<"ptr3  "<<&ptr3 <<endl;
	free(ptr1);
	free(ptr3);
}
int main()
{
	//Test();
	
	int* pa = (int*)calloc(4,sizeof(int));
	cout<<*pa<<endl;
	cout<<pa<<endl;
	return 0;
}
