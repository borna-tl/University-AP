#ifndef REVIEW_H_
#define REVIEW_H_ "REVIEW_H_"

#include <string>

class Review
{
public:
    Review(const int id_, const int book_id_, const int user_id_, const int rating_,
            const std::string date_, const int number_of_likes_);
    int get_book_id();
    int get_rating();
    int get_user_id();
    int get_id();
    int get_number_of_likes();
    std::string get_date();

private:
    int id;
    int book_id;
    int user_id;
    int rating;
    std::string date;
    int number_of_likes;
};

#endif