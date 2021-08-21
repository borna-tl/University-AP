#ifndef USER
#define USER "USER"
#include "Hash.hpp"
#include "Reservation.hpp"
#define EMPTY_MSG "Empty"
#define REFUND_MONEY 1/2
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
private:
	std::string email;
	std::string username;
	size_t password;
	int reservation_id;
	double money;
	std::vector <double> balance;
	bool logged_in;
	std::vector <Reservation*> reservations;
};

#endif