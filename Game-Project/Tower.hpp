#ifndef TOWER_H
#define TOWER_H_ "TOWER_H_"
#include "Enemy.hpp"

void draw_square (Window* win, int x_square, int y_square, std::string image_file, bool flip_img);

int calc_reminder(int a, int b);


class Tower {
public:
    Tower();
    Tower (std::string img_file_, Point place_, float damage_, float loading_time_,
            float initial_cost_, float upgrade_cost_, float upgrade_added_damage_);
    void draw (Window* win);
    bool in_the_same_square (Point selected_square);
    virtual void update_angle(Enemy* enemy);
    virtual void shoot_enemy(Window* win, Enemy* enemy, std::vector <Enemy*> enemies);
    virtual bool target_in_range(std::vector <Enemy*> enemies);
    virtual Enemy* new_target (std::vector <Enemy*> enemies);
    bool has_shot_reached_enemy();
    Enemy* get_last_enemy_shot();
    bool can_shoot (std::chrono::steady_clock::time_point current_time);
    bool player_can_buy_tower (Player& player, std::string status);
    void update_has_shot_enemy_status (bool status);
    bool can_be_upgraded(Player& Player);
    virtual void upgrade_tower(Player& player);
    void sell_tower(Player& player);
    virtual void play_shot_sound(Window* win) = 0;
protected:
    std::string img_file;
    int image_index;
    bool flip_img;
    Point place;
    float range;
    Shot* shot;
    float damage;
    std::chrono::steady_clock::time_point last_enemy_shot_time;
    float upgrade_cost;
    float upgrade_added_damage;
    float refund_value;
    Enemy* last_enemy_shot;
private:
    float loading_time;
    float initial_cost;
};

class Gattling : public Tower {
public:
    Gattling();
    Gattling (std::string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
            float upgrade_cost_, float upgrade_added_damage_); //: Tower (img_file_, place_, damage_,
            //loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){};
    bool target_in_range(std::vector <Enemy*> enemies);
    Enemy* new_target (std::vector <Enemy*> enemies);
    void play_shot_sound(Window* win);
private:
    std::string gun_shot_png;
    
};

class Missile : public Tower {
public:
    Missile();
    Missile (std::string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
            float upgrade_cost_, float upgrade_added_damage_); //: Tower (img_file_, place_, damage_,
            //loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){};
    void shoot_enemy(Window* win, Enemy* enemy, std::vector <Enemy*> enemies);
    void play_shot_sound(Window* win);
private:
    std::string gun_shot_png;
};

class Tesla : public Tower {
public:
    Tesla();
    Tesla (std::string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
            float upgrade_cost_, float upgrade_added_damage_); //: Tower (img_file_, place_, damage_,
            //loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){};
    void update_angle(Enemy* enemy);
    void play_shot_sound(Window* win);
private:
    std::string gun_shot_png;
};

class Glue : public Tower {
public:
    Glue();
    Glue (std::string img_file_, Point place_, float damage_, float damage_time_, float loading_time_, float initial_cost_,
            float upgrade_cost_, float upgrade_added_damage_, float upgrade_added_damage_time_);// : Tower (img_file_, place_,
            //damage_, loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){};
    void shoot_enemy (Window* win, Enemy* enemy, std::vector <Enemy*> enemies);
    bool target_in_range (std::vector <Enemy*> enemies);
    void upgrade_tower(Player& player);
    Enemy* new_target (std::vector <Enemy*> enemies);
    void play_shot_sound(Window* win);
private:
    std::string gun_shot_png;
    float damage_time;
    float upgrade_added_damage_time;
           
};

#endif