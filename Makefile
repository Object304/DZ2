all : main.o hw2.o
	g++ main.o hw2.o

main.o : main.cpp
	g++ -c main.cpp

hw2.o : hw2.cpp
	g++ -c hw2.cpp

clean :
	rm -rf *.o a.out