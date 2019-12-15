//数据处理模块
//对boost库中的html进行下列操作：
//  1.去除html标签
//  2.将所有的HTML文件的内容合并成一个行文本文件（便于索引模块处理）
//  3.提取出每个HTML文档的标题，正文和url

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"../common/Util.hpp"
#include<boost/filesystem/path.hpp>
#include<boost/filesystem/operations.hpp>

using namespace std;

const std::string g_input_path = "../data/input"; //输入文件(HTML文档)的路径
const std::string g_output_path  = "../data/tmp/raw_input"; //输出文件的路径

//doc文档（待搜索的html）
struct DocInfo{
    string title; //保存标题
    string content; //保存正文
    string url; //保存url
};

bool EnumFile(const std::string& input_path,std::vector<std::string>& file_list)
{
    //使用ofstream对象，进行循环读取，将读取出的内容放在file_list中；
    //同时注意，需要过滤掉非HTML文档的其他文件
    
    namespace fs = boost::filesystem; //fs是boost库中文件系统的别名；
    fs::path root_path(input_path); //根据input_path构建一个path对象；

    if(!fs::exists(root_path))  //判断需要遍历的文件路径是否存在；
    {
        std::cout<<"[Input_path Not Exists!] input_path="<<input_path<<std::endl;
        return false;
    }

    //遍历该目录下的所有文件，同时过滤掉非HTML的其他文件
    fs::recursive_directory_iterator end_iter; //Boost库提供的一种特殊的迭代器，如果不初始化就当成结束标记
    for(fs::recursive_directory_iterator iter(root_path); iter != end_iter; ++iter)
    {
        if(!fs::is_regular_file(*iter)) //过滤掉目录
            continue;
        if(iter->path().extension()!=".html") //过滤掉非HTML文件
            continue;
        file_list.push_back(iter->path().string());
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParseTitle(const std::string& html,DocInfo& doc)//解析标题
{
    const std::string s = "<title>";
    auto begin = html.find(s);
    if(begin == std::string::npos)
    {
        cout<<"【<title> Not Found!】"<<endl;
        return false;
    }
    auto end = html.find("</title>");
    if(end == std::string::npos)
    {
        cout<<"【</title> Not Found!】"<<endl;
        return false;
    }

    begin+=s.size();
    if(begin > end)
    {
        cerr<<"【Title Begin End Error】"<<endl;
        return false;
    }
    
    doc.title = html.substr(begin,end-begin);
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParseContent(const std::string& html,DocInfo& doc)//解析正文 
{
    //正文中的 < 和 > 会被转义成 &lt 和 &gt
    bool is_content = true;
    for(auto c : html)
    {
        if(is_content)
        {
            if(c == '<')
            {
                is_content = false;
                continue;
            }
            else
            {
                if(c =='\n') //替换成空格，为了在保存在行文本文件中
                    c = ' ';
                doc.content.push_back(c);
            }
        }
        else 
            if(c == '>')
                is_content = true;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// 
bool ParseUrl(const std::string& file_path,DocInfo& doc)//解析url
{
    //因为Boost文档中的URL有一个统一的前缀()，所以只需要追加文档在本地的路径即可
    //本地路径都是在遍历g_input_path的内容，在构造后半部分时，从本地路径中截取去非g_input_path的内容即可
    string perfix = "https://www.boost.org/doc/libs/1_71_0/doc/";
    string suffix = file_path.substr(g_input_path.size());
    doc.url = perfix + suffix;
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParseFile(const std::string& file_path,DocInfo& doc)//分析文件
{
    //1. 打开文件，读取文件内容 
    //2. 解析标题 ParseTitle() ; 可以使用正则表达式
    //3. 解析正文，并且去除html标签
    //4. 解析出url
    
    std::string html;
    bool ret = FileUtil::Read(file_path,html); //将文件的所有内容全部保存到html中
    if(!ret)
    {
        std::cout<<"【Read Failed!】 file_path="<<file_path<<std::endl;
        return false;
    }

    ret = ParseTitle(html,doc);
    if(!ret)
    {
        std::cout<<"【ParseTitle Failed!】"<<file_path<<std::endl;
        return false;
    }
    ret = ParseContent(html,doc);
    if(!ret)
    {
        std::cout<<"【ParseContent Failed!】"<<file_path<<std::endl;
        return false;
    }
    ret = ParseUrl(file_path,doc);
    if(!ret)
    {
        std::cout<<"【ParseUrl Failed!】"<<file_path<<std::endl;
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteOutput(std::ofstream& output_file,const DocInfo& doc) //将结果构建成一个行文本文件
{
    //C++中的iostream和ofstream等这些对象都是禁止拷贝的
    //最终结果为一个行文本文件，每一行对应一个HTML文件
    //将doc中的所有元素组成一行；
    string line = doc.title + '\3' + doc.url + '\3' + doc.content + '\n';
    output_file.write(line.c_str(),line.size());
}


int main()
{
    //1. 枚举出输入路径中的所有html文档的路径,保存到一个数组中；
    std::vector<std::string> file_list; //保存每个HTML文件的路径； 
    bool ret = EnumFile(g_input_path,file_list);
    if(!ret)
    {
        std::cout<<"【EnumFIle failed!】"<<std::endl;
        return 1;
    }

#if 0
    //test第一步的结果
    for(std::string path : file_list)
        cout<<path<<endl;
#endif 

    //检测输出文件的合法性，并打开输出文件
    std::ofstream output_file(g_output_path.c_str());
    if(!output_file.is_open())
    {
        std::cout<<"【Output_File Open Failed!】 g_output_path="<<g_output_path<<std::endl;
        return 1;
    }
    
    //2. 依次处理每个枚举出的html文档，并对该文档进行分析，分析得出html文档的标题/正文/url，同时去标
    int i = 0;
    for(const auto& file_path : file_list)
    {
        DocInfo info;
        ret = ParseFile(file_path,info);
        if(!ret)
        {
            std::cout<<"【File Parse Failed!】 File_path="<<file_path<<std::endl;
            continue;
        }

        cout<<"DocInfo: Title="<<info.title<<endl;
        cout<<"           url="<<info.url<<endl;
    
     //3. 将分析结果按照一行的形式写入到输出文件中
     WriteOutput(output_file,info);
     cout<<i++<<endl;
    }
    output_file.close();

    return 0;
}








//00:36:00
