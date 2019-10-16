#include<iostream>
#include<cstring>

namespace N1
{
	class String
	{
		public:
			String(const char* s)
				:size(strlen(s))
				,str(new strlen(s))
			{
				if(size == 0)
					str = "";
				strcpy(str,s);
			}
			String& operator=(const String& s)
			{

			}
			~String()
			{

			}
		private:
			char* str;
			int  size;
	};
}

int main()
{
	N1::String s1("Hello RC");
	std::cout<<s1<<std::endl;
	return 0;
}
