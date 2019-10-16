#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void Test1()
{
	int arr[] = {1,2,3,4,5,6,7};
	vector<int> first;
	vector<int> second(4,100);
	vector<int> third(second.begin(),second.end());
	vector<int> fourth(arr,arr+(sizeof(arr)/sizeof(arr[1])));
	vector<int> five(fourth);

	//vector<int>::iterator it = first.begin();
	//while(it != first.end())
	//	cout<<*it<<" ";
	//cout<<endl;

	//vector<int>::iterator it = second.begin();
	//while(it != second.end())
	//	cout<<*it<<" ";
	//cout<<endl;
	//

	//vector<int>::iterator it = third.begin();
	//while(it != third.end())
	//	cout<<*it<<" ";
	//cout<<endl;
	//	
	vector<int>::iterator it = fourth.begin();
	while(it != fourth.end())
		cout<<*it++<<" ";
	cout<<endl;
	
	vector<int>::iterator it1 = five.begin();
	while(it1 != five.end())
		cout<<*it1++<<" ";
	cout<<endl;
	
	for (std::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout <<' '<< *it;
	cout<<endl;
	for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout <<' '<< *it;
	cout<<endl;
	for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout <<' '<< *it;
	cout<<endl;

}
void PrintVector(vector<int>& v)
{
	vector<int>::iterator it = v.begin();
	while(it != v.end())
		cout<<*it++<<' ';
	cout<<endl;
}
void RPrintVector(vector<int>& v)
{
	vector<int>::reverse_iterator it = v.rbegin();
	while(it != v.rend())
		cout<<*it++<<' ';
	cout<<endl;
}
void Test2()
{
	int arr[] = {1,2,3,4,5,6,7};
	vector<int> v1;
	vector<int> v2(4,100);
	vector<int> v3(v2.begin(),v2.end());
	vector<int> v4(arr,arr+(sizeof(arr)/sizeof(arr[1])));
	vector<int> v5(v4);
	
	PrintVector(v1);
	PrintVector(v2);
	PrintVector(v3);
	PrintVector(v4);
	PrintVector(v5);
	
	RPrintVector(v1);
	RPrintVector(v2);
	RPrintVector(v3);
	RPrintVector(v4);
	RPrintVector(v5);
}

void Test3()
{
#if 0
	vector<int> v;
	size_t sz = v.capacity();
	cout<<"vector first capacity is : "<<sz<<endl;
	for(int i = 0;i<100;++i)
	{
		v.push_back(i);
		if(sz!=v.capacity())
		{
			sz = v.capacity();
			cout<<"capacity is change : "<<sz<<endl;
		}
	}
#endif 

	vector<int> v1;
	v1.reserve(100);
	PrintVector(v1);
	size_t sz1 = v1.capacity();
	cout<<"vector first capacity is : "<<sz1<<endl;
	for(int i = 0;i<100;++i)
	{
		v1.push_back(i);
		if(sz1 != v1.capacity())
		{
			sz1 = v1.capacity();
			cout<<"capacity is change : "<<sz1<<endl;
		}
		
	}
	PrintVector(v1);
}

void Test4()
{
	int arr[] = {1,2,3,4,5,6,7};
	vector<int> v1(arr,arr+sizeof(arr)/sizeof(arr[0]));
	cout<<"befor: ";
	PrintVector(v1);
	
	cout<<"Push:  ";
	v1.push_back(8);
	v1.push_back(9);
	PrintVector(v1);

	cout<<"Pop:   ";
	v1.pop_back();
	v1.pop_back();
	PrintVector(v1);

	cout<<"Insert:   ";
	v1.insert(v1.begin(),0);
	PrintVector(v1);

	cout<<"Erase:   ";
	v1.erase(v1.begin());
	PrintVector(v1);


	cout<<"find:   ";
	cout<<*(find(v1.begin(),v1.end(),3))<<endl;
	
	cout<<"new bianli :  ";
	for(auto& e:v1)
	{
		cout<<e<<" ";
	}
	cout<<endl;

	vector<int> swapV={11,22,33,44};
	//vector<char> swapV={'a','b','c','d'};
	v1.swap(swapV);
	cout<<"V1:   ";
	PrintVector(v1);
	cout<<"swapV:   ";
	PrintVector(swapV);
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	return 0;
}
