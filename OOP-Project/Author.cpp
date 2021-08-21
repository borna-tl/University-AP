#include "Author.hpp"

using namespace std;

Author::Author(const int id_, const string name_, const string gender_, const string member_since_,
               const int year_of_birth_, const string place_of_birth_, const vector<string> genres_)
{
    id = id_;
    name = name_;
    gender = gender_;
    member_since = member_since_;
    year_of_birth = year_of_birth_;
    place_of_birth = place_of_birth_;
    genres = genres_;
}
int Author::get_id() { return id; }
string Author::get_name() { return name; }
string Author::get_gender() { return gender; }
string Author::get_member_since() { return member_since; }
int Author::get_year_of_birth() { return year_of_birth; }
string Author::get_place_of_birth() { return place_of_birth; }
vector<string> Author::get_genres() { return genres; }
vector<Book> *Author::get_authors_books() { return &authors_books; }
