#include"protocol.hpp"

int main()
{
	//sock
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		cerr<<"sock error"<<endl;
		exit(1);
	}
	cout<<"sock success!"<<endl;

	//connnect
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(8888);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) < 0)
	{
		cerr<<"connect error"<<endl;
		exit(2);
	};
	request rp;
	response rsp;
	for(;;)
	{
		cout<<"Enter The Operater# ";
		cin>>rp.op;
		cout<<"Enter Two Number# ";
		cin>>rp.x>>rp.y;

		send(sock,(void*)&rp,sizeof(rp),0);
		recv(sock,(void*)&rsp,sizeof(rsp),0);

		cout<<"status: "<<rsp.status<<endl;
		cout<<"result: "<<rsp.result<<endl;
	}
}
