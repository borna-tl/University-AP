#ifndef FILTER
#define FILTER "FILTER"
#include "Hotel.hpp"

class Filter{
public:
	virtual bool eligible_hotel (Hotel* hotel);
	bool set_status(bool status);
	bool get_status();
protected:
	bool is_on;
};

class City_Filter : public Filter{
public:
	City_Filter();
	City_Filter (std::string city_);
	bool eligible_hotel (Hotel* hotel);
private:
	std::string city;
};
class Star_Filter : public Filter{
public:
	Star_Filter();
	Star_Filter(int min_star_, int max_star_);
	bool eligible_hotel (Hotel* hotel);
private:
	int min_star;
	int max_star;
};
class Avg_Cost_Filter : public Filter{
public:
	Avg_Cost_Filter();
	Avg_Cost_Filter(double min_cost_, double max_cost_);
	bool eligible_hotel (Hotel* hotel);
private:
	double min_cost;
	double max_cost;
};
class Room_Filter : public Filter{
public:
	Room_Filter();
	Room_Filter(std::string type_, int check_in_, int check_out_, int quantity_);
	bool eligible_hotel (Hotel* hotel);
private:
	std::string type;
	int check_in;
	int check_out;
	int quantity;
};
class Default_Price_Filter : public Filter{
public:
	Default_Price_Filter();
	Default_Price_Filter(User* user_);
	bool eligible_hotel (Hotel* hotel);
private:
	User* user;
};












#endif