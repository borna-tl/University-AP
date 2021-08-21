CC := g++ -std=c++11
all: utrip.out
utrip.out: main.o Handlers.o ReadFile.o Application.o Filter.o Hotel.o Rating.o Room.o User.o Reservation.o Hash.o Errors.o Weights.o Response.o Request.o Utilities.o Server.o Route.o Template_parser.o
	$(CC) main.o Handlers.o ReadFile.o Application.o Filter.o Hotel.o Rating.o Room.o User.o Reservation.o Hash.o Errors.o Weights.o Response.o Request.o Utilities.o Server.o Route.o Template_parser.o -o utrip.out
main.o: main.cpp ReadFile.hpp server/server.hpp
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

Template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp -o Template_parser.o
Response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o Response.o
Request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o Request.o
Utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o Utilities.o
Server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) -c server/server.cpp -o Server.o
Route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o Route.o
Handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c handlers.cpp -o Handlers.o
clean:
	rm -r *.o
	rm utrip.out