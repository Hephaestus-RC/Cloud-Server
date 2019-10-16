#include<iostream>
using namespace std;

class HeapOnly
{
	public:
		static HeapOnly* GetClass()
		{
			return new HeapOnly;
		}
	private:
		HeapOnly() = delete;
		HeapOnly(const HeapOnly&) = delete;
};
class StackOnly
{
	public:
		StackOnly()
		{}
	private:
		void* operator new(size_t size)=delete;
		void* operator new[](size_t num) = delete;
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;
};

int main()
{
//	HeapOnly ho;
//	StackOnly* so = new StackOnly;

	return ;
}

