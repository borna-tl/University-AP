#ifndef HOTEL
#define HOTEL "HOTEL"
#include "User.hpp"
#include "Room.hpp"
#include "Rating.hpp"
#include <iomanip>
#define NOT_ENOUGH_ROOM_MSG "Not Enough Room"
#define NOT_ENOUGH_CREDIT_MSG "Not Enough Credit"
#define PRECISION 2
class Hotel{
public:
	Hotel();
	Hotel (std::string unique_id_, std::string property_name_, int hotel_star_rating_, std::string hotel_overview_,
		std::string property_amenities_, std::string city_, std::pair <double, double> geo_place_, std::string image_url_,
		int num_standard_rooms_,int num_deluxe_rooms_, int num_luxury_rooms_, int num_premium_rooms_,
		int price_standard_rooms_, int price_deluxe_rooms_, int price_luxury_rooms_, int price_premium_rooms_);
	void reserve (User* customer, std::string room_type, int quantity, int check_in, int check_out);
	bool can_reserve (User* customer, std::string room_type, int quantity, int check_in, int check_out);
	std::string get_id ();
	bool same_city (std::string city_);
	bool sufficient_star (int min_star, int max_star);
	bool adequate_cost (double min_cost, double max_cost);
	bool has_enough_rooms (std::string type, int check_in, int check_out, int quantity);
	void list_hotel ();
	void show_hotel();
	void free_rooms (int reservation_id_);
	void add_comment(std::string user, std::string comment);
	void show_comments();
	void add_rating (double location, double cleanliness, double staff, double facilities, double value, double overall, std::string username);
	void show_ratings();
private:
	std::string unique_id;
	std::string property_name;
	int hotel_star_rating;
	std::string hotel_overview;
	std::string property_amenities;
	std::string city;
	std::pair <double, double> geo_place;
	std::vector <std::pair<std::string, std::string>> comments;
	std::string image_url;
	std::vector <Room*> rooms;
	int total_num_of_rooms;
	double avg_price;
	struct Num_Room_Types room_numbers;
	struct Price_Room_Types room_prices;
	Rating* ratings;
	std::vector <std::string> voted_users_id;
	void add_room(int number, char type);
	int find_room_type_cost (std::string room_type);
	std::vector <std::string> reserve_rooms(int reservation_id, int quantity, std::string type, int check_in, int check_out);
};




#endif