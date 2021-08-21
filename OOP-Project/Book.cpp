#include "Book.hpp"

using namespace std;

Book::Book(const int id_, const string title_, const int author_id_, const string genre_)
{
    id = id_;
    title = title_;
    author_id = author_id_;
    genre = genre_;
    avg_rating = {INITIAL, INITIAL};
}
int Book::get_id() { return id; }
string Book::get_title() { return title; }
string Book::get_genre() { return genre; }
int Book::get_author_id() { return author_id; }
void Book::update_avg_rating(const int new_rating)
{
    avg_rating.first = (avg_rating.first * avg_rating.second + new_rating) / (avg_rating.second + 1);
    avg_rating.second++;
}
double Book::get_avg_rating() { return avg_rating.first; }
double Book::get_first_approach_rating() { return first_approach_rating;}
void Book::set_first_approach_rating(double rating) {first_approach_rating = rating;}
vector <Review>* Book::get_reviews()
{
    return &reviews;
}
void Book::add_reviews(const int id, const int book_id, const int user_id,
                    const int rating, const string date, const int number_of_likes){
    reviews.push_back(Review(id, book_id, user_id, rating, date, number_of_likes));
}