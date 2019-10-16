#include<iostream>
using namespace std;

struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	int _data;

	void* operator new (size_t n)
	{
		void * p = nullptr;
		p = allocator<ListNode>().allocate(1);
		cout<<"memory pool allocate"<<endl;
		return p;
	}
	void operator delete(void * p)
	{
		allocator<ListNode>().deallocate((ListNode*)p,1);
		cout<<"memory pool deallocate"<<endl;

	}
};

class List
{
	public:
		List()
		{
			_head = new ListNode;
			_head->_next = _head;
			_head->_prev = _head;
		}
		~List()
		{
			ListNode* cur = _head->_next;
			while(cur != _head)
			{
				ListNode* next = cur->_next;
				delete cur;
				cur = next;
			}
			delete _head;
			_head = nullptr;
		}
	private:
		ListNode* _head;
};

int main()
{
	List l;
	return 0;
}

#if 0
void Test()
{
	int* pa = new int(1111);
	cout<<*pa<<endl;
	
	int* pa1 = new int{1111};
	cout<<*pa1<<endl;
	
	int* parr = new int[10]{1,2,3,4,5,6};

//	for(int i = 0;i<10;++i)
//	{
//		parr[i] = i+10;
//	}
	for(int i = 0;i<10;++i)
	{
		cout<<parr[i]<<endl;
	}
	
	delete pa;
	delete pa1;
	delete[] parr;
}

class Test
{
	public:
		Test()
			:_data(0)
		{
			cout<<"Test_init()"<<endl;
		}
		~Test()
		{
			cout<<"Test::~Test()"<<endl;
		}
	private:
		int _data;
};
void Test2()
{
	//Test* t = new Test;
	//delete t;
	//Test* tarr = new Test[10];
	//delete tarr;

	//Test* p1 = new Test;
	//delete p1;
}

int main()
{
	//Test();
	Test2();
	return 0;
}
#endif
