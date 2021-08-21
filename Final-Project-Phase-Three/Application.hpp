#ifndef APPLICATION
#define APPLICATION "APPLICATION"
#include "User.hpp"
#include "Filter.hpp"
#include "Errors.hpp"
#include <algorithm>
#include <sstream>
#define GET_COMMAND "GET"
#define POST_COMMAND "POST"
#define DELETE_COMMAND "DELETE"
#define OK_COMMAND "OK"
#define INSUFFICIENT_RATING_MSG "Insufficient Ratings"
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
#define PASSWORD_COPY_KEYWORD "passwordcopy"
#define TYPE_KEYWORD "type"
#define MAX_PRICE_KEYWORD "max_price"
#define MIN_PRICE_KETWORD "min_price"
#define MAX_STAR_KEYWORD "max_star"
#define MIN_STAR_KEYWORD "min_star"
#define QUANTITY_KEYWORD "quantity"
#define CHECK_IN_KEYWORD "check_in"
#define CHECK_OUT_KEYWORD "check_out"
#define ACTIVE_KEYWORD "active"
#define TRUE_KEYWORD "true"
#define FALSE_KEYWORD "false"
#define NAME_KEYWORD "name"
#define STAR_RATING_KEYWORD "star_rating"
#define CITY_KEYWORD "city"
#define STANDARD_ROOM_PRICE_KEYWORD "standard_room_price"
#define DELUXE_ROOM_PRICE_KEYWORD "deluxe_room_price"
#define LUXURY_ROOM_PRICE_KEYWORD "luxury_room_price"
#define PREMIUM_ROOM_PRICE_KEYWORD "premium_room_price"
#define AVERAGE_ROOM_PRICE_KEYWORD "average_room_price"
#define RATING_OVERALL_KEYWORD "rating_overall"
#define RATING_PERSONAL_KEYWORD "rating_personal"
#define ASCENDING_KEYWORD "ascending"
#define DESCENDING_KEYWORD "descending"
#define CITY_FILTER_TYPE "city"
#define ROOM_FILTER_TYPE "room"
#define COST_FILTER_TYPE "cost"
#define STAR_FILTER_TYPE "star"
#define DEFAULT_FILTER_TYPE "default"
#define LOGIN_TASK "login"
#define LOGOUT_TASK "logout"
#define SIGNUP_TASK "signup"
#define WALLET_TASK "wallet"
#define AMOUNT_KEYWORD "amount"
#define COUNT_KEYWORD "count"
#define HOTELS_TASK "hotels"
#define SORT_TASK "sort"
#define ID_KEYWORD "id"
#define FILTERS_TASK "filters"
#define RESERVES_TASK "reserves"
#define COMMENTS_TASK "comments"
#define RATINGS_TASK "ratings"
#define DEFAULT_PRICE_FILTER_TASK "default_price_filter"
#define MANUAL_WEIGHTS_TASK "manual_weights"
#define ESTIMATED_WEIGHTS_TASK "estimated_weights"
#define COMMENT_KEYWORD "comment"
#define PROPERTY_KEYWORD "property"
#define ORDER_KEYWORD "order"
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
#define DEFAULT_FILTER_SIZE 5
#define RESERVE_SIZE 13
#define SHOW_RESERVES_SIZE 2
#define DELETE_RESERVES_SIZE 5
#define COMMENT_SIZE 7
#define SHOW_COMMENT_SIZE 5
#define RATE_SIZE 17
#define SHOW_RATE_SIZE 5
#define DELETE_FILTER_SIZE 2
#define MANUAL_WEIGHTS_FALSE_ACTIVATION_SIZE 5
#define MANUAL_WEIGHTS_TRUE_ACTIVATION_SIZE 15
#define ESTIMATED_WEIGHTS_SIZE 2
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
	void add_hotel_rating(std::string unique_id, double rating_location, double rating_cleanliness,
			double rating_staff, double rating_facilities,
			double rating_value_for_money, double rating_overall);
	bool can_signup_user(std::string username);
	User* signup_user(std::string username, std::string password, std::string email);
	bool has_logged_in_user(){return have_logged_in_user;}
	std::vector <Hotel*> get_hotels() {return hotels;}
	//injaha hpp dorost she
	std::string get_hotels_list_html(int min_star, int max_star);
	void logout_user();
	void login_user(std::string username);
	Hotel* find_hotel_by_id (std::string id);
	
private:
	bool have_logged_in_user;
	bool custom_sort_filter_on;
	User* current_user;
	std::vector <User*> customers;
	std::vector <Hotel*> hotels;
	City_Filter city_filter;
	Star_Filter star_filter;
	Avg_Cost_Filter avg_cost_filter;
	Room_Filter room_filter;
	Default_Price_Filter* default_filter;
	bool is_unique(std::string type, std::string data);
	User* find_user_by_email(std::string email);
	User* find_user_by_username(std::string username);
	bool sorted_hotels(Hotel* a, Hotel* b);
	void sort_hotels();
	void reset_filters();
	bool has_hotel (std::string id);
};

#endif