#ifndef ENEMY_H
#define ENEMY_H_ "ENEMY_H_"

#include "Shot.hpp"
struct Player {
    int money;
    int life;
};

class Enemy {
public:
    Enemy ();
    Enemy (std::string img_file_, std::string last_movement_, Coordinate place_, float life_, float initial_speed_,
            float kill_prize_, float reach_end_loss_);
    Coordinate get_position ();
    std::string get_last_movement();
    void move_in_direction (std::string direction, float dt);
    void update_last_movement(std::string movement);
    void update_img (std::string new_img);
    void draw (Window* win);
    float get_speed ();
    bool is_dead ();
    void update_life (float damage);
    void add_player_money (Player& player);
    void reduce_player_life (Player& player);
    float distance_difference (Coordinate enemy_coordination);
    void update_speed (float time, float damage);
    bool finished_glue_time();
    void update_being_chased_by_glue_status(bool status);
    bool can_be_shot_by_glue();
    virtual bool not_the_same_type (std::string type_name) = 0;
    void update_flip_image(bool status);
private:
    std::string img_file;
    bool flip_img;
    std::string life_bar_img_file;
    std::string last_movement;
    Coordinate place;
    float life;
    float initial_speed;
    float current_speed;
    float glue_time;
    std::chrono::steady_clock::time_point last_hit_by_glue_time;
    float kill_prize;
    float reach_end_loss;
    float life_bar;
    bool is_being_chased_by_glue;
};

class Runner : public Enemy {
public:
    Runner (std::string img_file_, std::string last_movement_, Coordinate place_, float life_,
            float speed_, float kill_prize_,float reach_end_loss_);// : Enemy (img_file_,
            //last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){}
    bool not_the_same_type (std::string type_name);
private:

};

class Scrambler : public Enemy {
public:
    Scrambler (std::string img_file_, std::string last_movement_, Coordinate place_, float life_,
            float speed_, float kill_prize_,float reach_end_loss_);// : Enemy (img_file_,
            //last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){}
    bool not_the_same_type (std::string type_name);
private:

};

class Stubbornrunner : public Enemy {
public:
    Stubbornrunner (std::string img_file_, std::string last_movement_, Coordinate place_, float life_,
            float speed_, float kill_prize_,float reach_end_loss_);// : Enemy (img_file_,
            //last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){}
    bool not_the_same_type (std::string type_name);
private:

};

class Supertrooper : public Enemy {
public:
    Supertrooper (std::string img_file_, std::string last_movement_, Coordinate place_, float life_,
            float speed_, float kill_prize_,float reach_end_loss_);// : Enemy (img_file_,
            //last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){}
    bool not_the_same_type (std::string type_name);
private:

};



#endif