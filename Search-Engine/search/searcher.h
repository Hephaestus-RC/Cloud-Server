//该文件包含索引模块和搜索模块

#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include"../../cppjieba/include/cppjieba/Jieba.hpp"
//#include"cppjieba/Jieba.hpp"

namespace searcher
{
    using namespace std;
    
    struct DocInfo
    {
        uint64_t doc_id;
        string title;
        string url;
        string content;
    };

    struct Weight //倒排项
    {
        uint64_t doc_id;
        int weight; //权重（为排序做准备，权重值用词频计算出）
        string key; 
    };

    typedef vector<Weight> InvertedList; //倒排列表,用来记载出现该词的所有文档以及权重；
    
    //索引模块
    class Index
    {
        private:
            //正排索引(下标:文档id  元素:文档内容)
            vector<DocInfo> forward_index_;
            //倒排索引(key:文档内容  value:文档id)
            unordered_map<string,InvertedList> inverted_index_;
            cppjieba::Jieba _jieba;
        private:
            const DocInfo* BuildForward(const string& line);
            void BuildInverted(const DocInfo& doc);
        public:
            Index();
            bool Build(const string& input_file); //读取raw_output文件，构建正排/倒排索引
            const DocInfo* GetDocInfo(const uint64_t id) const; //正排查找
            const InvertedList* GetInvertedList(const string& key) const; //倒排查找
            void CutWord(const string& input,vector<string>& output); //进行分词
    };
    
    //搜索模块
    class Searcher
    {
        private:
            Index* _index;
        private:
            string GetDesc(const string& content,const string& key);
        public:
            Searcher():_index(new Index())
            {}
            ~Searcher()
            {
                delete _index;
            }
            //加载索引
            bool Init(const string& input_path);
            //通过特定的格式将搜索结果写入result字符串中
            bool Search(const string& query,string& result);
    };

}
