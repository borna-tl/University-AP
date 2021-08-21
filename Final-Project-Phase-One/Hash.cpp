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

