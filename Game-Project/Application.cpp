#include "Application.hpp"

using namespace std;

Application::Application (Points path_squares, chrono::steady_clock::time_point beginning_time_, vector <string> waves_) {
    beginning_time = beginning_time_;
    win = new Window (WINDOWS_WIDTH, WINDOWS_HEIGHT, APP_NAME);
    win->play_music(BACKGROUND_MUSIC);
    player.life = INITIAL_LIFE;
    player.money = INITIAL_MONEY;
    continue_game = 1;
    win->draw_img (BACK_GROUND_PNG);
    path.update_path(path_squares, waves_);
    draw_player_setting(win);
    path.draw_path_with_effects(win);
    selected_square.x = -1;
    selected_square.y = -1;
}
void Application::run() {
    while (continue_game == 1) {
        path.move_enemies(beginning_time, player, continue_game);
        read_input();
        delay(10);
    }
    win->stop_music();
    if (continue_game == 0){
        win->draw_img(YOU_WIN_PNG, Rectangle(Point((WINDOWS_WIDTH - END_MESSAGE_WIDTH) / 2,
                        (WINDOWS_HEIGHT - END_MESSAGE_HIGHT) / 2), Point((WINDOWS_WIDTH + END_MESSAGE_WIDTH) / 2,
                        (WINDOWS_HEIGHT + END_MESSAGE_HIGHT) / 2)));
        win->play_sound_effect(WIN_SOUND_EFFECT);
    }
    else{
        win->draw_img(YOU_LOSE_PNG, Rectangle(Point((WINDOWS_WIDTH - END_MESSAGE_WIDTH) / 2,
                        (WINDOWS_HEIGHT - END_MESSAGE_HIGHT) / 2), Point((WINDOWS_WIDTH + END_MESSAGE_WIDTH) / 2,
                        (WINDOWS_HEIGHT + END_MESSAGE_HIGHT) / 2)));
        win->play_sound_effect(LOSE_SOUND_EFFECT);
        
    }
    win->update_screen();
    delay(3000);
    exit(0);
}
void Application::read_input() {
    last_event = win->poll_for_event();
    apply_event();
}
bool Application::is_square_occupied (Point selected_square){
    for (auto curr_tower : towers){
        if (curr_tower->in_the_same_square(selected_square))
            return true;
    }
    return false;
}
Tower* Application::tower_type(Point selected_square){
    for (auto curr_tower : towers){
        if (curr_tower->in_the_same_square(selected_square))
            return curr_tower;
    }
} 
void Application::apply_event() {
    draw_board(win, beginning_time);
    if (last_event.get_type() == Event::QUIT){
        for (auto tower : towers){
            delete tower;
        }
        exit(0);
    }
    if (last_event.get_type() == Event::KEY_PRESS){
        char pressed_key = last_event.get_pressed_key();
        if (pressed_key == 'g' && !path.is_square_in_path(selected_square) && !is_square_occupied (selected_square)){
            Gattling* gt = new Gattling (GATTLING_TOWERS, selected_square, GATTLLING_TOWER_DAMAGE,
            GATTLING_TOWER_LOADING_TIME, GATTLING_TOWER_INITIAL_COST, GATTLING_TOWER_UPGRADE_COST,
            GATTLING_TOWER_UPGRADE_ADDED_DAMAGE);
            if (gt->player_can_buy_tower(player, INITIAL_BUILD_STATUS)){
                towers.push_back(gt);
                draw_square(win, selected_square.x, selected_square.y, GATTLING_TOWER_LVL1, false);
                win->play_sound_effect(PURCHASE_SOUND_EFFECT);
            }
            else
                delete gt;
            
        }
        else if (pressed_key == 'm' && !path.is_square_in_path(selected_square) && !is_square_occupied (selected_square)){
            Missile* ms = new Missile (MISSILE_TOWERS, selected_square, MISSILE_TOWER_DAMAGE, MISSILE_TOWER_LOADING_TIME,
            MISSILE_TOWER_INITIAL_COST, MISSILE_TOWER_UPGRADE_COST, MISSILE_TOWER_UPGRADE_ADDED_DAMAGE);
            if (ms->player_can_buy_tower(player, INITIAL_BUILD_STATUS)){
                towers.push_back(ms);
                draw_square(win, selected_square.x, selected_square.y, MISSILE_TOWER_LVL1, false);
                win->play_sound_effect(PURCHASE_SOUND_EFFECT);
            }
            else
                delete ms;
        }
        else if (pressed_key == 't' && !path.is_square_in_path(selected_square) && !is_square_occupied (selected_square)){
            Tesla* ts = new Tesla (TESLA_TOWERS, selected_square, TESLA_TOWER_DAMAGE, TESLA_TOWER_LOADING_TIME,
            TESLA_TOWER_INITIAL_COST, TESLA_TOWER_UPGRADE_COST, TESLA_TOWER_UPGRADE_ADDED_DAMAGE);
            if (ts->player_can_buy_tower(player, INITIAL_BUILD_STATUS)){
                towers.push_back(ts);
                draw_square(win, selected_square.x, selected_square.y, TESLA_TOWER_LVL1, false);
                win->play_sound_effect(PURCHASE_SOUND_EFFECT);
            }
            else
                delete ts;
            
        }
        else if (pressed_key == 'u' && !path.is_square_in_path(selected_square) && is_square_occupied (selected_square)){
            Tower* upgraded_tower = tower_type(selected_square);
            if (upgraded_tower->can_be_upgraded(player)){
                upgraded_tower->upgrade_tower(player);
                win->play_sound_effect(PURCHASE_SOUND_EFFECT);
            }
            
        }
        else if (pressed_key == 's' && !path.is_square_in_path(selected_square) && is_square_occupied (selected_square)){
            Tower* selected_tower = tower_type(selected_square);
            selected_tower->sell_tower(player);
            towers.erase(find(towers.begin(), towers.end(), selected_tower));
            delete selected_tower;
            win->play_sound_effect(PURCHASE_SOUND_EFFECT);
        }
        else if (pressed_key == 'l' && !path.is_square_in_path(selected_square) && !is_square_occupied (selected_square)){
            Tower* gl = new Glue (GLUE_TOWERS, selected_square, GLUE_TOWER_DAMAGE, GLUE_TOWER_EFFECTIVE_TIME,
            GLUE_TOWER_LOADING_TIME, GLUE_TOWER_INITIAL_COST, GLUE_TOWER_UPGRADE_COST, GLUE_TOWER_UPGRADE_ADDED_DAMAGE,
            GLUE_TOWER_UPGRADE_ADDED_EFFECTIVE_TIME);
            if (gl->player_can_buy_tower(player, INITIAL_BUILD_STATUS)){
                towers.push_back(gl);
                draw_square(win, selected_square.x, selected_square.y, GLUE_TOWER_LVL1, false);
                win->play_sound_effect(PURCHASE_SOUND_EFFECT);
            }
            else
                delete gl;
        }
        else{
            win->play_sound_effect(WRONG_KEY_SOUND_EFFECT);
        }
    }
    if (last_event.get_type() == Event::LRELEASE){
        Point mouse_position = last_event.get_mouse_position();
        if (mouse_position.x >= FSQUARE_X && mouse_position.y >= FSQUARE_Y &&
            mouse_position.x <= LSQUARE_X && mouse_position.y <= LSQUARE_Y){
            int x_square = (mouse_position.x - FSQUARE_X) / SQUARE_L;
            int y_square = (mouse_position.y - FSQUARE_Y) / SQUARE_L;
            selected_square.x = x_square;
            selected_square.y = y_square;
            win->play_sound_effect(SELECT_SOUND_EFFECT);
        }
        else{
            selected_square.x = -1;
            selected_square.y = -1;
            win->play_sound_effect(WRONG_KEY_SOUND_EFFECT);
        }
    }
}
void Application::draw_towers (Window* win){
    for (auto x : towers){
        x->draw(win);
    }
}
void Application::draw_player_setting (Window* win){
    win->draw_img(HEART_PNG, Rectangle(Point(60, 5), 30, 30));
    win->show_text(to_string(player.life), Point(100, 10), WHITE, FONT_LOCATION, FONT_SIZE);
    win->draw_img(MONEY_PNG, Rectangle(Point(60, 35), 30, 30));
    win->show_text(to_string(player.money), Point(100, 40), WHITE, FONT_LOCATION, FONT_SIZE);
}
void Application::draw_board(Window* win, chrono::steady_clock::time_point beginning_time_){
    win->clear();
    win->draw_img (BACK_GROUND_PNG);
    draw_player_setting(win);
    path.draw_path(win);
    auto current_time = chrono::steady_clock::now();
    chrono::duration<float> passed_seconds = current_time - beginning_time_;
    draw_square(win, selected_square.x, selected_square.y, SELECTED_SQUARE, false);
    if (passed_seconds.count() >= WAVES_TIME_BREAK){
        path.draw_enemies(win, passed_seconds.count());
        path.draw_shooting(win, towers, current_time);
    }
    draw_towers(win);
    win->update_screen();
}

void read_input(Points& path_squares, vector <string>& waves){
    string input, x_square, y_square;
    getline (cin, input);
    istringstream is (input);
    while (getline(is, x_square, ' ')){
        getline(is, y_square, ' ');
        path_squares.push_back(Point(stoi(x_square), stoi(y_square)));
    }
    string wave;
    while (getline(cin, wave)){
        waves.push_back(wave);
    }
}