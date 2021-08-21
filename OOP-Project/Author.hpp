#ifndef AUTHOR_H_
#define AUTHOR_H_ "AUTHOR_H_"

#include "Book.hpp"
#include <string>
#include <vector>

class Author
{
public:
    Author(const int id_, const std::string name_, const std::string gender_, const std::string member_since_,
           const int year_of_birth_, const std::string place_of_birth_, const std::vector<std::string> genres_);
    int get_id();
    std::string get_name();
    std::string get_gender();
    std::string get_member_since();
    int get_year_of_birth();
    std::string get_place_of_birth();
    std::vector<std::string> get_genres();
    std::vector<Book> *get_authors_books();

private:
    int id;
    std::string name;
    std::string gender;
    std::string member_since;
    int year_of_birth;
    std::string place_of_birth;
    std::vector<std::string> genres;
    std::vector<Book> authors_books;
};

#endif