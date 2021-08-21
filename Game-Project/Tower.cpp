#include "Tower.hpp"

using namespace std;


void draw_square (Window* win, int x_square, int y_square, string image_file, bool flip_img){
    if (x_square < 0 || x_square > SQUARES_COUNT_X || y_square < 0 || y_square > SQUARES_COUNT_Y){
        return;
    }
    if (flip_img == true){
        win->draw_img(image_file, Rectangle(Point(FSQUARE_X + x_square * SQUARE_L,
                                            FSQUARE_Y + y_square * SQUARE_L), SQUARE_L, SQUARE_L), NULL_RECT, 0, true, false);
    }
    else{
        win->draw_img(image_file, Rectangle(Point(FSQUARE_X + x_square * SQUARE_L,
                                             FSQUARE_Y + y_square * SQUARE_L), SQUARE_L, SQUARE_L));
    }
}

int calc_reminder(int a, int b){
    while (a < 0)
        a += b;
    return (a % b);
}

Tower::Tower(){};
Tower::Tower (string img_file_, Point place_, float damage_, float loading_time_,
        float initial_cost_, float upgrade_cost_, float upgrade_added_damage_){
    last_enemy_shot_time = chrono::steady_clock::now();
    img_file = img_file_;
    image_index = 1;
    flip_img = false;
    place = place_;
    range = STANDARD_TOWER_RANGE;
    damage = damage_;
    loading_time = loading_time_;
    initial_cost = initial_cost_;
    refund_value = initial_cost_;
    upgrade_cost = upgrade_cost_;
    upgrade_added_damage = upgrade_added_damage_;
}
void Tower::draw (Window* win){
    string s = img_file + "/" + to_string(image_index) + FILE_EXTENSION;
    draw_square(win, place.x, place.y, s, flip_img);
}
bool Tower::in_the_same_square (Point selected_square){
    if (selected_square.x == place.x && selected_square.y == place.y)
        return true;
    return false;
}
void Tower::update_angle(Enemy* enemy){
    float dx = enemy->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
    float dy = enemy->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
    double at = atan(-dy / dx), degree;
    if (dx >= 0){
        if (dy < 0)
            degree = 90 - (180 * at / PI);
        else
            degree = 90 - (180 * at / PI);
        image_index = calc_reminder((int)(degree / 10), 19) + 1;
        flip_img = false;
    }
    else{
        if (dy < 0)
            degree = 270 - (180 * at / PI);
        else
            degree = 270 - (180 * at / PI);
        image_index = 19 - calc_reminder((int)(degree / 10), 19);
        flip_img = true;
    }
    if (degree < 190 && degree > 170)
        image_index = 19;
    else if (degree < 10 || degree > 350)
        image_index = 1;
}
void Tower::shoot_enemy(Window* win, Enemy* enemy, vector <Enemy*> enemies){
    if (find(enemies.begin(), enemies.end(), enemy) == enemies.end())
        shot->reset_position(FSQUARE_X + (place.x * SQUARE_L) + SQUARE_L / 2, FSQUARE_Y + (place.y * SQUARE_L) + SQUARE_L / 2);
    else{
        shot->update_coordination(enemy->get_position(), SHOT_SPEED, D_TIME, place);
        shot->draw_shot(win);
        if (shot->reached_enemy()){
            last_enemy_shot_time = chrono::steady_clock::now();
            enemy->update_life(shot->get_shot_damage());
        }
    }
}
bool Tower::target_in_range(vector <Enemy*> enemies){
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance <= range){
            return true;
        }
    }
    return false;
}
Enemy* Tower::new_target (vector <Enemy*> enemies) {
    float min_distance = MAXX;
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < min_distance){
            min_distance = distance;
        }
    }
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance == min_distance){
            last_enemy_shot = x;
            shot->update_status(false);
            
            return x;
        }
    }
}
bool Tower::has_shot_reached_enemy(){
    return shot->reached_enemy();
}
Enemy* Tower::get_last_enemy_shot(){return last_enemy_shot;}
bool Tower::can_shoot (chrono::steady_clock::time_point current_time) {
    chrono::duration<float> passed_seconds = current_time - last_enemy_shot_time;
    return (passed_seconds.count() >= loading_time);
}
bool Tower::player_can_buy_tower (Player& player, string status){
    if (status == INITIAL_BUILD_STATUS && player.money >= initial_cost){
        player.money -= initial_cost;
        return true;
    }
    return false;
}
void Tower::update_has_shot_enemy_status (bool status){
    shot->update_status(status);
    if (status == true){
        shot->reset_position(FSQUARE_X + (place.x * SQUARE_L) + SQUARE_L / 2, FSQUARE_Y + (place.y * SQUARE_L) + SQUARE_L / 2);
    }
}
bool Tower::can_be_upgraded(Player& Player){
    if (img_file.rbegin()[0] < NUMBER_OF_UPGRADES && Player.money >= upgrade_cost)
        return true;
    return false;
}
void Tower::upgrade_tower(Player& player){
    player.money -= upgrade_cost;
    img_file.rbegin()[0]++;
    shot->upgrade_shot_damage(upgrade_added_damage);
    refund_value += (upgrade_cost * REFUND_PERCENTAGE);
}
void Tower::sell_tower(Player& player){
    player.money += refund_value;
}
//void Tower::play_shot_sound(Window* win) = 0;



