#ifndef __UTIL_HPP__
#define __UTIL_HPP__

//------------这个文件用来保存一些协助方法，与具体实习Web服务器没有直接关系

#include<iostream>
#include<string>
#include<algorithm>
#include<sstream>

class Util
{
	public:
		//将字符串中的字符全部转换成大写字符
		static void StringToUpper(std::string& s)
		{
			std::transform(s.begin(),s.end(),s.begin(),::toupper);
		}
		//字符串转整数
		static int StringToInt(std::string& s)
		{
			int ret = 0;
			std::stringstream ss(s);
			ss>>ret;
			return ret;
		}
		//将字符串中的子串打散，然后保存在vector中
		static void TransfromVector(std::string& s,std::vector<std::string>& v)
		{
		}
		//将一个字符串按“: ”构成key和value
		static void MakeKV(std::string& k,std::string& v)
		{
		}
};



























#endif
