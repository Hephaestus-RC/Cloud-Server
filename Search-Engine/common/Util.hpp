#pragma once 
#include<string>
#include<fstream>
#include<vector>
#include<boost/algorithm/string.hpp>

class FileUtil
{
    public:
        static bool Read(const std::string& file_path,std::string& s)
        {
            std::ifstream file(file_path.c_str());
            if(!file.is_open())
                return false;
            
            //按行读取文件
            std::string line;
            while(std::getline(file,line))
                s += (line+'\n');
            file.close();
            return true;
        }

        static bool Writer(const std::string& from,std::string& to)
        {
            std::ofstream file(from.c_str());
            if(!file.is_open())
                return false;
            file.write(to.c_str(),to.size());
            file.close();
            return true;
        }
};

class StringUtil
{
    public:
        static void Split(const std::string& input,std::vector<std::string>& output,const std::string& split_char)
        {
            //boost库中的字符串切分函数
            boost::split(output,input,boost::is_any_of(split_char),boost::token_compress_off);
        }
};
