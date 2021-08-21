#ifndef PATH_H
#define PATH_H_ "PATH_H_"

#include "Tower.hpp"

class Path
{
public:
    Path ();
    void draw_path (Window* win);
    void draw_path_with_effects (Window* win);
    void draw_enemies (Window* win, float seconds);
    void draw_shooting (Window* win, std::vector <Tower*> towers, std::chrono::steady_clock::time_point current_time);
    void update_path (Points path_squares, std::vector <std::string> waves_);
    bool is_square_in_path(Point selected_square);
    Coordinate get_square_center (Coordinate place);
    std::string next_direction (Enemy* enemy);
    void move_single_enemy (Enemy* enemy, Player& player, int& continue_game);
    void move_enemies (std::chrono::steady_clock::time_point& beginning_time_, Player& player, int& continue_game);
    Points get_path();
    void build_wave (std::string wave);
private:
    Points path_way;
    std::vector <std::string> path_direction;
    std::vector <Enemy*> enemies;
    std::vector <std::string> waves;
    int wave_number;
    void construct_path (Points path_squares);
};

#endif