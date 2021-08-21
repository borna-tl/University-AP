#include "Application.hpp"
using namespace std;



Application::Application (){
    have_logged_in_user = false;
    custom_sort_filter_on = false;
}
Application::~Application(){
    for (auto x : customers)
        delete x;
    for (auto x : hotels)
        delete x;
}
void Application::do_chore(vector <string> infos){
    if (infos.size() < MIN_INFO_SIZE || (infos[0] != GET_COMMAND && infos[0] != POST_COMMAND && infos[0] != DELETE_COMMAND)){
        throw Bad_Request_Error();
    }
    string task_type = infos[0];
    string task = infos[1];
    if (task == DEFAULT_PRICE_FILTER_TASK)
        task = FILTERS_TASK;
    if (have_logged_in_user){
        if (task == LOGIN_TASK || task == SIGNUP_TASK){
            throw Bad_Request_Error();
        }
        if (task == WALLET_TASK){
            if (infos.size() != WALLET_SIZE){
                throw Bad_Request_Error();
            }
            if (task_type == POST_COMMAND){
                double amount = 0;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == AMOUNT_KEYWORD){
                        amount = stod(infos[++i]);
                    }
                }
                if (amount <= 0){
                        throw Bad_Request_Error();
                }
                else{
                    current_user->charge_wallet(amount);
                    cout << OK_COMMAND << endl;
                }
            }
            else if (task_type == GET_COMMAND){
                int count = 0;
                for (int i = 3; i < infos.size(); i ++){
                    if (infos[i] == COUNT_KEYWORD){
                        count = stoi(infos[++i]);
                    }
                }
                if (count <= 0){
                        throw Bad_Request_Error();
                }
                else{
                    current_user->show_balance_history(count);
                }
            }		
        }
        else if (task == LOGOUT_TASK){
            if (infos.size() != LOGOUT_SIZE || task_type != POST_COMMAND){
                throw Bad_Request_Error();
            }
            current_user->set_log_status(false);
            have_logged_in_user = false;
            reset_filters();
            cout << OK_COMMAND << endl;
        }
        else if (task == HOTELS_TASK){
            if(infos.size() == HOTELS_ID_SIZE && task_type == GET_COMMAND){
                string id;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == ID_KEYWORD){
                        id = infos[++i];	
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                if (!has_hotel(id)){
                    throw Not_Found_Error();
                }
                find_hotel_by_id(id)->show_hotel();
            }
            else if (infos.size() == HOTELS_SIZE && task_type == GET_COMMAND){
                if (default_filter->get_status()){
                    cout << "* Results have been filtered by the default price filter." << endl;
                }
                if (!current_user->has_rated_enough_hotels() && !current_user->get_manual_weights_status() && current_user->has_user_used_personal_sort()){
                    throw Insufficient_Rating_Error();
                }
                bool has_eligible_hotel = false;
                for (auto x : hotels){
                    if ((default_filter->eligible_hotel(x) && (city_filter.eligible_hotel(x)
                        && room_filter.eligible_hotel(x) && avg_cost_filter.eligible_hotel(x)
                        && star_filter.eligible_hotel(x)))){
                        x->list_hotel();
                        has_eligible_hotel = true;
                    }
                }
                if (!has_eligible_hotel){
                    cout << EMPTY_MSG << endl;
                    return;
                }
            }
            else{
                throw Bad_Request_Error();
            }
        }
        else if (task == FILTERS_TASK){
            if (task_type == DELETE_COMMAND){
                if (infos.size() != DELETE_FILTER_SIZE){
                    throw Bad_Request_Error();
                }
                reset_filters();
                cout << OK_COMMAND << endl;
                return;
            }
            else if (task_type == GET_COMMAND){
                throw Bad_Request_Error();
            }
            string filter_type, city, room_type; 
            int min_star, max_star, quantity, check_in, check_out;
            double min_price, max_price;
            bool activation_status;
            for (int i = 3; i < infos.size(); i++){
                if (infos[i] == CITY_FILTER_TYPE){
                    city = infos[++i];
                    filter_type = CITY_FILTER_TYPE;
                }
                else if (infos[i] == MIN_STAR_KEYWORD){
                    min_star = stoi(infos[++i]);
                    filter_type = STAR_FILTER_TYPE;
                }
                else if (infos[i] == MAX_STAR_KEYWORD){
                    max_star = stoi(infos[++i]);
                    filter_type = STAR_FILTER_TYPE;
                }
                else if (infos[i] == MIN_PRICE_KETWORD){
                    min_price = stod(infos[++i]);
                    filter_type = COST_FILTER_TYPE;
                }
                else if (infos[i] == MAX_PRICE_KEYWORD){
                    max_price = stod(infos[++i]);
                    filter_type = COST_FILTER_TYPE;
                }
                else if (infos[i] == TYPE_KEYWORD){
                    room_type = infos[++i];
                    filter_type = ROOM_FILTER_TYPE;
                }
                else if (infos[i] == QUANTITY_KEYWORD){
                    quantity = stoi(infos[++i]);
                    filter_type = ROOM_FILTER_TYPE;
                }
                else if (infos[i] == CHECK_IN_KEYWORD){
                    check_in = stoi(infos[++i]);
                    filter_type = ROOM_FILTER_TYPE;
                }
                else if (infos[i] == CHECK_OUT_KEYWORD){
                    check_out = stoi(infos[++i]);
                    filter_type = ROOM_FILTER_TYPE;
                }
                else if (infos[i] == ACTIVE_KEYWORD){
                    if (infos[i + 1] != TRUE_KEYWORD && infos[i + 1] != FALSE_KEYWORD)
                        throw Bad_Request_Error();
                    activation_status = infos[++i] == TRUE_KEYWORD ? true : false;
                    filter_type = DEFAULT_FILTER_TYPE;
                }
                else if (filter_type != CITY_FILTER_TYPE){
                    throw Bad_Request_Error();
                }
            }
            if (filter_type == CITY_FILTER_TYPE){
                for (int i = 5; i < infos.size(); i++)
                    city += " " + infos[i];
                city_filter =  City_Filter(city);
                city_filter.set_status(true);
            }
            else if (filter_type == STAR_FILTER_TYPE && infos.size() == STAR_FILTER_SIZE){
                if (max_star < min_star || max_star > MAX_STAR || max_star < MIN_STAR || min_star < MIN_STAR || min_star > MAX_STAR){
                    throw Bad_Request_Error();
                }
                star_filter = Star_Filter(min_star, max_star);
                star_filter.set_status(true);
            }
            else if (filter_type == COST_FILTER_TYPE && infos.size() == COST_FILTER_SIZE){
                if (min_price < 0 || max_price < 0 || min_price > max_price){
                    throw Bad_Request_Error();
                }
                avg_cost_filter = Avg_Cost_Filter(min_price, max_price);
                avg_cost_filter.set_status(true);
            }
            else if (filter_type == ROOM_FILTER_TYPE && infos.size() == ROOM_FILTER_SIZE){
                room_filter = Room_Filter (room_type, check_in, check_out, quantity);
                room_filter.set_status(true);
            }
            else if (filter_type == DEFAULT_FILTER_TYPE && infos.size() == DEFAULT_FILTER_SIZE){
                default_filter->set_status(activation_status);
            }
            else{
                throw Bad_Request_Error();
            }
            default_filter->set_status(false);
            cout << OK_COMMAND << endl;
        }
        else if (task == RESERVES_TASK){
            if (task_type == POST_COMMAND && infos.size() == RESERVE_SIZE){
                string hotel_id, room_type;
                int quantity, check_in, check_out;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else if (infos[i] == TYPE_KEYWORD){
                        room_type = infos[++i];
                    }
                    else if (infos[i] == QUANTITY_KEYWORD){
                        quantity = stoi(infos[++i]);
                    }
                    else if (infos[i] == CHECK_IN_KEYWORD){
                        check_in = stoi(infos[++i]);
                    }
                    else if (infos[i] == CHECK_OUT_KEYWORD){
                        check_out = stoi(infos[++i]);
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                if (!has_hotel(hotel_id)){
                    throw Not_Found_Error();
                }
                Hotel* curr_hotel = find_hotel_by_id(hotel_id);
                if (curr_hotel->can_reserve(current_user, room_type, quantity, check_in, check_out)){
                    curr_hotel->reserve(current_user, room_type, quantity, check_in, check_out);
                }
                if (current_user->has_enough_rooms_for_default_filter() &&
                (!city_filter.get_status()) && (!star_filter.get_status()) &&
                (!room_filter.get_status()) && (!avg_cost_filter.get_status()))
                    default_filter->set_status(true);
            }
            else if (task_type == GET_COMMAND && infos.size() == SHOW_RESERVES_SIZE){
                current_user->show_reserves();
            }
            else if (task_type == DELETE_COMMAND && infos.size() == DELETE_RESERVES_SIZE){
                int id;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == ID_KEYWORD){
                        id = stoi(infos[++i]);
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                if (!current_user->has_id(id)){
                    throw Not_Found_Error();
                }
                else{
                    string hotel_id = current_user->delete_reservation(id);
                    find_hotel_by_id(hotel_id)->free_rooms(id);
                    cout << OK_COMMAND << endl;
                    return;
                }
            }
            else{
                throw Bad_Request_Error();
            }
        }
        else if (task == COMMENTS_TASK){
            if (task_type == POST_COMMAND && infos.size() == COMMENT_SIZE){
                string hotel_id, comment;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else if (infos[i] == COMMENT_KEYWORD){
                        comment = infos[++i];
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                if (!has_hotel(hotel_id)){
                    throw Not_Found_Error();
                }
                find_hotel_by_id(hotel_id)->add_comment(current_user->get_name(), comment);
                cout << OK_COMMAND << endl;
            }
            else if (task_type == GET_COMMAND && infos.size() == SHOW_COMMENT_SIZE){
                string hotel_id;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                find_hotel_by_id(hotel_id)->show_comments();
            }
            else{
                throw Bad_Request_Error();
            }
        }
        else if (task == RATINGS_TASK){
            if (task_type == POST_COMMAND && infos.size() == RATE_SIZE){
                string hotel_id;
                double location, cleanliness, staff, facilities, value, overall;
                for (int i = 3; i < infos.size(); i++){
                    if ((infos[i] == LOCATION_KEYWORD || infos[i] == CLEANLINESS_KEYWORD
                    || infos[i] == STAFF_KEYWORD || infos[i] == FACILITIES_KEYWORD
                    || infos[i] == VALUE_FOR_MONEY_KEYWORD || infos[i] == OVERALL_RATING_KEYWORD)
                    && (stod(infos[i + 1]) > MAX_RATING || stod(infos[i + 1]) < MIN_RATING)){
                        throw Bad_Request_Error();
                    }
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else if (infos[i] == LOCATION_KEYWORD){
                        location = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == CLEANLINESS_KEYWORD){
                        cleanliness = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == STAFF_KEYWORD){
                        staff = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == FACILITIES_KEYWORD){
                        facilities = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == VALUE_FOR_MONEY_KEYWORD){
                        value = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == OVERALL_RATING_KEYWORD){
                        overall = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                if (!has_hotel(hotel_id)){
                    throw Not_Found_Error();
                }
                find_hotel_by_id(hotel_id)->add_user_rating(overall, current_user);
                current_user->add_rating(hotel_id, location, cleanliness, staff, facilities, value, overall);
                cout << OK_COMMAND << endl;
            }
            else if (task_type == GET_COMMAND && infos.size() == SHOW_RATE_SIZE){
                string hotel_id;
                for (int i = 3; i < infos.size(); i++){
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                find_hotel_by_id(hotel_id)->show_ratings();
            }
            else{
                throw Bad_Request_Error();
            }
        }
        else if (task == SORT_TASK){
            sort(hotels.begin(), hotels.end(), [](Hotel* f, Hotel* s){return (f->get_id() <= s->get_id());});
            string property;
            bool ascending_order;
            for (int i = 3; i < infos.size(); i++){
                if (infos[i] == PROPERTY_KEYWORD){
                    property = infos[++i];
                }
                else if (infos[i] == ORDER_KEYWORD){
                    if (infos[i + 1] != ASCENDING_KEYWORD && infos[i + 1] != DESCENDING_KEYWORD)
                        throw Bad_Request_Error();
                    ascending_order = infos[++i] == ASCENDING_KEYWORD ? true : false;
                }
                else{
                    throw Bad_Request_Error();
                }
            }
            if (property == ID_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return (ascending_order ^ (f->get_id() > s->get_id()));});
            else if (property == NAME_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_name() == s->get_name() && f->get_id() < s->get_id()) || (f->get_name() != s->get_name() && ascending_order ^ (f->get_name() > s->get_name())));});
            else if (property == STAR_RATING_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_star_rating() == s->get_star_rating() && f->get_id() < s->get_id()) || (f->get_star_rating() != s->get_star_rating() && ascending_order ^ (f->get_star_rating() > s->get_star_rating())));});
            else if (property == CITY_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_city() == s->get_city() && f->get_id() < s->get_id()) || (f->get_city() != s->get_city() && ascending_order ^ (f->get_city() > s->get_city())));});
            else if (property == STANDARD_ROOM_PRICE_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_standard_room_price() == s->get_standard_room_price() && f->get_id() < s->get_id()) || (f->get_standard_room_price() != s->get_standard_room_price() && ascending_order ^ (f->get_standard_room_price() > s->get_standard_room_price())));});
            else if (property == DELUXE_ROOM_PRICE_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_deluxe_room_price() == s->get_deluxe_room_price() && f->get_id() < s->get_id()) || (f->get_deluxe_room_price() != s->get_deluxe_room_price() && ascending_order ^ (f->get_deluxe_room_price() > s->get_deluxe_room_price())));});
            else if (property == LUXURY_ROOM_PRICE_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_luxury_room_price() == s->get_luxury_room_price() && f->get_id() < s->get_id()) || (f->get_luxury_room_price() != s->get_luxury_room_price() && ascending_order ^ (f->get_luxury_room_price() > s->get_luxury_room_price())));});
            else if (property == PREMIUM_ROOM_PRICE_KEYWORD )
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_premium_room_price() == s->get_premium_room_price() && f->get_id() < s->get_id()) || (f->get_premium_room_price() != s->get_premium_room_price() && ascending_order ^ (f->get_premium_room_price() > s->get_premium_room_price())));});
            else if (property == AVERAGE_ROOM_PRICE_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_avg_room_price() == s->get_avg_room_price() && f->get_id() < s->get_id()) || (f->get_avg_room_price() != s->get_avg_room_price() && ascending_order ^ (f->get_avg_room_price() > s->get_avg_room_price())));});
            else if (property == RATING_OVERALL_KEYWORD)
                sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_overall_rating() == s->get_overall_rating() && f->get_id() < s->get_id()) || (f->get_overall_rating() != s->get_overall_rating() && ascending_order ^ (f->get_overall_rating() > s->get_overall_rating())));});
            else if (property == RATING_PERSONAL_KEYWORD){
                if (current_user->has_rated_enough_hotels() || current_user->get_manual_weights_status()){
                    User* user_copy = current_user;
                    sort(hotels.begin(), hotels.end(), [=](Hotel* f, Hotel* s){return ((f->get_personal_rating(user_copy) == s->get_personal_rating(user_copy) && f->get_id() < s->get_id()) || (f->get_personal_rating(user_copy) != s->get_personal_rating(user_copy) && ascending_order ^ (f->get_personal_rating(user_copy) > s->get_personal_rating(user_copy))));});
                }
                current_user->update_has_used_personal_sort_status(true);
            }
            else{
                throw Bad_Request_Error();
            }
            custom_sort_filter_on = true;
            cout << OK_COMMAND << endl;
        }
        else if (task == MANUAL_WEIGHTS_TASK){
            if (task_type == POST_COMMAND){
                double location, cleanliness, staff, facilities, value_for_money;
                bool activation_status;
                for (int i = 3; i < infos.size(); i++){
                    if ((infos[i] == LOCATION_KEYWORD || infos[i] == CLEANLINESS_KEYWORD ||
                        infos[i] == STAFF_KEYWORD || infos[i] == FACILITIES_KEYWORD || 
                        infos[i] == VALUE_FOR_MONEY_KEYWORD) && (stod(infos[i + 1]) > MAX_RATING || stod(infos[i + 1]) < MIN_RATING)){
                            throw Bad_Request_Error();
                    }
                    if (infos[i] == ACTIVE_KEYWORD){
                        if (infos[i + 1] != TRUE_KEYWORD && infos[i + 1] != FALSE_KEYWORD)
                            throw Bad_Request_Error();
                        activation_status = infos[++i] == TRUE_KEYWORD ? true : false;
                    }
                    else if (infos[i] == LOCATION_KEYWORD){
                        location = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == CLEANLINESS_KEYWORD){
                        cleanliness = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == STAFF_KEYWORD){
                        staff = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == FACILITIES_KEYWORD){
                        facilities = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else if (infos[i] == VALUE_FOR_MONEY_KEYWORD){
                        value_for_money = cut_leading_decimals(stod(infos[++i]), PRECISION);
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                if (infos.size() == MANUAL_WEIGHTS_FALSE_ACTIVATION_SIZE){
                    if (infos[MANUAL_WEIGHTS_FALSE_ACTIVATION_SIZE - 2] != ACTIVE_KEYWORD)
                        throw Bad_Request_Error();
                    current_user->update_manual_weights_status(activation_status);
                }
                else if (infos.size() == MANUAL_WEIGHTS_TRUE_ACTIVATION_SIZE){
                    current_user->update_manual_weights(activation_status, location, cleanliness,
                                staff, facilities, value_for_money);
                }
                else{
                    throw Bad_Request_Error();
                }
                cout << OK_COMMAND << endl;
            }
            else if (task_type == GET_COMMAND){
                current_user->show_manual_weights();
            }
            else
                throw Bad_Request_Error();   
        }
        else if (task == ESTIMATED_WEIGHTS_TASK){
            if (infos.size() == ESTIMATED_WEIGHTS_SIZE && task_type == GET_COMMAND){
                current_user->show_estimated_weights();
            }
            else {
                throw Bad_Request_Error();
            }
            
        }
        else {
            throw Not_Found_Error();
        }
    }
    else {
        if (task == SIGNUP_TASK){
            if (infos.size() != SIGNUP_SIZE){
                throw Bad_Request_Error();
            }
            string email, username, password;
            for (int i = 3; i < infos.size(); i ++){
                if (infos[i] == EMAIL_KEYWORD){
                    if (is_unique(EMAIL_KEYWORD, infos[i + 1])){
                        email = infos[++i];
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                else if (infos[i] == USERNAME_KEYWORD){
                    if (is_unique(USERNAME_KEYWORD, infos[i + 1])){
                        username = infos[++i];
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                else if (infos[i] == PASSWORD_KEYWORD){
                    password = infos[++i];
                }
                else{
                    throw Bad_Request_Error();
                }
            }
            User* new_user = new User(email, username, password);
            customers.push_back(new_user);
            current_user = new_user;
            current_user->set_log_status(true);
            have_logged_in_user = true;
            default_filter = new Default_Price_Filter (new_user);
            sort_hotels();
            cout << OK_COMMAND << endl;	
        }
        else if (task == LOGIN_TASK){
            if (infos.size() != LOGIN_SIZE) {
                throw Bad_Request_Error();
            }
            string email, password;
            for (int i = 3; i < infos.size(); i ++){
                if (infos[i] == EMAIL_KEYWORD){
                    if (!is_unique(EMAIL_KEYWORD, infos[i + 1])){
                        email = infos[++i];
                    }
                    else{
                        throw Bad_Request_Error();
                    }
                }
                else if (infos[i] == PASSWORD_KEYWORD){
                    password = infos[++i];
                }
                else{
                    throw Bad_Request_Error();
                }
            }
            current_user = find_user_by_email(email);
            if (current_user->same_password(password)){
                current_user->set_log_status(true);
                have_logged_in_user = true;
                cout << OK_COMMAND << endl;
            }
            else{
                throw Bad_Request_Error();
            }
            default_filter = new Default_Price_Filter (current_user);
            sort_hotels();
        }
        else if (task == HOTELS_TASK || task == LOGOUT_TASK || task == WALLET_TASK || task == FILTERS_TASK
                || task == RESERVES_TASK || task == COMMENTS_TASK || task == RATINGS_TASK
                || task == MANUAL_WEIGHTS_TASK || task == ESTIMATED_WEIGHTS_TASK || task == SORT_TASK){
            throw Permission_Error();
        }
        else {
            throw Not_Found_Error();
        }
    }
}
void Application::add_hotel(string unique_id, string property_name, int hotel_star_rating,
        string hotel_overview, string property_amenities, string city,
        pair<double, double> geo_place, string image_url, int num_standard_rooms,
        int num_deluxe_rooms, int num_luxury_rooms,	int num_premium_rooms,
        int price_standard_room, int price_deluxe_room,	int price_luxury_room,
        int price_premium_room){
    Hotel* new_hotel = new Hotel(unique_id, property_name, hotel_star_rating,
        hotel_overview, property_amenities, city, geo_place, image_url, num_standard_rooms,
        num_deluxe_rooms, num_luxury_rooms,	num_premium_rooms, price_standard_room,
        price_deluxe_room, price_luxury_room, price_premium_room);
    hotels.push_back (new_hotel);
}
void Application::add_hotel_rating(string unique_id, double rating_location, double rating_cleanliness,
		double rating_staff, double rating_facilities,
		double rating_value_for_money, double rating_overall){
            Hotel* selected_hotel = find_hotel_by_id(unique_id);
            selected_hotel->add_rating(rating_location, rating_cleanliness, rating_staff,
                            rating_facilities, rating_value_for_money, rating_overall);
}

bool Application::is_unique(string type, string data){
    if (type == USERNAME_KEYWORD){
        for (auto x : customers){
            if (x->same_username(data))
                return false;
        }
        return true;
    }
    else if (type == EMAIL_KEYWORD){
        for (auto x : customers){
            if (x->same_email(data))
                return false;
        }
        return true;
    }
}
User* Application::find_user_by_email(string email){
    for (auto x : customers){
        if (x->same_email(email))
            return x;
    }
}
bool Application::sorted_hotels(Hotel* a, Hotel* b){
    return (a->get_id() <= b->get_id());
}
void Application::sort_hotels(){
    for (int i = 0; i < hotels.size(); i++){
        for (int j = i + 1; j < hotels.size(); j++){
            if (!sorted_hotels(hotels[i], hotels[j]))
                swap(hotels[i], hotels[j]);
        }
    }
}
void Application::reset_filters(){
    city_filter.set_status(false);
    star_filter.set_status(false);
    room_filter.set_status(false);
    avg_cost_filter.set_status(false);
    default_filter->set_status(true);
}
bool Application::has_hotel (string id){
    for (auto x : hotels){
        if (x->get_id() == id)
            return true;
    }
    return false;
}
Hotel* Application::find_hotel_by_id (string id){
    for (auto x : hotels){
        if (x->get_id() == id)
            return x;
    }
    throw Not_Found_Error();
}
bool Application::can_signup_user(string username){
	return (is_unique(USERNAME_KEYWORD, username) && username != "");
}
User* Application::signup_user(string username, string password, string email){
    User* new_user = new User(email, username, password);
    customers.push_back(new_user);
    current_user = new_user;
    current_user->set_log_status(true);
    have_logged_in_user = true;
    default_filter = new Default_Price_Filter (new_user);
    sort_hotels();	
    return current_user;
}
void Application::logout_user(){
    current_user->set_log_status(false);
    have_logged_in_user = false;
    reset_filters();
}
User* Application::find_user_by_username(string username){
    for (auto x : customers){
        if (x->same_username(username))
            return x;
    }
}
void Application::login_user(string username){
    current_user = find_user_by_username(username);
    current_user->set_log_status(true);
    have_logged_in_user = true;
}
string Application::get_hotels_list_html(int min_star, int max_star){
    ostringstream body;
    star_filter = Star_Filter(min_star, max_star);
    star_filter.set_status(true);
    for (auto x : hotels){
        string name = x->get_name();
        if (name.size() >= 30){
            name = name.substr(0, 28) + "...";
        }
        body
        << "<style>"
        << ".button1 {"
        << "width: 300px;"
        << "background-color: tomato;"
        << "border: none;"
        << "color: white;"
        << "padding: 16px 32px;"
        << "text-align: center;"
        << "text-decoration: none;"
        << "display: inline-block;"
        << "font-size: 16px;"
        << "transition-duration: 0.4s;"
        << "cursor: pointer;"
        << "}"
        << ".button1:hover {"
        << "background-color: red;"
        << "color: white;"
        << "}"
        << "</style>";
        if (star_filter.eligible_hotel(x)){
            body
            << "<div class='gallery'>"
            << "<img src=" << '"' << x->get_img() << '"' << "alt='Hotel_img' width='60' height='40'>"
            << "<div class='desc' style='font-size:15px'> &#127977 " << name << "<br /> &#11088 " << x->get_star_rating() << "<br />&#127757 " << x->get_city() << "</div>"
            << "<form action='/hotel' method='get'>"
            << "<input type='hidden' id='custid' name='id' value='" << x->get_id() << "'>"
            << "<div class='form-group'>"
            << "<button type='submit' class='button1'>Read More</button>"
            << "  </div> </div> </form>";
        }
    }
    return body.str();
}
