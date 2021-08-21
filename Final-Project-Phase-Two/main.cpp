#include "ReadFile.hpp"
#include <iostream>
#include <sstream>
using namespace std;



int main(int argc, char *argv[]){
	Application utrip;
	string line, info;
	read_hotels_file(argv[1], utrip);
	read_ratings_file(argv[2], utrip);
	bool is_user_logged_in = false;
	while (getline(cin, line)){
		vector <string> infos;
		stringstream sstream(line);
		while (sstream >> info){
			infos.push_back(info);
		}
		try{
			utrip.do_chore(infos);
		}
		catch(Permission_Error& p){
			cout << p.what();
		}
		catch(Bad_Request_Error& b){
			cout << b.what();
		}
		catch(Not_Found_Error& n){
			cout << n.what();
		}
		catch(Insufficient_Rating_Error& i){
			cout << i.what();
		}
	}
}