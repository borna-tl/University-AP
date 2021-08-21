#include "GoodReads.hpp"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#define INITIAL 0
#define CREDIT_ACCURACY 6
#define FAV_GENRE_SCORE 5
#define NOT_FAV_GENRE_SCORE 0
#define MAX_READ_BOOKS 3
#define AVERAGE_ACCURACY 2
using namespace std;

Goodreads::Goodreads(vector<Author> Authors_)
{
    Authors = Authors_;
}
void Goodreads::add_author(const int id_, const string name_, const string gender_, const string member_since_,
                           const int year_of_birth_, const string place_of_birth_, const vector<string> genres_)
{
    Authors.push_back(Author(id_, name_, gender_, member_since_, year_of_birth_, place_of_birth_, genres_));
}
string Goodreads::show_author_info(const int author_id)
{
    ostringstream os;
    Author &wanted_author = find_author_by_id(author_id);
    os << "id: " << wanted_author.get_id() << endl
       << "Name: " << wanted_author.get_name() << endl
       << "Year of Birth: " << wanted_author.get_year_of_birth() << endl
       << "Place of Birth: " << wanted_author.get_place_of_birth() << endl
       << "Member Since: " << wanted_author.get_member_since() << endl
       << "Genres: ";
    for (int i = 0; i < wanted_author.get_genres().size(); i++)
    {
        os << wanted_author.get_genres()[i];
        if (i != wanted_author.get_genres().size() - 1)
            os << ", ";
    }
    os << endl
       << "Books:" << endl;
    book_sort(*wanted_author.get_authors_books());
    for (auto book_title : (*wanted_author.get_authors_books()))
    {
        os << "id: " << book_title.get_id()
           << " Title: " << book_title.get_title() << endl;
    }
    return os.str();
}
string Goodreads::show_sorted_shelf(const int user_id, const string shelf_type, const string genre)
{
    ostringstream os;
    User &wanted_user = find_user_by_id(user_id);
    vector<Book> *shelf = wanted_user.get_shelf(shelf_type);
    lexicographical_sort(shelf, genre);
    for (auto book : *shelf)
    {
        os << "id: " << book.get_id() << endl
           << "Title: " << book.get_title() << endl
           << "Genre: " << book.get_genre() << endl
           << "Author: " << (Author(find_author_by_id(book.get_author_id()))).get_name() << endl
           << "***\n";
    }
    return os.str();
}
void Goodreads::add_book(const int id_, const string title_, const int author_id_, const string genre_)
{
    Author &wanted_author = find_author_by_id(author_id_);
    (*wanted_author.get_authors_books()).push_back(Book(id_, title_, author_id_, genre_));
    Books.push_back(Book(id_, title_, author_id_, genre_));
}
void Goodreads::add_user(const int id_, const string name_, const string place_of_birth_, 
                        const string member_since_, const vector<Author> favorite_authors_, 
                        const vector<string> favorite_genres_, const vector<Book> want_to_read_,
                        const vector<Book> currently_reading_, const vector<Book> read_)
{
    Users.push_back(User(id_, INITIAL, INITIAL, name_, place_of_birth_, member_since_,
                         favorite_authors_, favorite_genres_,
                         want_to_read_, currently_reading_, read_));
}
void Goodreads::add_review(const int id_, const int book_id_, const int user_id_, const int rating_,
                            const string date_, const int number_of_likes_)
{
    Reviews.push_back(Review(id_, book_id_, user_id_, rating_, date_, number_of_likes_));
    User &wanted_user = find_user_by_id(user_id_);
    wanted_user.increase_number_of_reviews();
    wanted_user.increase_totall_likes(number_of_likes_);
}
void Goodreads::add_follow_edge(const int id_, const vector<int> following_)
{
    User *wanted_user = &(find_user_by_id(id_));
    for (auto user_id : following_)
    {
        User *following_user = &(find_user_by_id(user_id));
        (*wanted_user).add_following_member(following_user);
    }
}
double Goodreads::credit(const int user_id)
{
    User &wanted_user = find_user_by_id(user_id);
    double credit_reviews = (double)calc_reviews_number() == 0 ? 
    0 : (double)(wanted_user.get_number_of_reviews() / (double)calc_reviews_number());
    double credit_likes = (double)calc_likes_number() == 0 ? 
    0 : ((double)wanted_user.get_totall_likes() / (double)calc_likes_number());
    return (credit_reviews + credit_likes) / 2;
}
void Goodreads::update_book_rating(const int book_id, const int rating)
{
    Book &wanted_book = find_book_by_id(book_id);
    wanted_book.update_avg_rating(rating);
}
string Goodreads::best_book()
{
    ostringstream os;
    double best_rating;
    for (auto &book : Books)
    {
        if (book.get_avg_rating() > best_rating)
            best_rating = book.get_avg_rating();
    }
    for (auto &book : Books)
    {
        if (book.get_avg_rating() == best_rating)
        {
            os << "id: " << book.get_id() << endl
                << "Title: " << book.get_title() << endl
                << "Genre: " << book.get_genre() << endl
                << "Author: " << find_author_by_id(book.get_author_id()).get_name() << endl
                << "Average Rating: " << fixed << setprecision(AVERAGE_ACCURACY) << best_rating << endl;
            break;
        }
    }
    return os.str();
}
string Goodreads::best_reviewer()
{
    ostringstream os;
    int most_likes = 0;
    for (auto &user : Users)
    {
        if (user.get_totall_likes() > most_likes)
            most_likes = user.get_totall_likes();
    }
    for (auto &user : Users)
    {
        if (user.get_totall_likes() == most_likes)
        {
            os << "id: " << user.get_id() << endl
               << "Name: " << user.get_name() << endl
               << "Place of Birth: " << user.get_place_of_birth() << endl
               << "Member Since: " << user.get_member_since() << endl
               << "Favorite Genres: " << user.get_favorite_genres()[0];
            for (int i = 1; i < user.get_favorite_genres().size(); i++)
                os << ", " << user.get_favorite_genres()[i];
            os << endl
               << "Favorite Authors: " << (*user.get_favorite_authors())[0].get_name();
            for (int i = 1; i < (*user.get_favorite_authors()).size(); i++)
                os << ", " << (*user.get_favorite_authors())[i].get_name();
            os << endl
               << "Number of Books in Read Shelf: " << (*user.get_shelf("read")).size() << endl
               << "Number of Books in Want to Read Shelf: " << (*user.get_shelf("want_to_read")).size() << endl
               << "Number of Books in Currently Reading Shelf: " << (*user.get_shelf("currently_reading")).size() << endl
               << "Number of Likes: " << most_likes << endl;
        }
    }
    return os.str();
}
Book &Goodreads::find_book_by_id(const int book_id)
{
    for (auto &book : Books)
    {
        if (book.get_id() == book_id)
            return book;
    }
}
Author &Goodreads::find_author_by_id(const int author_id)
{
    for (auto &author : Authors)
    {
        if (author.get_id() == author_id)
            return author;
    }
}

