P1.exe : Project1.o execute.o check
	g++ -o P1.exe Project1.o execute.o

check : check.cpp execute.h execute.o
	g++ -g -o check check.cpp execute.o

execute.o : execute.cpp execute.h
	g++ -g -c execute.cpp

Project1.o : Project1.cpp execute.h
	g++ -g -c Project1.cpp 

clean : 
	rm -rf *.o check P1.exe 
