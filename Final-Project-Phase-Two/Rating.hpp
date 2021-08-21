#ifndef RATING
#define RATING "RATING"
#define NO_RATING_MSG "No Rating"
#define PRECISION 2
#include <string>
#include <vector>

struct Rating{
	Rating(std::string hotel_id_, double location_, double cleanliness_, double staff_,
				double facilities_, double value_, double overall_);
	std::string hotel_id;
	double location;
	double cleanliness;
	double staff;
	double facilities;
	double value;
	double overall;
	bool is_empty;
	Rating();
	void show_rating();
	void update (std::string hotel_id_, double location_, double cleanliness_, double staff_,
				double facilities_, double value_, double overall_);
};



#endif