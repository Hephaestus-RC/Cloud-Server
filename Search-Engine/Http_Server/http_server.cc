#include<iostream>
#include"httplib.h"
#include"../search/searcher.h"

using namespace std;
int main()
{
    searcher::Searcher s;
    if(!s.Init("../data/tmp/raw_input"))
    {
        cout<<"Searcher Init Error!"<<endl;
        return 1;
    }

    using namespace httplib;
    Server server;
    server.Get("/search",[&s](const Request& req,Response& res) { 
            string query = req.get_param_value("query");
            string result;
            s.Search(query,result);
            res.set_content(result,"text/plain");
            //cout<<req.path<<endl;
            //res.set_content("<html>hello</html>","text/html");
            });
    server.listen("0.0.0.0",8080);
    
    return 0;
}
