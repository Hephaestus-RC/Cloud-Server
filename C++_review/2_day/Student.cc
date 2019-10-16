#include<iostream>
using namespace std;


class Student 
{
	private:
		int _id;
		char* _name;
		int _age;
	public:
		Student(int id,char* name,int age)
			:_id(id)
			,_name(name)
			,_age(age)
		{
		cout<<"Student Init: id = "<<_id<<" name = "<<_name<<" age = "<<_age<<endl;
		}
		~Student()
		{
			_id = 0;
			_name = nullptr;
			_age = 0;
			cout<<"Student Destory"<<endl;
		}

};
int main()
{
	Student s1(45,"rencheng",22);
	return 0;
}
