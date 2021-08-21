CC=g++ -std=c++11

all: Goodreads.out

Goodreads.out: main.o ReadnPrint.o Author.o Book.o Review.o User.o GoodReads.o
	${CC} -o Goodreads.out main.o ReadnPrint.o Author.o Book.o Review.o User.o GoodReads.o

main.o: main.cpp GoodReads.hpp ReadnPrint.hpp
	${CC} -c main.cpp -o main.o

ReadnPrint.o: ReadnPrint.cpp ReadnPrint.hpp GoodReads.hpp
	${CC} -c ReadnPrint.cpp -o ReadnPrint.o

Author.o : Author.cpp Author.hpp Book.hpp
	${CC} -c Author.cpp -o Author.o

Book.o: Book.cpp Book.hpp
	${CC} -c Book.cpp -o Book.o

Review.o: Review.cpp Review.hpp
	${CC} -c Review.cpp -o Review.o

User.o: User.cpp User.hpp Author.hpp
	${CC} -c User.cpp -o User.o

GoodReads.o: GoodReads.cpp GoodReads.hpp Review.hpp Author.hpp User.hpp
	${CC} -c GoodReads.cpp -o GoodReads.o


clean:
	rm *.o
	rm Goodreads.out