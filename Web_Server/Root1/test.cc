#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
using namespace std;

int main()
{
    struct stat st;
    int ret = stat("./index.html",&st);
    cout<<st.st_size<<endl;
    return 0;

}
