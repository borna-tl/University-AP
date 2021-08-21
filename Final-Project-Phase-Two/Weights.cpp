#include "Weights.hpp"
#include <iostream>
using namespace std;
Weights::Weights(){
    is_on = false;
}
void Weights::update_status(bool status){
    is_on = status;
}
void Weights::update_weights(double location_, double cleanliness_, double staff_, double facilities_, double value_for_money_){
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    value_for_money = value_for_money_;
}
void Weights::show(){
    if (is_on == false){
        cout << "active false" << endl;
    }
    else{
        cout << fixed << setprecision(PRECISION) << "active true location " <<
        cut_leading_decimals(location, PRECISION) << " cleanliness " <<
        cut_leading_decimals(cleanliness, PRECISION) << " staff " <<
        cut_leading_decimals(staff, PRECISION) << " facilities " <<
        cut_leading_decimals(facilities, PRECISION) << " value_for_money " <<
        cut_leading_decimals(value_for_money, PRECISION) << endl;
    }
}