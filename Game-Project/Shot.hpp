#ifndef SHOT_H
#define SHOT_H_ "SHOT_H_"
#include "DefinesAndIncludes.hpp"

typedef std::vector <Point> Points;


struct Coordinate {
  float x;
  float y;
};

class Shot {
public:
    Shot (std::string img_file_, float x_, float y_, float damage_);
    void update_coordination (Coordinate enemy_coordination, float shot_speed, float dt, Point tower_position);
    void draw_shot (Window* win);
    bool reached_enemy ();
    void update_status (bool has_reached_enemy_);
    float get_shot_damage();
    void reset_position(float x_, float y_);
    void upgrade_shot_damage(float added_damage);
private:
    bool has_reached_enemy;
    std::string img_file;
    float x;
    float y;
    float damage;
};

#endif