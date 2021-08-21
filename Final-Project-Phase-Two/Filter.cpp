#include "Filter.hpp"
using namespace std;

bool Filter::eligible_hotel (Hotel* hotel){};
bool  Filter::set_status(bool status){
    is_on = status;
}
bool Filter::get_status(){return is_on;}

City_Filter::City_Filter(){}
City_Filter::City_Filter (string city_){
    is_on = false;
    city = city_;
}
bool City_Filter::eligible_hotel (Hotel* hotel){
    return (!is_on || hotel->same_city(city));
}

Star_Filter::Star_Filter(){}
Star_Filter::Star_Filter(int min_star_, int max_star_){
    is_on = false;
    min_star = min_star_;
    max_star = max_star_;
}
bool Star_Filter::eligible_hotel (Hotel* hotel){
    return (!is_on || hotel->sufficient_star(min_star, max_star));
}

Avg_Cost_Filter::Avg_Cost_Filter(){}
Avg_Cost_Filter::Avg_Cost_Filter(double min_cost_, double max_cost_){
    is_on = false;
    min_cost = min_cost_;
    max_cost = max_cost_;
}
bool Avg_Cost_Filter::eligible_hotel (Hotel* hotel){
    return (!is_on || hotel->adequate_cost(min_cost, max_cost));
}

Room_Filter::Room_Filter(){}
Room_Filter::Room_Filter(string type_, int check_in_, int check_out_, int quantity_){
    is_on = false;
    type = type_; 
    check_in = check_in_;
    check_out = check_out_;
    quantity = quantity_;
}
bool Room_Filter::eligible_hotel (Hotel* hotel){
    return (!is_on || hotel->has_enough_rooms(type, check_in, check_out, quantity));
}
Default_Price_Filter::Default_Price_Filter(){}
Default_Price_Filter::Default_Price_Filter(User* user_){
	is_on = false;
	user = user_;
}
bool Default_Price_Filter::eligible_hotel(Hotel* hotel){
    if (is_on && !user->has_enough_rooms_for_default_filter())
        return false;
    return (!is_on || (hotel->in_default_range(user)));
}