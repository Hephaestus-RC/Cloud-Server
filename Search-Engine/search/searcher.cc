#include"searcher.h"
#include<iostream>
#include<fstream>
#include<jsoncpp/json/json.h>
#include"../common/Util.hpp"
#include<boost/filesystem.hpp>

namespace searcher
{
    
///////////////////////////////////////////////////////////////////////////
//索引模块
/////////////////////////////////////////////////////////////////////////////
    const char* const DICT_PATH = "../jieba_dict/jieba.dict.utf8";
    const char* const HMM_PATH = "../jieba_dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "../jieba_dict/user.dict.utf8";
    const char* const IDF_PATH = "../jieba_dict/idf.utf8";
    const char* const STOP_WORD_PATH = "../jieba_dict/stop_words.utf8";

    Index::Index():_jieba(
            DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH)
    {}

    //正排查找
    const DocInfo* Index::GetDocInfo(const uint64_t id) const
    {
        if(id >= forward_index_.size())
            return NULL;
        return &forward_index_[id];
    }
    //倒排查找
    const InvertedList* Index::GetInvertedList(const string& key) const
    {
        auto pos = inverted_index_.find(key);
        if(pos == inverted_index_.end())
            return NULL;
        return &pos->second;
    }
    //构建正排/倒排索引
    bool Index::Build(const string& input_path)
    {
        //1. 按行读取文件内容(一行就是一个html文件) 
        //2. 构造Doinfo结构体，将其更新到正排索引中
        //3. 更新倒排索引
        cout<<"Start Build"<<endl;
        std::ifstream file(input_path.c_str());
        if(!file.is_open())
        {
            cout<<"[Input_path Open Failed!] input_path="<<input_path<<endl;
            return false;
        }
        string line;
        while(getline(file,line))
        {
            const DocInfo* doc = BuildForward(line);
            BuildInverted(*doc);
        }
        cout<<"Build End"<<endl;
        file.close();
        return true;
    }
    const DocInfo* Index::BuildForward(const string& line)
    {
        //1.切分
        vector<string> tokens;
        StringUtil::Split(line,tokens,"\3");
        if(tokens.size()!=3)
        {
            cout<<"[Tokens Error!]"<<endl;
            return NULL;
        }
        //2.构建DocInfo对象
        DocInfo doc;
        doc.doc_id = forward_index_.size();
        doc.title = tokens[0];
        doc.url = tokens[1];
        doc.content = tokens[2];
        //3. 插入正排序列
        forward_index_.push_back(doc);
        return &forward_index_.back();
    }
    void Index::BuildInverted(const DocInfo& doc)
    {
        //1. 对当前的doc进行分词（标题和正文，使用结巴分词）
        vector<string> title_tokens;
        vector<string> content_tokens;
        CutWord(doc.title, title_tokens);
        CutWord(doc.content,content_tokens);
        //2. 对doc中的标题和正文进行词频统计
        struct WordCnt
        {
            int title_cnt;
            int content_cnt;
        };
        unordered_map<string,WordCnt> wdct; //用来保存该html文档中的所有分词此结果
        for(string it : title_tokens)
        {
            boost::to_lower(it);    //统计词频时忽略大小写
            (wdct[it].title_cnt)++;
        }
        for(string it : content_tokens)
        {
            boost::to_lower(it);
            (wdct[it].content_cnt)++;
        }
        //3. 将分词结果更新进倒排序列中
        for(const pair<string,WordCnt>& word_pair : wdct)
        {
            Weight weth;
            weth.doc_id = doc.doc_id;
            weth.weight = 10*word_pair.second.title_cnt + word_pair.second.content_cnt;
            weth.key = word_pair.first;
            InvertedList& inveList = inverted_index_[word_pair.first];
            inveList.push_back(weth);
        }
    }
    void Index::CutWord(const string& input,vector<string>& output) //进行分词
    { 
        _jieba.CutForSearch(input,output);
    }



    ///////////////////////////////////////////////////////////////////////////
    //搜索模块
    /////////////////////////////////////////////////////////////////////////////
    
    bool Searcher::Init(const string& input_path)
    {
        return _index->Build(input_path);
    }
    bool Searcher::Search(const string& query,string& json_result)
    {
        //1. 分词--对查询词进行分词
        //2. 触发--针对分词结果查倒排索引，找到有相关性的
        //3. 排序--把这些结果按照一定的规则排序
        //4. 构造结果--查正排，找到每股搜索结果的标题，正文，url
        
        vector<string> tokens; //保存查询词的分词结果
        _index->CutWord(query,tokens);

        vector<Weight> all_token_result;
        for(auto word : tokens)
        {
            boost::to_lower(word);
            auto* inverted_list = _index->GetInvertedList(word);
            if(inverted_list == nullptr)
                continue;
            //去重，同时增加权重
            all_token_result.insert(all_token_result.end(),inverted_list->begin(),inverted_list->end());
        }

        
        sort(all_token_result.begin()
            ,all_token_result.end()
            ,[](const Weight& w1,const Weight& w2)
                {return w1.weight > w2.weight;}); //sort的第三个参数(仿函数/函数指针/lambda表达式)

        Json::Value results;
        // 借助jsoncpp库完成对返回结果的序列化
        // json结构：
        // [
        //     {
        //         "title":"标题",
        //         "Desc":"描述",
        //         "url":"url",
        //     },
        //     {
        //
        //     }
        // ]
        for(const auto& weight : all_token_result)
        {
            const auto* doc = _index->GetDocInfo(weight.doc_id); 
            if(doc == nullptr)
                continue;
            Json::Value result;
            result["title"] = doc->title;
            result["url"] = doc->url;
            result["Desc"] = GetDesc(doc->content,weight.key);
            results.append(result);
        }
        Json::FastWriter w;
        json_result = w.write(results);

        return true;
    }
    string Searcher::GetDesc(const string& content,const string& key)
    {
        string ret ;
        size_t pos = content.find(key);
        if(pos == string::npos)
        {
            if(content.size()>150)
                ret = content.substr(0,150)+"...";
            else 
                ret = content; 
        }
        else 
        {
            size_t beg = pos>50 ? pos-50 : 0;
            if(beg+150 >= content.size())
                ret = content.substr(beg);
            else 
                ret = content.substr(beg,150)+"...";
        }
        return ret;
    }
}
