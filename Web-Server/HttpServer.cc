#include"HttpServer.hpp"

void Usage(string proc)
{
	cout<<"Usage: "<<proc<<" PORT "<<endl;
}
int _main(int args,char* argv[])
{
	if(args!=2)
	{
		Usage(argv[0]);
		exit(1);
	}
	HttpServer* hs = new HttpServer(atoi(argv[1]));
	hs->InitHttpServer();
	hs->Start();

    delete hs;
    return 0;
}

int main(int args,char* argv[])
{
    //设置为守护进程
    pid_t pc = fork();
    if(pc < 0)
    {
        perror("fork error!");
        exit(1);
    }
    if(pc > 0)
        exit(0);
    
    umask(0);
    setsid();
    chdir("/home/rencheng/Project/Web-Server");
    size_t fd = open("./log.txt",O_RDONLY);
    dup2(1,fd);
    for(size_t i = 3;i < 65535;++i)
    {
        if(i == fd)
            continue;
        close(i);
    }
	return _main(args,argv);
}
