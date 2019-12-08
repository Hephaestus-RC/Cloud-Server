FLAG=-std=c++11 -lpthread -I ~/Project/cppjieba/include 

http_server:http_server.cc ../search/libSearcher.so 
	g++ -o $@ $^  $(FLAG)

.PHONY:clean
clean:
	rm -f http_server
