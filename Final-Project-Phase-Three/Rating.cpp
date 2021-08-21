#include "Rating.hpp"
#include <iomanip>
#include <iostream>
using namespace std;
Rating::Rating(){
    is_empty = true;
}
Rating::Rating(string hotel_id_, double location_, double cleanliness_, double staff_,
                double facilities_, double value_, double overall_){
                    hotel_id = hotel_id_;
                    location = location_;
                    cleanliness = cleanliness_;
                    staff = staff_;
                    facilities = facilities_;
                    value = value_;
                    overall = overall_;
                    is_empty = false;
}
void Rating::show_rating(){
    if (is_empty){
        cout << NO_RATING_MSG << endl;
        return;
    }
    cout << fixed << setprecision(PRECISION) << "location: " << location << endl << "cleanliness: "
    << cleanliness << endl << "staff: " << staff << endl << "facilities: " << facilities << endl
    << "value_for_money: " << value << endl << "overall_rating: " << overall << endl;
}
void Rating::update (string hotel_id_, double location_, double cleanliness_, double staff_,
				double facilities_, double value_, double overall_){
                    hotel_id = hotel_id_;
                    location = location_;
                    cleanliness = cleanliness_;
                    staff = staff_;
                    facilities = facilities_;
                    value = value_;
                    overall = overall_;
                }