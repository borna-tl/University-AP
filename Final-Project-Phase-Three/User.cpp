#include "User.hpp"
using namespace std;
void Status::reset(){
    wrong_username_or_password = false; wrong_password_copy = false;
	used_username = false; has_logged_out = false;
	wallet_update_status = 0;
}
User::User (string email_, string username_, string password_){
    email = email_;
    username = username_;
    password = myhash(password_);
    money = 0;
    balance.push_back(money);
    reservation_id = 1;
    manual_weights = new Weights();
    estimated_weights = new Weights();
    estimated_weights->is_on = false;
    has_used_personal_sort = false;
}
bool User::is_logged_in(){
    return logged_in;
}
bool User::same_username(string username_){
    return (username_ == username);
}
bool User::same_email(string email_){
    return (email_ == email);
}
void User::set_log_status (bool status){
    logged_in = status;
}
bool User::same_password(string password_){
    return (password == myhash(password_));
}
void User::charge_wallet(double money_){
    money += money_;
    balance.push_back(money);
}
void User::show_balance_history(int count){
    for (auto i = balance.rbegin(); i < min(balance.rend(), balance.rbegin() + count); i++){
        cout << (int) *i << endl;
    }
}
bool User::can_afford (double money_){
    return (money >= money_);
}
void User::add_reservation (string hotel_id_, string room_type_, int quantity_, double cost_,
                        int check_in_, int check_out_, vector <string> room_ids_){
                            Reservation* new_reservation = new Reservation (reservation_id, hotel_id_, room_type_, quantity_,
                            cost_, check_in_, check_out_, room_ids_);
                            reservations.push_back(new_reservation); 
                            reservation_id++;
                        }
void User::show_reserves (){
    if (reservations.size() == 0){
        cout << EMPTY_MSG << endl;
        return;
    }
    for (auto i = reservations.rbegin(); i < reservations.rend(); i++){
        (*i)->print();
    }
}
bool User::has_id(int id){
    for (auto r : reservations){
        if (r->same_id(id))
            return true;
    }
    return false;
}
const Reservation* User::find_reservation_by_id(int id){
    for (auto x : reservations){
        if (x->same_id(id))	
            return x;
    }
}
string User::delete_reservation(int id){
    auto it = reservations.begin();
    for (it; it < reservations.end(); it++){
        if ((*it)->id == id)
            break;
    }
    charge_wallet((*it)->cost * REFUND_MONEY);
    string hotel_id_ = (*it)->hotel_id;
    reservations.erase(it);
    return hotel_id_;
}
string User::get_name(){return username;}
int User::get_reservation_id(){
    return reservation_id;
}
bool User::has_enough_rooms_for_default_filter (){
    return (reservations.size() >= MIN_NUM_FOR_DEVIATION);
}
double User::calc_deviation(){
	double avg = calc_avg_res_cost(); 
    double sum = 0;
    int count = 0;
	for (auto x : reservations){
        sum += x->quantity * pow(((x->cost) / ((x->check_out - x->check_in + 1) * x->quantity) - avg), 2);
        count += x->quantity;
    }
    return cut_leading_decimals(sqrt(sum / (count - 1)), PRECISION);
}
double User::calc_avg_res_cost(){
	int count = 0;
    double sum = 0;
    for (auto x : reservations){
        sum += (x->cost) / (x->check_out - x->check_in + 1);
        count += x->quantity;
    }
	sum /= count;
	return sum;
}


void User::update_manual_weights(bool status, double location, double cleanliness, double staff, double facilities, double value_for_money){
    manual_weights->update_weights(location, cleanliness, staff, facilities, value_for_money);
    manual_weights->update_status(status);
}

void User::update_manual_weights_status(bool status){
    manual_weights->update_status(status);
}
void User::show_manual_weights(){
    manual_weights->show();
}
bool User::get_manual_weights_status(){
    return manual_weights->is_on;
}
Weights* User::get_manual_weights(){
    return manual_weights;
}
bool User::has_rated_enough_hotels(){
    return (ratings.size() >= MIN_NUM_OF_RATED_HOTELS_FOR_PERSONAL_RATING);
}
void User::add_rating(string hotel_id_, double location_, double cleanliness_, double staff_,
				double facilities_, double value_, double overall_){
                    auto iterator = find_if(ratings.begin(), ratings.end(), [&hotel_id_](Rating a){return (a.hotel_id == hotel_id_);});
                    if (iterator != ratings.end()){
                        iterator->update(hotel_id_, location_, cleanliness_, staff_, 
                                        facilities_, value_, overall_);
                    }
                    else{
                        Rating new_rating = Rating(hotel_id_, location_, cleanliness_,
                                            staff_, facilities_, value_, overall_);
                        ratings.push_back(new_rating);
                    }
                }