double Goodreads::map_highest_value (map <int, double> &rating)
{
    double max_val = 0;
    for (auto &rate : rating)
    {
        if (rate.second > max_val)
            max_val = rate.second;
    }
    return max_val;
}
Book &Goodreads::recommend_first_approach_book(map<int, double> &rating)
{
    double max_rating = map_highest_value (rating); 
    for (auto &rate : rating)
    {
        if (rate.second == max_rating)
            return (find_book_by_id(rate.first));
    }
}
void Goodreads::set_books_first_approach_rating(const int user_id, map<int, double> &rating)
{
    for (auto &book : Books)
    {
        double book_overall_rating = 0.0;
        int review_count = 0;
        for (auto &book_review : (*book.get_reviews()))
        {
            book_overall_rating += (book_review.get_rating() * credit(book_review.get_user_id()));
            review_count++;
        }
        book_overall_rating /= review_count;
        book.set_first_approach_rating(book_overall_rating);
        rating.insert(pair <int, double> (book.get_id(), book_overall_rating
        + is_favorite_genre(find_user_by_id(user_id), book.get_genre())));
    }
}
string Goodreads::recommend_first_approach(const int user_id, map<int, double> &rating)
{
    ostringstream os;
    set_books_first_approach_rating(user_id, rating);
    Book &selected_book = recommend_first_approach_book(rating);
    os << "id: " << selected_book.get_id() << endl
       << "Title: " << selected_book.get_title() << endl
       << "Genre: " << selected_book.get_genre() << endl
       << "Author: " << find_author_by_id(selected_book.get_author_id()).get_name() << endl
       << "Reviews:" << endl;
    for (auto review : (*selected_book.get_reviews()))
    {
        os << "id: " << review.get_id() << " Rating: " << review.get_rating() 
           << " Likes: " << review.get_number_of_likes() << " Date: " << review.get_date() << endl;
    }
    return os.str();
}
int Goodreads::count_repetition(Book &current_book, vector<Book> &best_books)
{
    int count = 0;
    for (auto &book : best_books)
    {
        if (book.get_id() == current_book.get_id())
            count++;
    }
    return count;
}
Book Goodreads::top_book(vector<Book> &best_books)
{
    int highest_repetition = 0;
    for (auto &book : best_books)
    {
        int n = count_repetition(book, best_books);
        if (n > highest_repetition)
            highest_repetition = n;
    }
    vector<Book> most_common_books;
    for (auto &book : best_books)
    {
        if (count_repetition(book, best_books) == highest_repetition)
            most_common_books.push_back(book);
    }
    book_sort(most_common_books);
    return most_common_books[0];
}
void Goodreads::recommend_top_books(User &current_user, int chosen_count,
                                    vector<Book> &best_books, map<int, double> &rating)
{
    multimap<double, Book &> book_shelf;
    for (auto &users_book : (*current_user.get_shelf("read")))
    {
        double overall_rating = rating.find(users_book.get_id())->second;
        book_shelf.insert(pair<double, Book &>(overall_rating, users_book));
    }
    for (auto i = book_shelf.rbegin(); i != book_shelf.rend() && chosen_count > 0; ++i)
    {
        best_books.push_back(i->second);
        chosen_count--;
    }
}
void Goodreads::recommend_second_approach_book(User &current_user, vector<Book> &best_books,
                                               map<int, double> &rating, vector<int> &seen_users)
{
    if (find(seen_users.begin(), seen_users.end(), current_user.get_id()) != seen_users.end())
    {
        return;
    }
    seen_users.push_back(current_user.get_id());
    for (auto &following_user : current_user.get_following())
    {
        recommend_second_approach_book(*following_user, best_books, rating, seen_users);
    }
    int chosen_count = (*current_user.get_shelf("read")).size();
    if (chosen_count > MAX_READ_BOOKS)
        chosen_count = MAX_READ_BOOKS;
    recommend_top_books(current_user, chosen_count, best_books, rating);
}
string Goodreads::recommend_second_approach(const int user_id, map<int, double> &rating)
{
    ostringstream os;
    vector<Book> best_books;
    vector<int> seen_users;
    User &wanted_user = find_user_by_id(user_id);
    set_books_first_approach_rating(user_id, rating);
    recommend_second_approach_book(wanted_user, best_books, rating, seen_users);
    Book selected_book = top_book(best_books);
    os << "id: " << selected_book.get_id() << endl
       << "Title: " << selected_book.get_title() << endl
       << "Genre: " << selected_book.get_genre() << endl
       << "Author: " << find_author_by_id(selected_book.get_author_id()).get_name() << endl
       << "Reviews:" << endl;
    for (auto &review : Reviews)
    {
        if (review.get_book_id() == selected_book.get_id())
        {
            os << "id: " << review.get_id() << " Rating: " << review.get_rating()
               << " Likes: " << review.get_number_of_likes() << " Date: " << review.get_date() << endl;
        }
    }
    return os.str();
}
bool Goodreads::compare_genres(const string genre_1, const string genre_2)
{
    return (genre_1 <= genre_2);
}
void Goodreads::genre_sort(vector<string> &genres)
{
    for (int i = 0; i < genres.size(); i++)
        for (int j = i + 1; j < genres.size(); j++)
            if (!compare_genres(genres[i], genres[j]))
                swap(genres[i], genres[j]);
}
bool Goodreads::compare_authors(Author author_1, Author author_2)
{
    return (author_1.get_id() < author_2.get_id());
}
void Goodreads::author_sort(vector<Author> &authors)
{
    for (int i = 0; i < authors.size(); i++)
        for (int j = i + 1; j < authors.size(); j++)
            if (!compare_authors(authors[i], authors[j]))
                swap(authors[i], authors[j]);
}
bool Goodreads::compare_books(Book book_1, Book book_2, string genre)
{
    if (book_1.get_genre() != book_2.get_genre())
    {
        if (book_1.get_genre() == genre)
        {
            return true;
        }
        else if (book_2.get_genre() == genre)
        {
            return false;
        }
    }
    if (book_1.get_title() == book_2.get_title())
        return (book_1.get_id() < book_2.get_id());
    return (book_1.get_title() < book_2.get_title());
}
void Goodreads::lexicographical_sort(vector<Book> *books, const string genre)
{
    for (int i = 0; i < (*books).size(); i++)
    {
        for (int j = i + 1; j < (*books).size(); j++)
        {
            if (!compare_books((*books)[i], (*books)[j], genre))
            {
                swap((*books)[i], (*books)[j]);
            }
        }
    }
}
bool Goodreads::compare_books(Book book_1, Book book_2)
{
    return (book_1.get_id() < book_2.get_id());
}
void Goodreads::book_sort(vector<Book> &books)
{
    for (int i = 0; i < books.size(); i++)
        for (int j = i + 1; j < books.size(); j++)
            if (!compare_books(books[i], books[j]))
                swap(books[i], books[j]);
}
User &Goodreads::find_user_by_id(const int user_id)
{
    for (auto &user : Users)
    {
        if (user.get_id() == user_id)
            return user;
    }
}
int Goodreads::calc_reviews_number()
{
    int totall_reviews = 0;
    for (auto &review_count : Users)
        totall_reviews += review_count.get_number_of_reviews();
    return totall_reviews;
}
int Goodreads::calc_likes_number()
{
    int totall_likes = 0;
    for (auto &like_count : Users)
        totall_likes += like_count.get_totall_likes();
    return totall_likes;
}
double Goodreads::max_first_approach_score(const int user_id)
{
    User &wanted_user = find_user_by_id(user_id);
    double max_rating = INITIAL;
    for (auto &book : Books)
    {
        if ((book.get_first_approach_rating() + is_favorite_genre(wanted_user, book.get_genre())) > max_rating)
           max_rating = (book.get_first_approach_rating() + is_favorite_genre(wanted_user, book.get_genre()));
    }
    return max_rating;
}
int Goodreads::is_favorite_genre(User &wanted_user, string const genre)
{
    for (auto &user_favorite_genre : wanted_user.get_favorite_genres())
    {
        if (user_favorite_genre == genre)
            return FAV_GENRE_SCORE;
    }
    return NOT_FAV_GENRE_SCORE;
}