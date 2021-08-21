#ifndef HASH
#define HASH "HASH"
#include <iostream>
#include <functional>
#include <string>
static const size_t InitialFNV = 2166136261U;
static const size_t FNVMultiple = 16777619;

size_t myhash(const std::string &s);



#endif