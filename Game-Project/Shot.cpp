#include "Shot.hpp"

using namespace std;


Shot::Shot (string img_file_, float x_, float y_, float damage_){
    has_reached_enemy = true;
    img_file = img_file_;
    x = x_;
    y = y_;
    damage = damage_;
}
void Shot::update_coordination (Coordinate enemy_coordination, float shot_speed, float dt, Point tower_position){
    float distance = sqrt(pow((enemy_coordination.y - y), 2) + pow ((enemy_coordination.x - x), 2));
    float distance_x = (enemy_coordination.x - x);
    float distance_y = (enemy_coordination.y - y);
    x += shot_speed * dt * (distance_x / distance);
    y += shot_speed * dt * (distance_y / distance);
    if (abs(x - enemy_coordination.x) < shot_speed * dt && abs(y - enemy_coordination.y) < shot_speed * dt){
        x = FSQUARE_X + (tower_position.x * SQUARE_L) + (SQUARE_L / 2);
        y = FSQUARE_Y + (tower_position.y * SQUARE_L) + (SQUARE_L / 2);
        has_reached_enemy = true;
    }
}
void Shot::draw_shot (Window* win){
    win->draw_img(img_file, Rectangle(Point(x - SHOT_L / 2, y - SHOT_L / 2), SHOT_L, SHOT_L));
}
bool Shot::reached_enemy (){
    return has_reached_enemy;
}
void Shot::update_status (bool has_reached_enemy_){
    has_reached_enemy = has_reached_enemy_;
}
float Shot::get_shot_damage() {return damage;}
void Shot::reset_position(float x_, float y_){
    x = x_;
    y = y_;
}
void Shot::upgrade_shot_damage(float added_damage) {
    damage += added_damage;
}
