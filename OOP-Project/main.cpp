#include <iostream>
#include "GoodReads.hpp"
#include "ReadnPrint.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    Goodreads my_goodreads({});
    string command;
    read_files(argv[1], my_goodreads);
    while (cin >> command)
    {
        print_answer(command, my_goodreads);
    }
}