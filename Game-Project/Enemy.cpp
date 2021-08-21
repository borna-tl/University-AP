#include "Enemy.hpp"

using namespace std;


Enemy::Enemy (){}
Enemy::Enemy (string img_file_, string last_movement_, Coordinate place_, float life_, float initial_speed_,
        float kill_prize_, float reach_end_loss_){
    img_file = img_file_;
    flip_img = false;
    life_bar_img_file = LIFE_BAR_IMG_PNG;
    last_movement = last_movement_;
    place = place_;
    life = life_;
    initial_speed = initial_speed_;
    current_speed = initial_speed_;
    kill_prize = kill_prize_;
    reach_end_loss = reach_end_loss_;
    life_bar = life;
    last_hit_by_glue_time = chrono::steady_clock::now();
    is_being_chased_by_glue = false;
}
Coordinate Enemy::get_position (){return place;}
string Enemy::get_last_movement(){return last_movement;}
void Enemy::move_in_direction (string direction, float dt){
    chrono::steady_clock::time_point current_time;
    current_time = chrono::steady_clock::now();
    chrono::duration<float> passed_seconds = current_time - last_hit_by_glue_time;
    if (passed_seconds.count() > glue_time){
        current_speed = initial_speed;
    }
    last_movement = direction;
    if (direction == RIGHT_DIRECTION){
        place.x += dt * current_speed;
    }
    else if (direction == LEFT_DIRECTION){
        place.x -= dt * current_speed;
    }
    else if (direction == DOWN_DIRECTION){
        place.y += dt * current_speed;
    }
    else if (direction == UP_DIRECTION){
        place.y -= dt * current_speed;
    }
}
void Enemy::update_last_movement(string movement){
    last_movement = movement;
}
void Enemy::update_img (string new_img){
    img_file = new_img;
}
void Enemy::draw (Window* win){
    if (flip_img){
        win->draw_img(img_file, Rectangle(Point(place.x - (SQUARE_L / 2), place.y - (SQUARE_L / 2)), SQUARE_L, SQUARE_L), NULL_RECT, 0, true, false);
    }
    else {
        win->draw_img(img_file, Rectangle(Point(place.x - (SQUARE_L / 2), place.y - (SQUARE_L / 2)), SQUARE_L, SQUARE_L));
    }
    win->draw_img(life_bar_img_file, Rectangle(Point(place.x - (SQUARE_L / 2) , place.y - (SQUARE_L / 2) - 5),
                    (life_bar / life * SQUARE_L), 5));
}
float Enemy::get_speed (){return current_speed;}
bool Enemy::is_dead () {
    return (life_bar <= 0);
}
void Enemy::update_life (float damage){
    life_bar -= damage;
}
void Enemy::add_player_money (Player& player){
    player.money += kill_prize;
}
void Enemy::reduce_player_life (Player& player){
    player.life -= reach_end_loss;
}
float Enemy::distance_difference (Coordinate enemy_coordination) {
    return sqrt( pow((place.x - enemy_coordination.x), 2) + pow((place.y - enemy_coordination.y), 2));
}
void Enemy::update_speed (float time, float damage){
    last_hit_by_glue_time = chrono::steady_clock::now();
    glue_time = time;
    current_speed = initial_speed * (1 - damage);
}
bool Enemy::finished_glue_time(){
    chrono::steady_clock::time_point current_time;
    current_time = chrono::steady_clock::now();
    chrono::duration<float> passed_seconds = current_time - last_hit_by_glue_time;
    return (passed_seconds.count() >= glue_time);
}
void Enemy::update_being_chased_by_glue_status(bool status){
    is_being_chased_by_glue = status;
}

bool Enemy::can_be_shot_by_glue(){
    return !is_being_chased_by_glue;
}

void Enemy::update_flip_image(bool status){
    flip_img = status;
}

Runner::Runner (string img_file_, string last_movement_, Coordinate place_, float life_,
        float speed_, float kill_prize_,float reach_end_loss_) : Enemy (img_file_,
        last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){

    }
bool Runner::not_the_same_type (string type_name) {
    if (type_name == RUNNER_TYPE){
        return false;
    }
    return true;
}


Scrambler::Scrambler (string img_file_, string last_movement_, Coordinate place_, float life_,
        float speed_, float kill_prize_,float reach_end_loss_) : Enemy (img_file_,
        last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){

    }
bool Scrambler::not_the_same_type (string type_name) {
    if (type_name == SCRAMBLER_TYPE){
        return false;
    }
    return true;
}

Stubbornrunner::Stubbornrunner (string img_file_, string last_movement_, Coordinate place_, float life_,
        float speed_, float kill_prize_,float reach_end_loss_) : Enemy (img_file_,
        last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){

    }
bool Stubbornrunner::not_the_same_type (string type_name) {
    if (type_name == STUBBORNRUNNER_TYPE){
        return false;
    }
    return true;
}


Supertrooper::Supertrooper (string img_file_, string last_movement_, Coordinate place_, float life_,
        float speed_, float kill_prize_,float reach_end_loss_) : Enemy (img_file_,
        last_movement_, place_, life_, speed_, kill_prize_, reach_end_loss_){

    }
bool Supertrooper::not_the_same_type (string type_name) {
    if (type_name == SUPERTROOPER_TYPE){
        return false;
    }
    return true;
}
