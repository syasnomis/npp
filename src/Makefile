all: npp

npp: main.o cpu.o nes.o rom.o
	g++ -g -o npp main.o cpu.o nes.o rom.o

main.o: main.cpp nes.h
	g++ -c --std=c++11 main.cpp

cpu.o: cpu.cpp cpu.h
	g++ -g -c --std=c++11 cpu.cpp

nes.o: nes.cpp nes.h
	g++ -g -c --std=c++11 nes.cpp

rom.o: rom.cpp rom.h
	g++ -g -c --std=c++11 rom.cpp

clean:
	rm -rf *o npp
