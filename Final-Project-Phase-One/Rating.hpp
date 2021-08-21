#ifndef RATING
#define RATING "RATING"
#define NO_RATING_MSG "No Rating"
#define PRECISION 2
#include <string>
#include <vector>
class Rating{
public:
	Rating();
	void add(double location_, double cleanliness_, double staff_, double facilities_,
					double value_, double overall_, std::string username_);
	void show_rating();
	double calculate_avg (std::vector <std::pair<std::string, double>> vec);
private:
	std::vector <std::pair<std::string, double>> location;
	std::vector <std::pair<std::string, double>> cleanliness;
	std::vector <std::pair<std::string, double>> staff;
	std::vector <std::pair<std::string, double>> facilities;
	std::vector <std::pair<std::string, double>> value;
	std::vector <std::pair<std::string, double>> overall;
	bool repetetive_user (std::string username);
	std::vector <std::pair<std::string, double>>::iterator find_pair
            (std::vector <std::pair<std::string, double>>& vec, std::string username_);
};



#endif