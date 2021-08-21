CC := g++ -std=c++11
all: utrip.out
utrip.out: main.o ReadFile.o Application.o Filter.o Hotel.o Rating.o Room.o User.o Reservation.o Hash.o Errors.o Weights.o
	$(CC) main.o ReadFile.o Application.o Filter.o Hotel.o Rating.o Room.o User.o Reservation.o Hash.o Errors.o Weights.o -o utrip.out
main.o: main.cpp ReadFile.hpp
	$(CC) -c main.cpp -o main.o
ReadFile.o: ReadFile.cpp ReadFile.hpp Application.hpp
	$(CC) -c ReadFile.cpp -o ReadFile.o
Application.o: Application.cpp Application.hpp User.hpp Filter.hpp Errors.hpp
	$(CC) -c Application.cpp -o Application.o
Filter.o: Filter.cpp Filter.hpp Hotel.hpp
	$(CC) -c Filter.cpp -o Filter.o
Hotel.o: Hotel.cpp Hotel.hpp User.hpp Room.hpp Rating.hpp
	$(CC) -c Hotel.cpp -o Hotel.o
Rating.o: Rating.cpp Rating.hpp 
	$(CC) -c Rating.cpp -o Rating.o
Room.o : Room.cpp Room.hpp 
	$(CC) -c Room.cpp -o Room.o
User.o: User.cpp User.hpp Hash.hpp Reservation.hpp Weights.hpp
	$(CC) -c User.cpp -o User.o
Reservation.o: Reservation.cpp Reservation.hpp
	$(CC) -c Reservation.cpp -o Reservation.o
Hash.o: Hash.cpp Hash.hpp
	$(CC) -c Hash.cpp -o Hash.o
Errors.o: Errors.hpp Errors.cpp
	$(CC) -c Errors.cpp -o Errors.o
Weights.o: Weights.cpp Weights.hpp Hash.hpp
	$(CC) -c Weights.cpp -o Weights.o

clean:
	rm -r *.o
	rm utrip.out