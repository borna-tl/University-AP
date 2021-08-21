#include "Application.hpp"
#include <iostream>
using namespace std;

int main()
{
    Points path_squares;
    vector <string> waves;
    read_input (path_squares, waves);
    auto beginning_time = chrono::steady_clock::now();
    Application fieldrunners (path_squares, beginning_time, waves);
    fieldrunners.run();
}