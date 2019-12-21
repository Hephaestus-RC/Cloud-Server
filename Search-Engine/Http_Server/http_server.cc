#include<iostream>
#include"httplib.h"
#include"../search/searcher.h"
#include"../common/Util.hpp"
using namespace std;

int main()
{
    std::string ss;
    FileUtil::Read("./web/index.html",ss);
    searcher::Searcher s;
    cout<<"Searcher Init()"<<endl;
    if(!s.Init("../data/tmp/raw_input"))
    {
        cout<<"Searcher Init Error!"<<endl;
        return 1;
    }

    cout<<"Search Init Finish!"<<endl;
    
    using namespace httplib;
    Server server;
    
    cout<<"Ready To Server.Get!"<<endl;
    server.Get("/search",[&s](const Request& req,Response& res) { 
            
            //std::string ss;
            //FileUtil::Read("./web/index.html",ss);
            //res.set_content(ss,"text/html"); //浏览器可以直接处理json格式的对象
            
             string query = req.get_param_value("query"); //获取参数内容（即搜索词）
            string result;
            s.Search(query,result);
             res.set_content(result,"text/html"); //浏览器可以直接处理json格式的对象

            });
    cout<<"Server.Get finish, Ready To Listen!"<<endl;
    server.set_base_dir("./web");
    server.listen("0.0.0.0",9999);
    cout<<"Listen finish!"<<endl;
    
    return 0;
}
