#ifndef APPLICATION
#define APPLICATION "APPLICATION"
#include "User.hpp"
#include "Filter.hpp"
#include "Errors.hpp"
#define GET_COMMAND "GET"
#define POST_COMMAND "POST"
#define DELETE_COMMAND "DELETE"
#define OK_COMMAND "OK"
#define HOTEL_KEYWORD "hotel"
#define LOCATION_KEYWORD "location"
#define CLEANLINESS_KEYWORD "cleanliness"
#define STAFF_KEYWORD "staff"
#define FACILITIES_KEYWORD "facilities"
#define VALUE_FOR_MONEY_KEYWORD "value_for_money"
#define OVERALL_RATING_KEYWORD "overall_rating"
#define EMAIL_KEYWORD "email"
#define USERNAME_KEYWORD "username"
#define PASSWORD_KEYWORD "password"
#define TYPE_KEYWORD "type"
#define MAX_PRICE_KEYWORD "max_price"
#define MIN_PRICE_KETWORD "min_price"
#define MAX_STAR_KEYWORD "max_star"
#define MIN_STAR_KEYWORD "min_star"
#define QUANTITY_KEYWORD "quantity"
#define CHECK_IN_KEYWORD "check_in"
#define CHECK_OUT_KEYWORD "check_out"
#define CITY_FILTER_TYPE "city"
#define ROOM_FILTER_TYPE "room"
#define COST_FILTER_TYPE "cost"
#define STAR_FILTER_TYPE "star"
#define LOGIN_TASK "login"
#define LOGOUT_TASK "logout"
#define SIGNUP_TASK "signup"
#define WALLET_TASK "wallet"
#define AMOUNT_KEYWORD "amount"
#define COUNT_KEYWORD "count"
#define HOTELS_TASK "hotels"
#define ID_KEYWORD "id"
#define FILTERS_TASK "filters"
#define RESERVES_TASK "reserves"
#define COMMENTS_TASK "comments"
#define RATINGS_TASK "ratings"
#define COMMENT_KEYWORD "comment"
#define MIN_STAR 1
#define MAX_STAR 5
#define MIN_RATING 1
#define MAX_RATING 5
#define MIN_INFO_SIZE 2
#define SIGNUP_SIZE 9
#define LOGIN_SIZE 7
#define LOGOUT_SIZE 2
#define WALLET_SIZE 5
#define HOTELS_SIZE 2
#define HOTELS_ID_SIZE 5
#define STAR_FILTER_SIZE 7
#define ROOM_FILTER_SIZE 11
#define COST_FILTER_SIZE 7
#define RESERVE_SIZE 13
#define SHOW_RESERVES_SIZE 2
#define DELETE_RESERVES_SIZE 5
#define COMMENT_SIZE 7
#define SHOW_COMMENT_SIZE 5
#define RATE_SIZE 17
#define SHOW_RATE_SIZE 5

#define DELETE_FILTER_SIZE 2
class Application{
public:
	Application ();
	~Application();
	void do_chore(std::vector <std::string> infos);
	void add_hotel(std::string unique_id, std::string property_name, int hotel_star_rating,
			std::string hotel_overview, std::string property_amenities, std::string city,
			std::pair<double, double> geo_place, std::string image_url, int num_standard_rooms,
			int num_deluxe_rooms, int num_luxury_rooms,	int num_premium_rooms,
			int price_standard_room, int price_deluxe_room,	int price_luxury_room,
			int price_premium_room);
private:
	bool have_logged_in_user;
	User* current_user;
	std::vector <User*> customers;
	std::vector <Hotel*> hotels;
	City_Filter city_filter;
	Star_Filter star_filter;
	Avg_Cost_Filter avg_cost_filter;
	Room_Filter room_filter;
	bool is_unique(std::string type, std::string data);
	User* find_user_by_email(std::string email);
	bool sorted_hotels(Hotel* a, Hotel* b);
	void sort_hotels();
	void reset_filters();
	bool has_hotel (std::string id);
	Hotel* find_hotel_by_id (std::string id);
};

#endif