#include<iostream>
#include"httplib.h"
#include"../search/searcher.h"

using namespace std;
int main()
{
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
            
            string query = req.get_param_value("query"); //获取参数内容（即搜索词）
            string result;
            
            // 通过表单将搜索词传入query中
            // todo 
            // 
            //
            
            s.Search(query,result);
            
            //在此处进行结果界面处理
            // todo
            
            
            
            res.set_content(result,"text/plain"); //浏览器可以直接处理json格式的对象

            //cout<<req.path<<endl;
            //res.set_content("<html>hello</html>","text/html");
            });
    cout<<"Server.Get finish, Ready To Listen!"<<endl;
    server.listen("0.0.0.0",8080);
    cout<<"Listen finish!"<<endl;
    
    return 0;
}
