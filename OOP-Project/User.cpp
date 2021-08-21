#include "User.hpp"
#define WANT_TO_READ_STATUS "want_to_read"
#define CURRENTLY_READING_STATUS "currently_reading"
#define READ_STATUS "read"
using namespace std;

User::User(const int id_, const int number_of_reviews_, const int totall_likes_,
           const string name_, const string place_of_birth_, const string member_since_,
           const vector<Author> favorite_authors_, const vector<string> favorite_genres_,
           const vector<Book> want_to_read_, const vector<Book> currently_reading_, const vector<Book> read_)
{
    id = id_;
    number_of_reviews = number_of_reviews_;
    totall_likes = totall_likes_;
    name = name_;
    place_of_birth = place_of_birth_;
    member_since = member_since_;
    favorite_authors = favorite_authors_;
    favorite_genres = favorite_genres_;
    want_to_read = want_to_read_;
    currently_reading = currently_reading_;
    read = read_;
}
int User::get_id() { return id; }
vector<Book> *User::get_shelf(const string shelf_type)
{
    if (shelf_type == WANT_TO_READ_STATUS)
        return &want_to_read;
    else if (shelf_type == CURRENTLY_READING_STATUS)
        return &currently_reading;
    else if (shelf_type == READ_STATUS)
        return &read;
}
void User::increase_number_of_reviews()
{
    number_of_reviews++;
}
void User::increase_totall_likes(const int added_likes)
{
    totall_likes += added_likes;
}
void User::add_following_member(User *following_user)
{
    following.push_back(following_user);
}
int User::get_number_of_reviews() { return number_of_reviews; }
int User::get_totall_likes() { return totall_likes; }
string User::get_name() { return name; }
string User::get_place_of_birth() { return place_of_birth; }
string User::get_member_since() { return member_since; }
vector<string> User::get_favorite_genres() { return favorite_genres; }
vector<Author> *User::get_favorite_authors() { return &favorite_authors; }
vector<User *> User::get_following() { return following; }
