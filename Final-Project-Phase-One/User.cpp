#include "User.hpp"
using namespace std;
User::User (string email_, string username_, string password_){
    email = email_;
    username = username_;
    password = myhash(password_);
    money = 0;
    balance.push_back(money);
    reservation_id = 1;
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

