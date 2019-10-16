.PHONY:all
all: size date test


#student:student.cc
#	g++ -std=c++11 -o  $@ $^

size:class_size.cc
	g++ -std=c++11 -o $@ $^
date:Date.cc
	g++ -std=c++11 -o $@ $^
test:test.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f size date test
