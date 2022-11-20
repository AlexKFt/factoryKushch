all: factory

factory: CompressorStation.o Pipe.o menu.o utils.o Network.o Link.o
	g++ Link.o Network.o CompressorStation.o Pipe.o menu.o utils.o -o factory

Network.o: Network.cpp
	g++ -c Network.cpp

Link.o: Link.cpp
	g++ -c Link.cpp

CompressorStation.o: CompressorStation.cpp
	g++ -c CompressorStation.cpp

Pipe.o: Pipe.cpp
	g++ -c Pipe.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

utils.o: utils.cpp
	g++ -c utils.cpp

clean:
	rm -rf *.o factory
