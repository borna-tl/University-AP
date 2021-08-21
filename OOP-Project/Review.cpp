#include "Review.hpp"
using namespace std;

Review::Review(const int id_, const int book_id_, const int user_id_, const int rating_,
                const string date_, const int number_of_likes_)
{
    id = id_;
    book_id = book_id_;
    user_id = user_id_;
    rating = rating_;
    date = date_;
    number_of_likes = number_of_likes_;
}
int Review::get_book_id() { return book_id; }
int Review::get_rating() { return rating; }
int Review::get_user_id() { return user_id; }
int Review::get_id() { return id; }
int Review::get_number_of_likes() { return number_of_likes; }
string Review::get_date() { return date; }
