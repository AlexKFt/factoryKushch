all: factory

factory: CompressorStation.o Pipe.o menu.o utilites.o
	g++ CompressorStation.o Pipe.o menu.o utilites.o -o factory

CompressorStation.o: CompressorStation.cpp
	g++ -c CompressorStation.cpp

Pipe.o: Pipe.cpp
	g++ -c Pipe.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

utilites.o: utilites.cpp
	g++ -c utilites.cpp

clean:
	rm -rf *.o factory
