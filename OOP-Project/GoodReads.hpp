#ifndef GOODREADS_H_
#define GOODREADS_H_ "GOODREADS_H_"
#include <vector>
#include <string>
#include <map>
#include "Review.hpp"
#include "Author.hpp"
#include "User.hpp"
class Goodreads
{
public:
    Goodreads(std::vector<Author> Authors_);
    void add_author(const int id_, const std::string name_, const std::string gender_, 
                    const std::string member_since_, const int year_of_birth_,
                    const std::string place_of_birth_, const std::vector<std::string> genres_);
    std::string show_author_info(const int author_id);
    std::string show_sorted_shelf(const int user_id, const std::string shelf_type, const std::string genre);
    void add_book(const int id_, const std::string title_, const int author_id_, const std::string genre_);
    void add_user(const int id_, const std::string name_, const std::string place_of_birth_,
                const std::string member_since_, const std::vector<Author> favorite_authors_,
                const std::vector<std::string> favorite_genres_, const std::vector<Book> want_to_read_,
                const std::vector<Book> currently_reading_, const std::vector<Book> read_);
    void add_review(const int id_, const int book_id_, const int user_id_, const int rating_,
                    const std::string date_, const int number_of_likes_);
    void add_follow_edge(const int id_, const std::vector<int> following_);
    double credit(const int user_id);
    void update_book_rating(const int book_id, const int rating);
    std::string best_book();
    std::string best_reviewer();
    Book &find_book_by_id(const int book_id);
    Author &find_author_by_id(const int author_id);
    double map_highest_value (std::map <int, double> &rating);
    Book &recommend_first_approach_book (std::map<int, double> &rating);
    void set_books_first_approach_rating(const int user_id, std::map<int, double> &rating);
    std::string recommend_first_approach(const int user_id, std::map<int, double> &rating);
    int count_repetition(Book &current_book, std::vector<Book> &best_books);
    Book top_book(std::vector<Book> &best_books);
    void recommend_top_books(User &current_user, int chosen_count,
                            std::vector<Book> &best_books, std::map<int, double> &rating);
    void recommend_second_approach_book(User &current_user, std::vector<Book> &best_books,
                                        std::map<int, double> &rating, std::vector<int> &seen_users);
    std::string recommend_second_approach(const int user_id, std::map<int, double> &rating);
    bool compare_genres(const std::string genre_1, const std::string genre_2);
    void genre_sort(std::vector<std::string> &genres);
    bool compare_authors(Author author_1, Author author_2);
    void author_sort(std::vector<Author> &authors);
    bool compare_books(Book book_1, Book book_2, std::string genre);
    void lexicographical_sort(std::vector<Book> *books, const std::string genre);
    bool compare_books(Book book_1, Book book_2);
    void book_sort(std::vector<Book> &books);
private:
    std::vector <Author> Authors;
    std::vector <User> Users;
    std::vector <Book> Books;
    User &find_user_by_id(const int user_id);
    std::vector<Review> Reviews;
    int calc_reviews_number();
    int calc_likes_number();
    double max_first_approach_score(const int user_id);
    int is_favorite_genre(User &wanted_user, const std::string genre);
};

#endif