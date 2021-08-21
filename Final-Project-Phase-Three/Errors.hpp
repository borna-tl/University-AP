#ifndef ERRORS
#define ERRORS "ERRORS"
#include <iostream>
#include <exception>

class Permission_Error : public std::exception{
public:
    const char* what() const noexcept;
};
class Bad_Request_Error : public std::exception{
public:
    const char* what() const noexcept;
};
class Not_Found_Error : public std::exception{
public:
    const char* what() const noexcept;
};
class Insufficient_Rating_Error : public std::exception{
public:
    const char* what() const noexcept;
};


#endif