Gattling::Gattling(){};
Gattling::Gattling (string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
        float upgrade_cost_, float upgrade_added_damage_) : Tower (img_file_, place_, damage_,
        loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){
        gun_shot_png = FIREBALL_PNG;
        shot = new Shot (FIREBALL_PNG, FSQUARE_X + place_.x * SQUARE_L + (SQUARE_L / 2),
                        FSQUARE_Y + place_.y * SQUARE_L + (SQUARE_L / 2), damage_);
}
bool Gattling::target_in_range(vector <Enemy*> enemies){
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance <= range && (x->not_the_same_type(STUBBORNRUNNER_TYPE))){
            return true;
        }
    }
    return false;
}
Enemy* Gattling::new_target (vector <Enemy*> enemies) {
    float min_distance = MAXX;
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < min_distance && (x->not_the_same_type(STUBBORNRUNNER_TYPE))){
            min_distance = distance;
        }
    }
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance == min_distance && (x->not_the_same_type(STUBBORNRUNNER_TYPE))){
            last_enemy_shot = x;
            shot->update_status(false);
            return x;
        }
    }
}
void Gattling::play_shot_sound(Window* win){
    win->play_sound_effect(GATTLING_SOUND_EFFECT);
}


Missile::Missile(){};
Missile::Missile (string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
        float upgrade_cost_, float upgrade_added_damage_) : Tower (img_file_, place_, damage_,
        loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){
    gun_shot_png = MISSILE_SHOT_PNG;
    shot = new Shot (MISSILE_SHOT_PNG, FSQUARE_X + place_.x * SQUARE_L + (SQUARE_L / 2),
                    FSQUARE_Y + place_.y * SQUARE_L + (SQUARE_L / 2), damage_);
}
void Missile::shoot_enemy(Window* win, Enemy* enemy, vector <Enemy*> enemies){
    if (find(enemies.begin(), enemies.end(), enemy) == enemies.end())
        shot->reset_position(FSQUARE_X + (place.x * SQUARE_L) + SQUARE_L / 2, FSQUARE_Y + (place.y * SQUARE_L) + SQUARE_L / 2);
    else{
        shot->update_coordination(enemy->get_position(), SHOT_SPEED, D_TIME, place);
        shot->draw_shot(win);
        if (shot->reached_enemy()){
            last_enemy_shot_time = chrono::steady_clock::now();
            for (auto x : enemies){
                if (enemy->distance_difference(x->get_position()) <= MISSILE_TOWER_DAMAGE_RANGE){
                    x->update_life(shot->get_shot_damage());
                }
            }
        }
    }
}
void Missile::play_shot_sound(Window* win){
    win->play_sound_effect(MISSILE_SOUND_EFFECT);
}


