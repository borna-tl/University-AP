#include "Rating.hpp"
#include <iomanip>
#include <iostream>
using namespace std;
Rating::Rating(){}
void Rating::add(double location_, double cleanliness_, double staff_, double facilities_,
                double value_, double overall_, string username_){
    if (repetetive_user(username_)){
        find_pair(location, username_)->second = location_;
        find_pair(cleanliness, username_)->second = cleanliness_;
        find_pair(staff, username_)->second = staff_;
        find_pair(facilities, username_)->second = facilities_;
        find_pair(value, username_)->second = value_;
        find_pair(overall, username_)->second = overall_;
    }
    else{
        pair <string, double> l = make_pair(username_, location_);
        location.push_back(l);
        pair <string, double> c = make_pair(username_, cleanliness_);
        cleanliness.push_back(c);
        pair <string, double> s = make_pair(username_, staff_);
        staff.push_back(s);
        pair <string, double> f = make_pair(username_, facilities_);
        facilities.push_back(f);
        pair <string, double> v = make_pair(username_, value_);
        value.push_back(v);
        pair <string, double> o = make_pair(username_, overall_);
        overall.push_back(o);
    }
}
void Rating::show_rating(){
    if (location.size() * cleanliness.size() * staff.size() * facilities.size() * value.size() * overall.size() == 0){
        cout << NO_RATING_MSG << endl;
        return;
    }
    double l = calculate_avg (location);
    double c = calculate_avg (cleanliness);
    double s = calculate_avg (staff);
    double f = calculate_avg (facilities);
    double v = calculate_avg (value);
    double o = calculate_avg (overall);
    cout << fixed << setprecision(PRECISION) << "location: " << l << endl << "cleanliness: " << c << endl <<
    "staff: " << s << endl << "facilities: " << f << endl << "value for money: " << v << endl <<
    "overall rating: " << o << endl;
}
double Rating::calculate_avg (vector <pair<string, double>> vec){
    double sum = 0;
    for (auto x : vec)
        sum += x.second;
    return (sum / vec.size());
}

bool Rating::repetetive_user (string username){
    for (auto x : location){
        if (x.first == username)
            return true;
    }
    return false;
}
vector <pair<string, double>>::iterator Rating::find_pair (vector <pair<string, double>>& vec, string username_){
    auto it = vec.begin();
    for (it; it < vec.end(); it++)
        if ((*it).first == username_)
            return it;
}
