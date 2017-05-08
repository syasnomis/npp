all: npp

npp: main.o cpu.o
	g++ -o npp main.o cpu.o

main.o: main.cpp cpu.h
	g++ -c --std=c++11 main.cpp

cpu.o: cpu.cpp cpu.h
	g++ -c --std=c++11 cpu.cpp

clean:
	rm -rf *o npp