Tesla::Tesla(){}
Tesla::Tesla (string img_file_, Point place_, float damage_, float loading_time_, float initial_cost_,
        float upgrade_cost_, float upgrade_added_damage_) : Tower (img_file_, place_, damage_,
        loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){
    gun_shot_png = LIGHTNINGBALL_PNG;
    shot = new Shot (LIGHTNINGBALL_PNG, FSQUARE_X + place_.x * SQUARE_L + (SQUARE_L / 2),
                    FSQUARE_Y + place_.y * SQUARE_L + (SQUARE_L / 2), damage_);
}
void Tesla::update_angle(Enemy* enemy){
    float dx = enemy->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
    if (dx >= 0){
        image_index = 1;
    }
    else{
        image_index = 2;
    }
}
void Tesla::play_shot_sound(Window* win){
    win->play_sound_effect(TESLA_SOUND_EFFECT);
}


Glue::Glue(){}
Glue::Glue (string img_file_, Point place_, float damage_, float damage_time_, float loading_time_, float initial_cost_,
        float upgrade_cost_, float upgrade_added_damage_, float upgrade_added_damage_time_) : Tower (img_file_, place_,
        damage_, loading_time_, initial_cost_, upgrade_cost_, upgrade_added_damage_){
    gun_shot_png = GLUEBALL_PNG;
    shot = new Shot (GLUEBALL_PNG, FSQUARE_X + place_.x * SQUARE_L + (SQUARE_L / 2),
                    FSQUARE_Y + place_.y * SQUARE_L + (SQUARE_L / 2), damage_);
    damage_time = damage_time_;
    upgrade_added_damage_time = upgrade_added_damage_time_;
}
void Glue::shoot_enemy (Window* win, Enemy* enemy, vector <Enemy*> enemies){
    if (find(enemies.begin(), enemies.end(), enemy) == enemies.end())
        shot->reset_position(FSQUARE_X + (place.x * SQUARE_L) + SQUARE_L / 2, FSQUARE_Y + (place.y * SQUARE_L) + SQUARE_L / 2);
    else{
        shot->update_coordination(enemy->get_position(), SHOT_SPEED, D_TIME, place);
        shot->draw_shot(win);
        if (shot->reached_enemy()){
            enemy->update_being_chased_by_glue_status(false);
            last_enemy_shot_time = chrono::steady_clock::now();
            for (auto x : enemies){
                if (x->not_the_same_type(STUBBORNRUNNER_TYPE) && enemy->distance_difference(x->get_position()) <= GLUE_TOWER_DAMAGE_RANGE){
                    x->update_speed(damage_time, shot->get_shot_damage());
                }
            }
        }
    }
}
bool Glue::target_in_range (vector <Enemy*> enemies){
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance <= range && x->not_the_same_type(STUBBORNRUNNER_TYPE) && x->can_be_shot_by_glue() && x->finished_glue_time()){
            return true;
        }
    }
    return false;
}
void Glue::upgrade_tower(Player& player){
    player.money -= upgrade_cost;
    img_file.rbegin()[0]++;
    shot->upgrade_shot_damage(upgrade_added_damage);
    refund_value += (upgrade_cost * REFUND_PERCENTAGE);
    damage_time += upgrade_added_damage_time;
}
Enemy* Glue::new_target (vector <Enemy*> enemies) {
    float min_distance = MAXX;
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < min_distance && x->not_the_same_type(STUBBORNRUNNER_TYPE) && x->can_be_shot_by_glue() && x->finished_glue_time()){
            min_distance = distance;
        }
    }
    for (auto x : enemies){
        float dx = x->get_position().x - (SQUARE_L * place.x + FSQUARE_X + SQUARE_L / 2);
        float dy = x->get_position().y - (SQUARE_L * place.y + FSQUARE_Y + SQUARE_L / 2);
        float distance = sqrt(dx * dx + dy * dy);
        if (distance == min_distance && x->not_the_same_type(STUBBORNRUNNER_TYPE) && x->can_be_shot_by_glue() && x->finished_glue_time()){
            last_enemy_shot = x;
            shot->update_status(false);
            x->update_being_chased_by_glue_status(true);
            return x;
        }
    }
}
void Glue::play_shot_sound(Window* win){}