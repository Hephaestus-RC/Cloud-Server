#include<iostream>
#include"Util.hpp"

using namespace std;

int main()
{
	vector<string> v;
	string s = "a: b\nb: d\nf: h";
	Util::TransfromVector(s,v);
	auto it = v.begin();
	while(it!=v.end())
	{
		cout<<*it<<endl;
		it++;
	}
	cout<<v.size()<<endl;

	return 0;
}
