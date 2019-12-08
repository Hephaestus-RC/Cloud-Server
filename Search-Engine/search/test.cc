#include"searcher.h"
using namespace std;

#if 0
int main()
{
    //检验索引模块
    searcher::Index index;
    bool ret = index.Build("../data/tmp/raw_input");
    if(!ret)
    {
        cout<<"[Build failed!]"<<endl;
        return 1;
    }
    auto* inverted_list = index.GetInvertedList("filesystem");
    if(inverted_list==NULL)
    {
        cout<<"[GetInvertedList Error!]"<<endl;
        return 1;
    }
    int i = 1;
    for(auto weight : *inverted_list)
    {
        cout<<i++<<endl;
        cout<<"ID: "<<weight.doc_id<<" Weigth:"<<weight.weight<<endl;
        const auto* doc_info = index.GetDocInfo(weight.doc_id);
        cout<<"title: "<<doc_info->title<<endl;
        cout<<"url: "<<doc_info->url<<endl;
        //cout<<"Content: "<<doc_info->content<<endl;
    }

    return 0;
}
#endif

int main()
{
    searcher::Searcher searcher;
    if(!searcher.Init("../data/tmp/raw_input"))
        return 1;
    string query = "filesystem"; //检索词：filesystem 
    string result ;
    searcher.Search(query,result);

    cout<<"Result: "<<result<<endl;
    return 0;

}
