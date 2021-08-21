#ifndef ROOM
#define ROOM "ROOM"
#include <string>
#include <vector>
#define MONTH_DAYS 30
class Room{
public:
	Room (std::string id_);
	std::string get_id();
	bool is_rentable (std::string type, int check_in, int check_out);
	void reserve_room(int reservation_id_, std::vector<std::string>& room_ids, int check_in, int check_out);
	void free_room (int reservation_id_);
private:
	std::string id;
	int reservation_id[MONTH_DAYS];
};

struct Num_Room_Types {
	int num_standard_rooms;
	int num_deluxe_rooms;
	int num_luxury_rooms;
	int num_premium_rooms;
};
struct Price_Room_Types {
	int price_standard_rooms;
	int price_deluxe_rooms;
	int price_luxury_rooms;
	int price_premium_rooms;
};



#endif