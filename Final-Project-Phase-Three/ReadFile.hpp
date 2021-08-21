#ifndef READFILE
#define READFILE "READFILE"
#include "Application.hpp"
#include <fstream>
#include <sstream>
#define SEPERATION_CHAR ','
void read_hotels_file(std::string file_path, Application& utrip);
void read_ratings_file(std::string file_path, Application& utrip);
#endif