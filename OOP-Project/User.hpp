#ifndef USER_H_
#define USER_H_ "USER_H_"
#include <string>
#include <vector>
#include "Author.hpp"
class User
{
public:
    User(const int id_, const int number_of_reviews_, const int totall_likes_,
         const std::string name_, const std::string place_of_birth_, const std::string member_since_,
         const std::vector<Author> favorite_authors_, const std::vector<std::string> favorite_genres_,
         const std::vector<Book> want_to_read_, const std::vector<Book> currently_reading_, 
         const std::vector<Book> read_);
    int get_id();
    std::vector<Book> *get_shelf(const std::string shelf_type);
    void increase_number_of_reviews();
    void increase_totall_likes(const int added_likes);
    void add_following_member(User *following_user);
    int get_number_of_reviews();
    int get_totall_likes();
    std::string get_name();
    std::string get_place_of_birth();
    std::string get_member_since();
    std::vector<std::string> get_favorite_genres();
    std::vector<Author> *get_favorite_authors();
    std::vector<User *> get_following();

private:
    int id;
    int number_of_reviews;
    int totall_likes;
    std::string name;
    std::string place_of_birth;
    std::string member_since;
    std::vector<Author> favorite_authors;
    std::vector<std::string> favorite_genres;
    std::vector<Book> want_to_read;
    std::vector<Book> currently_reading;
    std::vector<Book> read;
    std::vector<User *> following;
};

#endif