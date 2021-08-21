#include "Path.hpp"

using namespace std;


Path::Path (){}
void Path::draw_path (Window* win){
    for (int i = 0; i < path_way.size(); i++){
        draw_square(win, path_way[i].x, path_way[i].y, SQUARE_PNG, false);
    }
}
void Path::draw_path_with_effects (Window* win){
    for (int i = 0; i < path_way.size(); i++){
        draw_square(win, path_way[i].x, path_way[i].y, SQUARE_PNG, false);
        win->update_screen();
        delay(80);
    }
}
void Path::draw_enemies (Window* win, float seconds){
    if (seconds >= WAVES_TIME_BREAK){
        seconds -= WAVES_TIME_BREAK;
        for (int i = 0; i < enemies.size(); i++){
            if (seconds > 0){
                enemies[i]->draw(win);
                seconds -= ENEMY_DEPLOY_TIME;
            }
        }
    }
}
void Path::draw_shooting (Window* win, vector <Tower*> towers, chrono::steady_clock::time_point current_time){
    for (auto x : towers){
        if(x->can_shoot(current_time) && (x->has_shot_reached_enemy() == false || x->target_in_range(enemies))){
            Enemy* enemy_to_be_shot;
            if (x->has_shot_reached_enemy() == true){
                enemy_to_be_shot = x->new_target(enemies);
            }
            else{
                enemy_to_be_shot = x->get_last_enemy_shot();
            }
            x->update_angle(enemy_to_be_shot);
            x->shoot_enemy(win, enemy_to_be_shot, enemies);
            x->play_shot_sound(win);
            if (enemy_to_be_shot->is_dead()){
                for (auto x : towers){
                    if (x->get_last_enemy_shot() == enemy_to_be_shot){
                        x->update_has_shot_enemy_status(true);
                    }
                }
            }
        }
    }
}
void Path::update_path (Points path_squares, vector <string> waves_){
    construct_path(path_squares);
    waves = waves_;
    wave_number = 0;
}
bool Path::is_square_in_path(Point selected_square){
    for (auto curr_square : path_way)
        if (curr_square.x == selected_square.x && curr_square.y == selected_square.y)
            return true;
    return false;
}
Coordinate Path::get_square_center (Coordinate place){
    int x_square = (place.x - FSQUARE_X) / SQUARE_L;
    int y_square = (place.y - FSQUARE_Y) / SQUARE_L;
    Coordinate square_center;
    square_center.x = FSQUARE_X + (SQUARE_L / 2) + (x_square * SQUARE_L);
    square_center.y = FSQUARE_Y + (SQUARE_L / 2) + (y_square * SQUARE_L);
    return square_center; 
}
string Path::next_direction (Enemy* enemy){
    Coordinate location_square = get_square_center(enemy->get_position());
    int curr = 0;
    for (int i = 0; i < path_way.size(); i++){ 
        if (FSQUARE_X + (SQUARE_L / 2) + (path_way[i].x * SQUARE_L) == location_square.x && 
            FSQUARE_Y + (SQUARE_L / 2) + (path_way[i].y * SQUARE_L) == location_square.y){
            curr = i;
        }
    }
    if (curr == 0)
        return path_direction[0];
    if (path_direction[curr - 1] == RIGHT_DIRECTION && enemy->get_position().x < location_square.x)
        return path_direction[curr - 1];
    if (path_direction[curr - 1] == LEFT_DIRECTION && enemy->get_position().x > location_square.x)
        return path_direction[curr - 1];
    if (path_direction[curr - 1] == UP_DIRECTION && enemy->get_position().y > location_square.y)
        return path_direction[curr - 1];
    if (path_direction[curr - 1] == DOWN_DIRECTION && enemy->get_position().y < location_square.y)
        return path_direction[curr - 1];
    return path_direction[curr];
}
void Path::move_single_enemy (Enemy* enemy, Player& player, int& continue_game){
    string next_move = next_direction(enemy);
    if (next_move == END_OF_PATH || enemy->is_dead()){
        if (next_move == END_OF_PATH){
            enemy->reduce_player_life(player);
            if (player.life <= 0) {
                continue_game = -1;
            }
        }
        else{
            enemy->add_player_money(player);
        }
        enemies.erase(find(enemies.begin(), enemies.end(), enemy));
        delete enemy;
    }
    else{
        string new_img;
        if (!enemy->not_the_same_type(RUNNER_TYPE)){
            if (next_move == LEFT_DIRECTION){
                enemy->update_flip_image(true);
                new_img = "Icons/Runner/soldier_run_right_" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 12) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else{
                enemy->update_flip_image(false);
                new_img = "Icons/Runner/soldier_run_" + next_move + "_" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 12) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
        }
        else if (!enemy->not_the_same_type(SCRAMBLER_TYPE)){
            if (next_move == LEFT_DIRECTION){
                enemy->update_flip_image(true);
                new_img = "Icons/Scrambler/bike_run_right_" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 4) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else{
                enemy->update_flip_image(false);
                new_img = "Icons/Scrambler/bike_run_" + next_move + "_" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 4) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
        }
        else if (!enemy->not_the_same_type(SUPERTROOPER_TYPE)){
            if (next_move == LEFT_DIRECTION){
                enemy->update_flip_image(true);
                new_img = "Icons/Supertrooper/heavyRunnerRight" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 21) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == RIGHT_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Supertrooper/heavyRunnerRight" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 21) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == UP_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Supertrooper/heavyRunnerUp" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 19) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == DOWN_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Supertrooper/heavyRunnerDown" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 15) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
        }
        else if (!enemy->not_the_same_type(STUBBORNRUNNER_TYPE)){
            if (next_move == LEFT_DIRECTION){
                enemy->update_flip_image(true);
                new_img = "Icons/Stubborn/icerunnerRight" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 15) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == RIGHT_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Stubborn/icerunnerRight" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 15) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == UP_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Stubborn/icerunnerUp" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 15) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
            else if (next_move == DOWN_DIRECTION){
                enemy->update_flip_image(false);
                new_img = "Icons/Stubborn/icerunnerDown" +
                to_string((int)(enemy->get_position().x + enemy->get_position().y) % 16) + FILE_EXTENSION;
                enemy->update_img(new_img);
            }
        }
        enemy->update_last_movement(next_move);
        enemy->move_in_direction(next_move, PROGRAM_SPEED);
    }
}
void Path::move_enemies (chrono::steady_clock::time_point& beginning_time_, Player& player, int& continue_game){
    if (enemies.size() == 0){
        beginning_time_ = std::chrono::steady_clock::now();
        if (wave_number == waves.size()){
            continue_game = 0;
            return;
        }
        build_wave(waves[wave_number]);
        wave_number++;
    }
    auto current_time = std::chrono::steady_clock::now();
    chrono::duration<float> seconds = current_time - beginning_time_;
    float passed_time = WAVES_TIME_BREAK;
    if (seconds.count() >= passed_time){
        for (auto enemy : enemies){
            if (seconds.count() > passed_time){
                move_single_enemy(enemy, player, continue_game);
                passed_time += ENEMY_DEPLOY_TIME;
            }
        }
    }
}
Points Path::get_path(){return path_way;}
void Path::build_wave (string wave){
    string runner, stubborn_runner, super_trooper, scrambler;
    int runner_number, stubborn_runner_number, super_trooper_number, scrambler_number, enemy_count = 0;
    istringstream is (wave);
    while (getline(is, runner, ' ')){
        getline(is, stubborn_runner, ' ');
        getline(is, super_trooper, ' ');
        getline(is, scrambler, ' ');
    }
    runner_number = stoi (runner);
    stubborn_runner_number = stoi (stubborn_runner);
    super_trooper_number = stoi (super_trooper);
    scrambler_number = stoi (scrambler);
    Coordinate coordinate;
    coordinate.x = path_way[0].x * SQUARE_L + (FSQUARE_X + SQUARE_L / 2);
    coordinate.y = path_way[0].y * SQUARE_L + (FSQUARE_Y + SQUARE_L / 2);
    while (runner_number > 0 || stubborn_runner_number > 0 || super_trooper_number > 0 || scrambler_number > 0){
        Runner* runners;
        Stubbornrunner* stubbornrunners;
        Supertrooper* supertroopers;
        Scrambler* scramblers;
        int group = rand() % 4;
        enemy_count++;
        switch (group) {
            case 0:
                {
                    if (runner_number > 0){
                        runners = new Runner (RUNNER_ENEMY, RIGHT_DIRECTION, coordinate,
                        ((1 - NEW_WAVE_ADDED_LIFE) + NEW_WAVE_ADDED_LIFE * (wave_number + 1)) * RUNNER_INITIAL_HEALTH,
                        RUNNER_SPEED, RUNNER_KILL_PRIZE, RUNNER_REACH_END_LOSS);
                        enemies.push_back(runners);
                        runner_number--;
                    }
                break;
                }
            case 1:
                {
                    if (stubborn_runner_number > 0){
                        stubbornrunners = new Stubbornrunner (STUBBORNRUNNER_ENEMY, RIGHT_DIRECTION, coordinate,
                        ((1 - NEW_WAVE_ADDED_LIFE) + NEW_WAVE_ADDED_LIFE * (wave_number + 1)) * STUBBORNRUNNER_INITIAL_HEALTH,
                        STUBBORNRUNNER_SPEED, STUBBORNRUNNER_KILL_PRIZE, STUBBORNRUNNER_REACH_END_LOSS);
                        enemies.push_back(stubbornrunners);
                        stubborn_runner_number--;
                    }
                break;
                }
            case 2:
                {
                    if (super_trooper_number > 0){
                        supertroopers = new Supertrooper (SUPERTROOPER_ENEMY, RIGHT_DIRECTION, coordinate,
                        ((1 - NEW_WAVE_ADDED_LIFE) + NEW_WAVE_ADDED_LIFE * (wave_number + 1)) * SUPERTROOPER_INITIAL_HEALTH,
                        SUPERTROOPER_SPEED, SUPERTROOPER_KILL_PRIZE, SUPERTROOPER_REACH_END_LOSS);
                        enemies.push_back(supertroopers);
                        super_trooper_number--;
                    }
                break;
                }
            case 3:
                {
                    if (scrambler_number > 0){
                        scramblers = new Scrambler (SCRAMBLER_ENEMY, RIGHT_DIRECTION, coordinate,
                        ((1 - NEW_WAVE_ADDED_LIFE) + NEW_WAVE_ADDED_LIFE * (wave_number + 1)) * SCRAMBLER_INITIAL_HEALTH,
                        SCRAMBLER_SPEED, SCRAMBLER_KILL_PRIZE, SCRAMBLER_REACH_END_LOSS);
                        enemies.push_back(scramblers);
                        scrambler_number--;
                    }
                break;
                }
        }
    }
    
}
void Path::construct_path (Points path_squares){
    path_way.push_back (Point(path_squares[0].x, path_squares[0].y));
    for (int i = 1; i < path_squares.size(); i++) {
        if (path_squares[i].x == path_squares[i - 1].x){
            if (path_squares[i].y >= path_squares[i - 1].y){
                for (int j = path_squares[i - 1].y + 1; j <= path_squares[i].y; j++){
                    path_direction.push_back(DOWN_DIRECTION);
                    path_way.push_back(Point(path_squares[i].x, j));
                }
            }
            else{
                for (int j = path_squares[i - 1].y - 1; j >= path_squares[i].y; j--){
                    path_direction.push_back(UP_DIRECTION);
                    path_way.push_back(Point(path_squares[i].x , j));
                }
            }
        }
        else if (path_squares[i].y == path_squares[i - 1].y){
            if (path_squares[i].x >= path_squares[i - 1].x){
                for (int j = path_squares[i - 1].x + 1; j <= path_squares[i].x; j++){
                    path_direction.push_back(RIGHT_DIRECTION);
                    path_way.push_back(Point(j, path_squares[i].y));
                }
            }
            else{
                for (int j = path_squares[i - 1].x - 1; j >= path_squares[i].x; j--){
                    path_direction.push_back(LEFT_DIRECTION);
                    path_way.push_back(Point(j, path_squares[i].y));
                }
            }
        }
        else{
            cerr << "path error!" << endl;
        }
    }
    path_direction.push_back(END_OF_PATH);
}