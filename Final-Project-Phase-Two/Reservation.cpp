#include "Reservation.hpp"
using namespace std;

Reservation::Reservation (int id_, std::string hotel_id_, std::string room_type_, int quantity_, double cost_,
                        int check_in_, int check_out_, std::vector <std::string> room_ids_){
                            id = id_;
                            hotel_id = hotel_id_;
                            room_type = room_type_;
                            quantity = quantity_;
                            cost = cost_;
                            check_in = check_in_;
                            check_out = check_out_;
                            room_ids = room_ids_;
                        }
void Reservation::print(){
    cout << "id: " << id << " hotel: " << hotel_id << " room: " << room_type << " quantity: " << quantity <<
    " cost: " << (int)cost << " check_in " << check_in << " check_out " << check_out << endl;
}
bool Reservation::same_id(int id_){
    return (id == id_);
}
