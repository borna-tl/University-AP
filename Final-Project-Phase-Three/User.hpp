#ifndef USER
#define USER "USER"
#include "Hash.hpp"
#include "Reservation.hpp"
#include "Weights.hpp"
#include "Rating.hpp"
#include "Errors.hpp"
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <random>
#include <cstdint>
#include <sstream>
#define EMPTY_MSG "Empty"
#define REFUND_MONEY 1/2
#define MIN_NUM_FOR_DEVIATION 10
#define MIN_NUM_OF_RATED_HOTELS_FOR_PERSONAL_RATING 5
#define EPSILON 1e-5
#define LOWER_BOUND 1
#define UPPER_BOUND 5
#define ROUNDS_COUNT 10000

struct Status{
  bool wrong_username_or_password;
  bool wrong_password_copy;
  bool used_username;
  bool has_logged_out;
  int wallet_update_status;
  bool has_signup_errors(){return (wrong_password_copy || used_username);}
  bool has_login_errors(){return (wrong_username_or_password);}
  void reset();
};
class User{
public:
	User (std::string email_, std::string username_, std::string password_);
	bool is_logged_in();
	bool same_username(std::string username_);
	bool same_email(std::string email_);
	void set_log_status (bool status);
	bool same_password(std::string password_);
	void charge_wallet(double money_);
	void show_balance_history(int count);
	bool can_afford (double money_);
	void add_reservation (std::string hotel_id_, std::string room_type_, int quantity_, double cost_,
							int check_in_, int check_out_, std::vector <std::string> room_ids_);
	void show_reserves ();
	bool has_id(int id);
	const Reservation* find_reservation_by_id(int id);
	std::string delete_reservation(int id);
	std::string get_name();
	int get_reservation_id();
	double calc_deviation();
	bool has_enough_rooms_for_default_filter ();
	static int room_cout_func(int sum, Reservation* reservation);
	int total_num_of_rooms();
	double calc_avg_res_cost();
	void update_manual_weights(bool status, double location, double cleanliness, double staff, double facilities, double value_for_money);
	void update_manual_weights_status(bool status);
	void show_manual_weights();
	bool get_manual_weights_status();
	Weights* get_manual_weights();
	bool has_rated_enough_hotels();
	void add_rating(std::string hotel_id_, double location_, double cleanliness_, double staff_,
				double facilities_, double value_, double overall_);
	Weights* get_estimated_weights();
	bool has_user_used_personal_sort();
	void update_has_used_personal_sort_status(bool status);
	void show_estimated_weights();
	std::string show_wallet_html(int update_status);
private:
	std::string email;
	std::string username;
	size_t password;
	int reservation_id;
	double money;
	std::vector <double> balance;
	bool logged_in;
	std::vector <Reservation*> reservations;
	struct Weights* manual_weights;
	struct Weights* estimated_weights;
	std::vector <Rating> ratings;
	double overall_satisfaction_estimation(struct Rating* rating, struct Weights* weights);
	double error_estimation(struct Rating* rating, struct Weights* weights);
	double gradient(struct Rating* rating, struct Weights* weights, int i);
	void update_weights(std::vector <Rating>& ratings, struct Weights* weights);
	double fix_range(double d);
	bool has_used_personal_sort;
};

#endif