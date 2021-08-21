#include "ReadnPrint.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#define COLUMN_SEPARATOR ','
#define ELEMENT_SEPARATOR '$'
#define CREDIT_ACCURACY 6
using namespace std;

ifstream open_file(const string file_folder, const string file_name)
{
    stringstream file_location;
    file_location << "./" << file_folder << "/" << file_name << ".csv";
    ifstream csv_file(file_location.str());
    return csv_file;
}

void add_authors(Goodreads &my_goodreads, ifstream *authors_file)
{
    string input_line;
    getline(*authors_file, input_line);
    while (getline(*authors_file, input_line))
    {
        istringstream input(input_line);
        string id;
        string name;
        string gender;
        string member_since;
        string year_of_birth;
        string place_of_birth;
        vector<string> genres;
        getline(input, id, COLUMN_SEPARATOR);
        getline(input, name, COLUMN_SEPARATOR);
        getline(input, gender, COLUMN_SEPARATOR);
        getline(input, member_since, COLUMN_SEPARATOR);
        getline(input, year_of_birth, COLUMN_SEPARATOR);
        getline(input, place_of_birth, COLUMN_SEPARATOR);
        string vec_element;
        while (getline(input, vec_element, ELEMENT_SEPARATOR))
            genres.push_back(vec_element);
        my_goodreads.genre_sort(genres);
        my_goodreads.add_author(stoi(id), name, gender, member_since, stoi(year_of_birth), place_of_birth, genres);
    }
}

void add_books(Goodreads &my_goodreads, ifstream *books_file)
{
    string input_line;
    getline(*books_file, input_line);
    while (getline(*books_file, input_line))
    {
        istringstream input(input_line);
        string id;
        string title;
        string author_id;
        string genre;
        getline(input, id, COLUMN_SEPARATOR);
        getline(input, title, COLUMN_SEPARATOR);
        getline(input, author_id, COLUMN_SEPARATOR);
        getline(input, genre);
        my_goodreads.add_book(stoi(id), title, stoi(author_id), genre);
    }
}

void add_users(Goodreads &my_goodreads, ifstream *users_file)
{
    string input_line;
    getline(*users_file, input_line);
    while (getline(*users_file, input_line))
    {
        istringstream input(input_line);
        string id;
        string name;
        string place_of_birth;
        string member_since;
        vector<Author> favorite_authors;
        vector<string> favorite_genres;
        vector<Book> want_to_read;
        vector<Book> currently_reading;
        vector<Book> read;
        getline(input, id, COLUMN_SEPARATOR);
        getline(input, name, COLUMN_SEPARATOR);
        getline(input, place_of_birth, COLUMN_SEPARATOR);
        getline(input, member_since, COLUMN_SEPARATOR);
        string favorite_authors_column, favorite_genres_column,
            want_to_read_column, currently_reading_column, read_column, vec_element;
        getline(input, favorite_authors_column, COLUMN_SEPARATOR);
        getline(input, favorite_genres_column, COLUMN_SEPARATOR);
        getline(input, want_to_read_column, COLUMN_SEPARATOR);
        getline(input, currently_reading_column, COLUMN_SEPARATOR);
        getline(input, read_column, COLUMN_SEPARATOR);
        istringstream authors_element(favorite_authors_column), genres_element(favorite_genres_column),
            want_to_read_element(want_to_read_column), currently_reading_element(currently_reading_column),
            read_element(read_column);
        while (getline(authors_element, vec_element, ELEMENT_SEPARATOR))
            favorite_authors.push_back(my_goodreads.find_author_by_id(stoi(vec_element)));
        while (getline(genres_element, vec_element, ELEMENT_SEPARATOR))
            favorite_genres.push_back(vec_element);
        while (getline(want_to_read_element, vec_element, ELEMENT_SEPARATOR))
        {
            Book &users_book = my_goodreads.find_book_by_id(stoi(vec_element));
            want_to_read.push_back(users_book);
        }
        while (getline(currently_reading_element, vec_element, ELEMENT_SEPARATOR))
        {
            Book &users_book = my_goodreads.find_book_by_id(stoi(vec_element));
            currently_reading.push_back(users_book);
        }
        while (getline(read_element, vec_element, ELEMENT_SEPARATOR))
        {
            Book &users_book = my_goodreads.find_book_by_id(stoi(vec_element));
            read.push_back(users_book);
        }
        my_goodreads.genre_sort(favorite_genres);
        my_goodreads.author_sort(favorite_authors);
        my_goodreads.book_sort(want_to_read);
        my_goodreads.book_sort(currently_reading);
        my_goodreads.book_sort(read);
        my_goodreads.add_user(stoi(id), name, place_of_birth, member_since,
                            favorite_authors, favorite_genres, want_to_read, currently_reading, read);
    }
}

