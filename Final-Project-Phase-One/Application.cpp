#include "Application.hpp"
using namespace std;

Application::Application (){
    have_logged_in_user = false;
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
                bool has_eligible_hotel = false;
                sort_hotels();
                for (auto x : hotels){
                    if (city_filter.eligible_hotel(x) && room_filter.eligible_hotel(x) &&
                        avg_cost_filter.eligible_hotel(x) && star_filter.eligible_hotel(x)){
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
            else{
                throw Bad_Request_Error();
            }
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
                    if (infos[i] != HOTEL_KEYWORD && (stod(infos[i + 1]) > MAX_RATING || stod(infos[i + 1]) < MIN_RATING)){
                        throw Bad_Request_Error();
                    }
                    if (infos[i] == HOTEL_KEYWORD){
                        hotel_id = infos[++i];
                    }
                    else if (infos[i] == LOCATION_KEYWORD){
                        location = stod(infos[++i]);
                    }
                    else if (infos[i] == CLEANLINESS_KEYWORD){
                        cleanliness = stod(infos[++i]);
                    }
                    else if (infos[i] == STAFF_KEYWORD){
                        staff = stod(infos[++i]);
                    }
                    else if (infos[i] == FACILITIES_KEYWORD){
                        facilities = stod(infos[++i]);
                    }
                    else if (infos[i] == VALUE_FOR_MONEY_KEYWORD){
                        value = stod(infos[++i]);
                    }
                    else if (infos[i] == OVERALL_RATING_KEYWORD){
                        overall = stod(infos[++i]);
                    }
                    else {
                        throw Bad_Request_Error();
                    }
                }
                if (!has_hotel(hotel_id)){
                    throw Not_Found_Error();
                }
                find_hotel_by_id(hotel_id)->add_rating(location, cleanliness, staff, facilities,
                                                value, overall, current_user->get_name());
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
        }
        else if (task == HOTELS_TASK || task == LOGOUT_TASK || task == WALLET_TASK || task == FILTERS_TASK
                || task == RESERVES_TASK || task == COMMENTS_TASK || task == RATINGS_TASK){
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
}
