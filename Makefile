all: factory

factory: CompressorStation.o Pipe.o menu.o utils.o const.o
	g++ CompressorStation.o Pipe.o menu.o utils.o const.o -o factory

CompressorStation.o: CompressorStation.cpp
	g++ -c CompressorStation.cpp

Pipe.o: Pipe.cpp
	g++ -c Pipe.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

utils.o: utils.cpp
	g++ -c utils.cpp

const.o: const.cpp
	g++ -c const.cpp

clean:
	rm -rf *.o factory
