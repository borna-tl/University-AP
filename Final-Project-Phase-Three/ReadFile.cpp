#include "ReadFile.hpp"
using namespace std;
#include <iostream>
void read_hotels_file(string file_path, Application& utrip){
	ifstream my_file(file_path);
	string s;
	getline(my_file, s);
	while (getline(my_file, s)){
		string unique_id, property_name, hotel_star_rating, hotel_overview, property_amenities,
		city, latitude, longitude, image_url, num_standard_rooms, num_deluxe_rooms, num_luxury_rooms,
		num_premium_rooms, price_standard_room, price_deluxe_room, price_luxury_room, price_premium_room;
		istringstream is(s);
		getline(is, unique_id, SEPERATION_CHAR);
		getline(is, property_name, SEPERATION_CHAR);
		getline(is, hotel_star_rating, SEPERATION_CHAR);
		getline(is, hotel_overview, SEPERATION_CHAR);
		getline(is, property_amenities, SEPERATION_CHAR);
		getline(is, city, SEPERATION_CHAR);
		getline(is, latitude, SEPERATION_CHAR);
		getline(is, longitude, SEPERATION_CHAR);
		getline(is, image_url, SEPERATION_CHAR);
		getline(is, num_standard_rooms, SEPERATION_CHAR);
		getline(is, num_deluxe_rooms, SEPERATION_CHAR);
		getline(is, num_luxury_rooms, SEPERATION_CHAR);
		getline(is, num_premium_rooms, SEPERATION_CHAR);
		getline(is, price_standard_room, SEPERATION_CHAR);
		getline(is, price_deluxe_room, SEPERATION_CHAR);
		getline(is, price_luxury_room, SEPERATION_CHAR);
		getline(is, price_premium_room, SEPERATION_CHAR);
		Hotel(unique_id, property_name, stoi(hotel_star_rating),
			hotel_overview, property_amenities, city, make_pair(stod(latitude), stod(longitude)),
			image_url, stoi(num_standard_rooms), stoi(num_deluxe_rooms), stoi(num_luxury_rooms),
			stoi(num_premium_rooms), stoi(price_standard_room), stoi(price_deluxe_room),
			stoi(price_luxury_room), stoi(price_premium_room));
		utrip.add_hotel(unique_id, property_name, stoi(hotel_star_rating), hotel_overview,
		 	property_amenities, city, make_pair(stod(latitude), stod(longitude)), image_url,
			stoi(num_standard_rooms), stoi(num_deluxe_rooms), stoi(num_luxury_rooms),
			stoi(num_premium_rooms), stoi(price_standard_room), stoi(price_deluxe_room),
			stoi(price_luxury_room), stoi(price_premium_room));
	}
}
void read_ratings_file(string file_path, Application& utrip){
	ifstream my_file(file_path);
	string s;
	getline(my_file, s);
	while (getline(my_file, s)){
		string unique_id, rating_location, rating_cleanliness, rating_staff, rating_facilities,
		rating_value_for_money, rating_overall;
		istringstream is(s);
		getline(is, unique_id, SEPERATION_CHAR);
		getline(is, rating_location, SEPERATION_CHAR);
		getline(is, rating_cleanliness, SEPERATION_CHAR);
		getline(is, rating_staff, SEPERATION_CHAR);
		getline(is, rating_facilities, SEPERATION_CHAR);
		getline(is, rating_value_for_money, SEPERATION_CHAR);
		getline(is, rating_overall, SEPERATION_CHAR);
		utrip.add_hotel_rating(unique_id, stod(rating_location), stod(rating_cleanliness), 
		stod(rating_staff), stod(rating_facilities), stod(rating_value_for_money), stod(rating_overall));
	}
}