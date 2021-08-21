#ifndef RESERVATION
#define RESERVATION "RESERVATION"
#include <iostream>
#include <string>
#include <vector>
struct Reservation {
	int id;
	std::string hotel_id;
	std::string room_type;
	int quantity;
	double cost;
	int check_in;
	int check_out;
	std::vector <std::string> room_ids;
	Reservation (int id_, std::string hotel_id_, std::string room_type_, int quantity_, double cost_,
							int check_in_, int check_out_, std::vector <std::string> room_ids_);
	void print();
	bool same_id(int id_);
};















#endif