void add_reviews(Goodreads &my_goodreads, ifstream *reviews_file)
{
    string input_line;
    getline(*reviews_file, input_line);
    while (getline(*reviews_file, input_line))
    {
        istringstream input(input_line);
        string id;
        string book_id;
        string user_id;
        string rating;
        string date;
        string number_of_likes;
        getline(input, id, COLUMN_SEPARATOR);
        getline(input, book_id, COLUMN_SEPARATOR);
        getline(input, user_id, COLUMN_SEPARATOR);
        getline(input, rating, COLUMN_SEPARATOR);
        getline(input, date, COLUMN_SEPARATOR);
        getline(input, number_of_likes);
        my_goodreads.add_review(stoi(id), stoi(book_id), stoi(user_id), stoi(rating), date, stoi(number_of_likes));
        my_goodreads.update_book_rating(stoi(book_id), stoi(rating));
        Book& selected_book = my_goodreads.find_book_by_id(stoi(book_id));
        selected_book.add_reviews(stoi(id), stoi(book_id), stoi(user_id), stoi(rating), date, stoi(number_of_likes));
    }
}

void add_follow_edges(Goodreads &my_goodreads, ifstream *follow_edges_file)
{
    string input_line;
    getline(*follow_edges_file, input_line);
    while (getline(*follow_edges_file, input_line))
    {
        istringstream input(input_line);
        vector<int> following;
        vector<int> followers;
        string id, following_column, followers_column, vec_element;
        getline(input, id, COLUMN_SEPARATOR);
        getline(input, following_column, COLUMN_SEPARATOR);
        getline(input, followers_column, COLUMN_SEPARATOR);
        istringstream following_element(following_column), followers_element(followers_column);
        while (getline(following_element, vec_element, ELEMENT_SEPARATOR))
            following.push_back(stoi(vec_element));
        while (getline(followers_element, vec_element, ELEMENT_SEPARATOR))
            followers.push_back(stoi(vec_element));
        my_goodreads.add_follow_edge(stoi(id), following);
    }
}

void read_files(const string file_folder, Goodreads &my_goodreads)
{
    ifstream authors_file = open_file(file_folder, "authors");
    ifstream books_file = open_file(file_folder, "books");
    ifstream users_file = open_file(file_folder, "users");
    ifstream reviews_file = open_file(file_folder, "reviews");
    ifstream follow_edges_file = open_file(file_folder, "follow_edges");
    add_authors(my_goodreads, &authors_file);
    add_books(my_goodreads, &books_file);
    add_users(my_goodreads, &users_file);
    add_reviews(my_goodreads, &reviews_file);
    add_follow_edges(my_goodreads, &follow_edges_file);
    authors_file.close();
    books_file.close();
    users_file.close();
    reviews_file.close();
    follow_edges_file.close();
}

void print_answer(const string command, Goodreads &my_goodreads)
{
    if (command == "show_author_info")
    {
        string author_id;
        cin >> author_id;
        cout << my_goodreads.show_author_info(stoi(author_id));
    }
    else if (command == "show_sorted_shelf")
    {
        string user_id, shelf_type, genre;
        cin >> user_id >> shelf_type;
        char c = getchar();
        while ((c = getchar()) != '\n')
            genre += c;
        cout << my_goodreads.show_sorted_shelf(stoi(user_id), shelf_type, genre);
    }
    else if (command == "credit")
    {
        int user_id;
        cin >> user_id;
        cout << fixed << setprecision(CREDIT_ACCURACY) << my_goodreads.credit(user_id) << endl;
    }
    else if (command == "best_book")
    {
        cout << my_goodreads.best_book();
    }
    else if (command == "best_reviewer")
    {
        cout << my_goodreads.best_reviewer();
    }
    else if (command == "recommend_first_approach")
    {
        map<int, double> rating;
        int user_id;
        cin >> user_id;
        cout << my_goodreads.recommend_first_approach(user_id, rating);
    }
    else if (command == "recommend_second_approach")
    {
        map<int, double> rating;
        int user_id;
        cin >> user_id;
        cout << my_goodreads.recommend_second_approach(user_id, rating);
    }
}
