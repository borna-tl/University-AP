#include "Hash.hpp"
using namespace std;

size_t myhash(const string &s) {
	size_t hash = InitialFNV;
	for(size_t i = 0; i < s.length(); i++) {
		hash = hash ^ (s[i]);
		hash = hash * FNVMultiple;
	}
	return hash;
}

double cut_leading_decimals(double number, int decimal_count){
	return (double)((int)(pow(10, decimal_count) * number)) / pow(10, decimal_count); 
}
