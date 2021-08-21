#include "Errors.hpp"
using namespace std;


const char* Permission_Error::what() const noexcept{
    return ("Permission Denied\n");
}

const char* Bad_Request_Error::what() const noexcept{
    return ("Bad Request\n");
}
const char* Not_Found_Error::what() const noexcept{
    return ("Not Found\n");
}
const char* Insufficient_Rating_Error::what() const noexcept{
    return ("Insufficient Ratings\n");
}