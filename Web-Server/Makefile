.PHONY:all
all:cgi http 

cgi:TestCgi.cc 
	g++ -o $@ $^ -std=c++11
http:HttpServer.cc
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -rf http cgi
