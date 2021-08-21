#include "Room.hpp"
using namespace std;

Room::Room (string id_){
    id = id_;
    for (int i = 0; i < MONTH_DAYS; i++)
        reservation_id[i] = 0;
}
string Room::get_id(){return id;}
bool Room::is_rentable (string type, int check_in, int check_out){
    if (id[0] != type[0])
        return false;
    for (int i = check_in; i <= check_out; i++){
        if (reservation_id[i - 1])
            return false;
    }
    return true;
}
void Room::reserve_room(int reservation_id_, vector<string>& room_ids, int check_in, int check_out){
    for (int i = check_in; i <= check_out; i++)
        reservation_id[i - 1] = reservation_id_;
    room_ids.push_back(id);
}
void Room::free_room (int reservation_id_){
    for (int i = 0; i < MONTH_DAYS; i++){
        if (reservation_id[i] == reservation_id_)
            reservation_id[i] = 0;
    }
}

