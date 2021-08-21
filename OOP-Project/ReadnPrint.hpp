#ifndef READNPRINT_H_
#define READNPRINT_H_ "READNPRINT_H_"
#include "GoodReads.hpp"
#include <fstream>

std::ifstream open_file(const std::string file_folder, const std::string file_name);
void add_authors(Goodreads &my_goodreads, std::ifstream *authors_file);
void add_books(Goodreads &my_goodreads, std::ifstream *books_file);
void add_users(Goodreads &my_goodreads, std::ifstream *users_file);
void add_reviews(Goodreads &my_goodreads, std::ifstream *reviews_file);
void add_follow_edges(Goodreads &my_goodreads, std::ifstream *follow_edges_file);
void read_files(const std::string file_folder, Goodreads &my_goodreads);
void print_answer(const std::string command, Goodreads &my_goodreads);

#endif