double User::overall_satisfaction_estimation(struct Rating* rating, struct Weights* weights){
    double sum = (weights->location * rating->location) + (weights->cleanliness * rating->cleanliness)
    + (weights->staff * rating->staff) + (weights->facilities * rating->facilities)
    + (weights->value_for_money * rating->value);
    double count = (weights->location + weights->cleanliness + weights->staff + weights->facilities + weights->value_for_money);
    return (sum/count);
}
double User::error_estimation(struct Rating* rating, struct Weights* weights){
    return pow((overall_satisfaction_estimation(rating, weights) - rating->overall), 2);
}
double User::gradient(struct Rating* rating, struct Weights* weights, int i){
    struct Weights new_weights = *weights;
    switch (i) {
    case 0:
        new_weights.location += EPSILON;
        return ((error_estimation(rating, &new_weights) - error_estimation(rating, weights)) / EPSILON);
        break;
    case 1:
        new_weights.cleanliness += EPSILON;
        return ((error_estimation(rating, &new_weights) - error_estimation(rating, weights)) / EPSILON);
        break;
    case 2:
        new_weights.staff += EPSILON;
        return ((error_estimation(rating, &new_weights) - error_estimation(rating, weights)) / EPSILON);
        break;
    case 3:
        new_weights.facilities += EPSILON;
        return ((error_estimation(rating, &new_weights) - error_estimation(rating, weights)) / EPSILON);
        break;
    case 4:
        new_weights.value_for_money += EPSILON;
        return ((error_estimation(rating, &new_weights) - error_estimation(rating, weights)) / EPSILON);
        break;
    default:
        break;
    }
}
double User::fix_range(double d){
    if (d > UPPER_BOUND)
        return UPPER_BOUND;
    if (d < LOWER_BOUND)
        return LOWER_BOUND;
    return d;
}

void User::update_weights(vector <Rating>& ratings, struct Weights* weights){
    double d[5];
    for (int i = 0; i < 5; i++){
        d[i] = 0;
    }
    for (int j = 0; j < ratings.size(); j++){
        for (int i = 0; i < 5; i++){
            d[i] += gradient(&ratings[j], weights, i);
        }
    }
    weights->location = fix_range(weights->location - d[0]);
    weights->cleanliness = fix_range(weights->cleanliness - d[1]);
    weights->staff = fix_range(weights->staff - d[2]);
    weights->facilities = fix_range(weights->facilities - d[3]);
    weights->value_for_money = fix_range(weights->value_for_money - d[4]);
}
Weights* User::get_estimated_weights(){
    if (estimated_weights->is_on){
        return estimated_weights;
    }
    struct Weights random_weights;
    uniform_real_distribution<double> unif (LOWER_BOUND, UPPER_BOUND);
    default_random_engine re;
    int round = ROUNDS_COUNT;
    random_weights.location = unif(re);
    random_weights.cleanliness = unif(re);
    random_weights.staff = unif(re);
    random_weights.facilities = unif(re);
    random_weights.value_for_money = unif(re);
    while (round--){
        update_weights(ratings, &random_weights);
    }
    estimated_weights->location = random_weights.location;
    estimated_weights->cleanliness = random_weights.cleanliness;
    estimated_weights->staff = random_weights.staff;
    estimated_weights->facilities = random_weights.facilities;
    estimated_weights->value_for_money = random_weights.value_for_money;
    estimated_weights->is_on = true;
    return estimated_weights;
}
bool User::has_user_used_personal_sort(){
    return has_used_personal_sort;
}
void User::update_has_used_personal_sort_status(bool status){
    has_used_personal_sort = status;
}
void User::show_estimated_weights(){
    if (!has_rated_enough_hotels()){
        throw Insufficient_Rating_Error();
    }
    cout << fixed << setprecision(PRECISION) << "location " << estimated_weights->location << " cleanliness " <<
    estimated_weights->cleanliness << " staff " << estimated_weights->staff <<
    " facilities " << estimated_weights->facilities << " value_for_money " <<
    estimated_weights->value_for_money << endl;
}
string User::show_wallet_html(int update_status){
    ostringstream body;
    body
    << "<html>" << endl
    << "<head><title>Wallet</title>" << endl
    << "</head>"
    << "<body style='background-color: white; text-align: center;'>" << endl
    << "<div style='background-color:tomato;color:white;padding:1px;'>"
    << "<h1>Wallet Charge</h1>" << endl
    << "</div>"
    << "<br /> <br />"
    << "<div style='background-color:tomato;color:white;padding:1px;'>"
    << "<p>You Currently Have &#128178 " << money << "</p>" << endl
    << "</div>"
    << "<br />"
    << "<form action='/check_wallet' method='get'>" << endl
    << "<input name='amount' type='text' placeholder='Amount' />" << "<br />" << endl
    << "<button type='submit' >Charge!</button>" << endl
    << "</form>" << endl
    << "</div>" << endl;
    if (update_status == 1){
        body
        << "<br />"
        << "<div style='background-color:tomato;color:white;padding:1px;'>"
        << "<p>&#10071 Amount Should Be Positive.</p>";
    }
    else if (update_status == 2){
        body
        << "<br />"
        << "<div style='background-color:tomato;color:white;padding:1px;'>"
        << "<p>&#9989 Update Successful.</p>";
    }
    body
    << "</div>"
    << "<br />"
    << "</body>"
    << "</html>";
    return body.str();
}