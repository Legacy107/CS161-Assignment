.PHONY: all clean

CXX = g++ -std=c++14 -Wall -Wextra -w -O2
lib = board.o input.o

# Build entire program
all: main

main: main.o  ${lib}
	${CXX} -o main ${lib} main.o

board.o: .\src\board.cpp .\header\board.h
	${CXX} -c .\src\board.cpp

input.o: .\src\input.cpp .\header\input.h
	${CXX} -c .\src\input.cpp

main.o: main.cpp
	${CXX} -c main.cpp

# Build driver program for testing
driver: driver.o  ${lib}
	${CXX} -o driver ${lib} driver.o

driver.o: driver.cpp
	${CXX} -c driver.cpp

clean:
	rm *.o main.exe driver.exe