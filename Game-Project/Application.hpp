#ifndef APPLICATION_H
#define APPLICATION_H_ "APPLICATION_H_"
#include "Path.hpp"


class Application
{
public:
    Application (Points path_squares, std::chrono::steady_clock::time_point beginning_time_,
                    std::vector <std::string> waves_);
    void run();
private:
    Window* win;
    std::chrono::steady_clock::time_point beginning_time;
    Player player;
    Path path;
    Event last_event;
    int continue_game;
    std::vector <Tower*> towers;
    Point selected_square;
    void read_input();
    bool is_square_occupied (Point selected_square);
    Tower* tower_type(Point selected_square);
    void apply_event();
    void draw_towers (Window* win);
    void draw_player_setting (Window* win);
    void draw_board(Window* win, std::chrono::steady_clock::time_point beginning_time_);
};
void read_input(Points& path_squares, std::vector <std::string>& waves);

#endif
