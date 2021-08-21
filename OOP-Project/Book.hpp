#ifndef BOOK_H_
#define BOOK_H_ "BOOK_H_"
#define INITIAL 0
#include <string>
#include <vector>
#include "Review.hpp"
class Book
{
public:
    Book(const int id_, const std::string title_, const int author_id_, const std::string genre_);
    int get_id();
    std::string get_title();
    std::string get_genre();
    int get_author_id();
    void update_avg_rating(int new_rating);
    double get_avg_rating();
    double get_first_approach_rating();
    std::vector <Review>* get_reviews();
    void add_reviews(const int id, const int book_id, const int user_id,
                    const int rating, const std::string date, const int number_of_likes);
    void set_first_approach_rating(double rating);
private:
    int id;
    std::string title;
    int author_id;
    std::string genre;
    std::pair<double, int> avg_rating;
    double first_approach_rating;
    std::vector <Review> reviews;
};

#endif