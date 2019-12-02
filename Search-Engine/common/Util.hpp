#pragma once 
#include<string>
#include<fstream>


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
