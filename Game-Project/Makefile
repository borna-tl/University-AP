CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: Main.o rsdl.o Application.o Path.o Tower.o Enemy.o Shot.o DefinesAndIncludes.o
	$(CC) rsdl.o Main.o Application.o Path.o Tower.o Enemy.o Shot.o DefinesAndIncludes.o $(CCFLAGS) -o FieldRunners.out

Main.o: rsdl.hpp Main.cpp Application.hpp DefinesAndIncludes.hpp
	$(CC) -c Main.cpp
Application.o: rsdl.hpp Application.cpp Path.hpp DefinesAndIncludes.hpp
	$(CC) -c Application.cpp
Path.o: rsdl.hpp Path.cpp Tower.hpp DefinesAndIncludes.hpp
	$(CC) -c Path.cpp
Tower.o: rsdl.hpp Tower.cpp Enemy.hpp DefinesAndIncludes.hpp
	$(CC) -c Tower.cpp
Enemy.o: rsdl.hpp Enemy.cpp Shot.hpp DefinesAndIncludes.hpp
	$(CC) -c Enemy.cpp
Shot.o: rsdl.hpp Shot.cpp DefinesAndIncludes.hpp
	$(CC) -c Shot.cpp
DefinesAndIncludes.o: DefinesAndIncludes.cpp
	$(CC) -c DefinesAndIncludes.cpp
rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp

clean:
	rm -r *.o
	rm FieldRunners.out