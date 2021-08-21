#include "ReadFile.hpp"
#include <iostream>
#include <sstream>
#include "server/server.hpp"
#include "handlers.hpp"
#define SERVER_PORT 3000
using namespace std;

int main(int argc, char *argv[]){
	Application utrip;
	Status status;
	status.reset();
	read_hotels_file(argv[1], utrip);
	map <string, User*> sessions;
	bool is_user_logged_in = false;
	try{
		Server server(SERVER_PORT);
		server.get("/login", new ShowLoginForm(&utrip, &status, &sessions));
		server.get("/check_login", new CheckLogin(&utrip, &status, &sessions));
		server.get("/", new ShowDynamicHome(&utrip, &status, &sessions));
		server.get("/signup", new SignupForm(&utrip, &status, &sessions));
		server.get("/check_signup", new CheckSignup(&utrip, &status, &sessions));
		server.get("/home", new ShowLoggedinHome(&utrip, &status, &sessions));
		server.get("/logout", new CheckLogout(&utrip, &status, &sessions));
		server.get("/wallet", new ShowWallet(&utrip, &status, &sessions));
		server.get("/check_wallet", new CheckWallet(&utrip, &status, &sessions));
		server.get("/hotel", new ShowHotel(&utrip, &status, &sessions));
		server.run();
	}
	catch (Server::Exception e){
		cerr << e.getMessage() << endl;
	}
}