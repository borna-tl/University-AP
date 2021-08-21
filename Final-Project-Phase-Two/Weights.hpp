#ifndef WEIGHTS
#define WEIGHTS "WEIGHTS"
#include "Hash.hpp"
#include <iomanip>
struct Weights{
    Weights();
    bool is_on;
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double value_for_money;
    void update_status(bool status);
    void update_weights(double location_, double cleanliness_, double staff_, double facilities_, double value_for_money_);
    void show();
};

#endif