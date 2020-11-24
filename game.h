//
// Created by d on 2020/10/3.
//

#ifndef PLANTS_ZOMBIES_GAME_H
#define PLANTS_ZOMBIES_GAME_H
#include "plant.h"

class Game {
    vector <pair <Object*, bool>> object_list;
    int sun;
    int score;
    vector <Object*> board[board_width][board_height];
    int cursor_x;
    int cursor_y;
    int store_cursor;
    bool root_out;

    int zombie_cd;
    int test_zombie_cd;
    int zombie_step;
    int zombie_time_count;

    vector <pair<Plant*, clock_t>> store_objects;

    void init_board();
    void update_board();
    vector <int> find_obj(int x, int y, Object_type t);
    bool update_zombie_cd();
    bool can_be_planted();
    bool exist_zombie(int x);
    bool exist_plant(int x, int y);
    int get_printed(int x, int y);
    void box_boom(BoxZom* boxZom);
    void throw_stone(CatapultZombie* catapultZombie);
    void set_text_color(int color);
    void update_zombie_step();
    void generate_zombie();
    bool update_test_zombie_cd();
    void test_generate_zombie();

    void drawInterface(clock_t now);
 public:
    Game();
    void playing();
};

#endif //PLANTS_ZOMBIES_GAME_H
