#include "Hotel.hpp"
using namespace std;

Hotel::Hotel(){}
Hotel::Hotel (string unique_id_, string property_name_, int hotel_star_rating_, string hotel_overview_,
    string property_amenities_, string city_, pair <double, double> geo_place_, string image_url_,
    int num_standard_rooms_,int num_deluxe_rooms_, int num_luxury_rooms_, int num_premium_rooms_,
    int price_standard_rooms_, int price_deluxe_rooms_, int price_luxury_rooms_, int price_premium_rooms_){
    unique_id = unique_id_;
    property_name = property_name_;
    hotel_star_rating = hotel_star_rating_;
    hotel_overview = hotel_overview_;
    property_amenities = property_amenities_;
    city = city_;
    geo_place = geo_place_;
    image_url = image_url_;
    room_numbers.num_standard_rooms = num_standard_rooms_;
    room_numbers.num_deluxe_rooms = num_deluxe_rooms_;
    room_numbers.num_luxury_rooms = num_luxury_rooms_;
    room_numbers.num_premium_rooms = num_premium_rooms_;
    room_prices.price_standard_rooms = price_standard_rooms_;
    room_prices.price_deluxe_rooms = price_deluxe_rooms_;
    room_prices.price_luxury_rooms = price_luxury_rooms_;
    room_prices.price_premium_rooms = price_premium_rooms_;
    add_room(num_standard_rooms_, 's');
    add_room(num_deluxe_rooms_, 'd');
    add_room(num_luxury_rooms_, 'l');
    add_room(num_premium_rooms_, 'p');
    total_num_of_rooms = num_standard_rooms_ + num_deluxe_rooms_ + num_luxury_rooms_ + num_premium_rooms_;
    double sum = 0, count = 0;
    if (price_standard_rooms_ > 0)
        count ++;
    if (price_deluxe_rooms_ > 0)
        count ++;
    if (price_luxury_rooms_ > 0)
        count ++;
    if (price_premium_rooms_ > 0)
        count ++;
    sum = price_standard_rooms_ +  price_deluxe_rooms_ + price_luxury_rooms_ +  price_premium_rooms_;
    if (count == 0)
        avg_price = 0;
    else
        avg_price = sum / count;
    rating = new Rating();
}
void Hotel::reserve (User* customer, string room_type, int quantity, int check_in, int check_out){
    int cost = quantity * find_room_type_cost (room_type) * (check_out - check_in + 1);
    vector <string> room_ids = reserve_rooms (customer->get_reservation_id(), quantity, room_type, check_in, check_out);
    for (int i = 0; i < room_ids.size() - 1; i++)
        cout << room_ids[i] << " ";
    cout << room_ids[room_ids.size() - 1] << endl;
    customer->charge_wallet(-cost);
    customer->add_reservation(unique_id, room_type, quantity, cost, check_in, check_out, room_ids);
}
bool Hotel::can_reserve (User* customer, string room_type, int quantity, int check_in, int check_out){
    int cost = find_room_type_cost (room_type);
    if (customer->can_afford(quantity * cost)){ 
        if (has_enough_rooms(room_type, check_in, check_out, quantity))
            return true;
        else{
            cout << NOT_ENOUGH_ROOM_MSG << endl;
            return false;
        }
    }
    else{
        cout << NOT_ENOUGH_CREDIT_MSG << endl;
        return false;
    }
}
string Hotel::get_id (){return unique_id;}
bool Hotel::same_city (string city_){
    return (city ==  city_);
}
bool Hotel::sufficient_star (int min_star, int max_star){
    return (min_star <= hotel_star_rating && max_star >= hotel_star_rating);
}
bool Hotel::adequate_cost (double min_cost, double max_cost){
    return (avg_price >= min_cost && avg_price <= max_cost);
}
bool Hotel::has_enough_rooms (string type, int check_in, int check_out, int quantity){
    int room_count = 0;
    for (auto x : rooms){
        if (x->is_rentable(type, check_in, check_out))
            room_count++;
    }
    return (room_count >= quantity);
}
void Hotel::list_hotel (){
    cout << unique_id << " " << property_name << " " << hotel_star_rating << " " << city << " " <<
    total_num_of_rooms << " " << fixed << setprecision(PRECISION) << avg_price << " " << endl;
}
void Hotel::show_hotel(){
    cout << unique_id << endl << property_name << endl << "star: " << hotel_star_rating << endl <<
    "overview: " << hotel_overview << endl << "amenities: " << property_amenities << endl <<
    "city: " << city << endl << fixed << setprecision(PRECISION) << "latitude: " << geo_place.first << endl	<<
    "longitude: " << geo_place.second << endl << "#rooms: " << room_numbers.num_standard_rooms << " " <<
    room_numbers.num_deluxe_rooms << " " <<	room_numbers.num_luxury_rooms << " " <<
    room_numbers.num_premium_rooms << endl << "price: " << room_prices.price_standard_rooms << " " << 
    room_prices.price_deluxe_rooms << " " << room_prices.price_luxury_rooms << " " << 
    room_prices.price_premium_rooms << endl;
}
void Hotel::free_rooms (int reservation_id_){
    for (auto r : rooms){
        r->free_room(reservation_id_);
    }
}
void Hotel::add_comment(string user, string comment){
    comments.push_back(make_pair(user, comment));
}
void Hotel::show_comments(){
    for (auto i = comments.rbegin(); i < comments.rend(); i++){
        cout << (*i).first << ": " << (*i).second << endl;
    }
}
void Hotel::add_rating (double location, double cleanliness, double staff, double facilities, double value, double overall){
    rating = new Rating(unique_id ,location, cleanliness, staff, facilities, value, overall);
}
void Hotel::add_user_rating (double overall, User* user){
    user_overall_rating.insert(make_pair(user, overall));
}

