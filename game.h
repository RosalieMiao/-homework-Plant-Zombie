//
// Created by d on 2020/10/3.
//

#ifndef PLANTS_ZOMBIES_GAME_H
#define PLANTS_ZOMBIES_GAME_H
//#include <map>
#include <vector>
#include "zombie.h"
#include "plant.h"
#define board_width 8
#define board_height 3
using namespace std;

class Game {
    vector <pair <Object*, bool>> object_list;
    int sun;
    int score;
    vector <Object*> board[board_width][board_height];
    int cursor_x;
    int cursor_y;
    int store_cursor;
    double zombie_cd;
    double zombie_cd_piece;

    void init_board();
    void update_board();
    bool encounter(Object* obj, Object_type t);
    int find_obj(int x, int y, Object_type t);
    Object* find(int x, int y, Object_type t);
    bool update_zombie_cd();
    bool can_be_planted(int x, int y);
 public:
    Game();
    void playing();
    void drawInterface();
};

#endif //PLANTS_ZOMBIES_GAME_H