void Hotel::show_ratings(){
    rating->show_rating();
}

void Hotel::add_room(int number, char type){
    for (int i = 1; i <= number; i++){
        Room* new_room = new Room(type + to_string(i));
        rooms.push_back(new_room);
    }
}

int Hotel::find_room_type_cost (string room_type){
    if (room_type[0] == 's')
        return room_prices.price_standard_rooms;
    else if (room_type[0] == 'd')
        return room_prices.price_deluxe_rooms;
    else if (room_type[0] == 'l')
        return room_prices.price_luxury_rooms;
    return room_prices.price_premium_rooms;
}
bool Hotel::in_default_range(User* user){
	return (abs(avg_price - user->calc_avg_res_cost()) <= 2 * user->calc_deviation());
}
vector <string> Hotel::reserve_rooms(int reservation_id, int quantity, string type, int check_in, int check_out){
    vector<string> room_ids;
    for (int i = 0; i < rooms.size() && quantity; i++){
        if (rooms[i]->is_rentable(type, check_in, check_out)){
            rooms[i]->reserve_room(reservation_id, room_ids, check_in, check_out);
            quantity--;
        }
    }
    return room_ids;
}
double Hotel::get_avg_room_price(){
    return avg_price;
}
string Hotel::get_name(){
    return property_name;
}
int Hotel::get_star_rating(){
    return hotel_star_rating;
}
string Hotel::get_city(){
    return city;
}
int Hotel::get_standard_room_price(){
    return room_prices.price_standard_rooms;
}
int Hotel::get_deluxe_room_price(){
    return room_prices.price_deluxe_rooms;
}
int Hotel::get_luxury_room_price(){
    return room_prices.price_luxury_rooms;
}
int Hotel::get_premium_room_price(){
    return room_prices.price_premium_rooms;
}
double Hotel::get_overall_rating(){
    return rating->overall;
}
double Hotel::calc_weighted_average(struct Weights* weights, struct Rating* rating){
    double sum = (weights->location * rating->location) + (weights->cleanliness * rating->cleanliness)
    + (weights->staff * rating->staff) + (weights->facilities * rating->facilities)
    + (weights->value_for_money * rating->value);
    double count = (weights->location + weights->cleanliness + weights->staff + weights->facilities + weights->value_for_money);
    return (sum/count);
}
bool Hotel::has_personal_rating_method(User* current_user){
    return ((user_overall_rating.find(current_user) != user_overall_rating.end()) || current_user->get_manual_weights_status());
}
double Hotel::get_personal_rating(User* current_user){
    if (user_overall_rating.find(current_user) != user_overall_rating.end()){
        return user_overall_rating.find(current_user)->second;
    }
    else if (current_user->get_manual_weights_status()){
        return calc_weighted_average(current_user->get_manual_weights(), rating);
    }
    else{
        Weights* estimated_weights = current_user->get_estimated_weights();
        return calc_weighted_average(estimated_weights, rating);
    }
}
string Hotel::get_img(){
    return image_url;
}
string Hotel::get_overview(){
    return hotel_overview;
}
string Hotel::get_property_amenities(){
    return property_amenities;
}
string Hotel::get_rooms_table_html(string username){
    ostringstream body;
    body
    << "<!DOCTYPE html>"
    << "<html>"
    << "<head> <title>Hotel</title>"
    << "<style>"
    << "ul {"
    << "list-style-type: none;"
    << "margin: 0;"
    << "padding: 0;"
    << "overflow: hidden;"
    << "background-color: orange;"
    << "}"

    << "li {"
    << "float: left;"
    << "}"

    << "li a {"
    << "display: block;"
    << "color: white;"
    << "text-align: center;"
    << "padding: 14px 16px;"
    << "text-decoration: none;"
    << "}"

    << "li a:hover:not(.active) {"
    << "background-color: tomato;"
    << "}"

    << ".active {"
    << "background-color: tomato;"
    << "}"
   
    << "</style>"
    << "</head>"
    << "<body>"

    << "<ul>"
    << "<li><a href='/home'>Home</a></li>"
    << "<li><a href='/wallet'>Wallet</a></li>"
    << "<li style='float:right'><a class='active' href='/logout'>&#128100 Logout "
    << username << "</a></li>"
    << "</ul>"
    << "<br /> <br />";
    
    body
    << "<div class='gallery'>"
    << "<img src=" << '"' << image_url << '"' << "alt='Hotel_img' width='360' height='360'>"
    << "</div>"
    << "<div style='background-color:tomato;color:white;padding:20px;'>"
    << "<h1>" << property_name << "</h1>"
    << "<p>" << hotel_overview << "</p>"
    << "<p>";
    for (int i = 0; i < hotel_star_rating; i++)
        body << "&#11088";
    body << "</p>"
    << "<p>" << city << "</p>"
    << "</div> <br />"
    << "<div style='background-color:tomato;color:white;padding:20px;'>"
    << "<h1>Hotel Amenities</h1>"
    << "<ol>"
    << "<li>";
    for (int i = 0; i < property_amenities.size(); i++){
        if (property_amenities[i] == '|'){
            body << "</li> <br /> <li>";
        }
        else{
            body << property_amenities[i];
        }
    }
    body
    << "</li> </ol>"
    << "</div> <br />"
    << "<style>"
    << "table {"
    << "width:100%;"
    << "}"
    << "table, th, td {"
    << "border: 1px solid black;"
    << "border-collapse: collapse;"
    << "}"
    << "th, td {"
    << "padding: 15px;"
    << "text-align: left;"
    << "}"
    << "#t01 tr:nth-child(even) {"
    << "background-color: peachpuff;"
    << "}"
    << "#t01 tr:nth-child(odd) {"
    << "background-color: orange;"
    << "}"
    << "#t01 th {"
    << "background-color: orangered;"
    << "color: white;"
    << "}"
    << "</style>"
    << "<table id = 't01'>"
    << "<tr>"
    << "<th>Type</th>"
    << "<th>Count</th>" 
    << "<th>Price/Night</th>"
    << "</tr>"
    << "<tr>"
    << "<td> Standard </td>"
    << "<td>" << room_numbers.num_standard_rooms << "</td>"
    << "<td>" << room_prices.price_standard_rooms << "</td>"
    << "</tr>"
    << "<tr>"
    << "<td> Deluxe </td>"
    << "<td>" << room_numbers.num_deluxe_rooms << "</td>"
    << "<td>" << room_prices.price_deluxe_rooms << "</td>"
    << "</tr>"
    << "<tr>"
    << "<td> Luxury </td>"
    << "<td>" << room_numbers.num_luxury_rooms << "</td>"
    << "<td>" << room_prices.price_luxury_rooms << "</td>"
    << "</tr>"
    << "<tr>"
    << "<td> Premium </td>"
    << "<td>" << room_numbers.num_premium_rooms << "</td>"
    << "<td>" << room_prices.price_premium_rooms << "</td>"
    << "</tr>"
    << "</table>"
    << "</body>"
    << "</html>";
    return body.str();
}

