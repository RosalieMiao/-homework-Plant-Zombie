//
// Created by d on 2020/10/3.
//

#include "game.h"
#include <iostream>
#include <assert.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;

void Game::init_board() {
    for (auto &i : board)
        for (auto &j : i)
            j.clear();
}

void Game::update_board() {
    init_board();

    vector <pair<Object*, bool>>::iterator obj_iter;
    obj_iter = object_list.begin();
    while (obj_iter != object_list.end()) {
        board[(*obj_iter).first->get_cor_y()][(*obj_iter).first->get_cor_x()].push_back((*obj_iter).first);
        obj_iter++;
    }
}

bool Game::encounter(Object* obj, Object_type t) {
    int tx = obj->get_cor_x();
    int ty = obj->get_cor_y();
    for (auto &i : board[ty][tx]) {
        if (i->get_type() == t) return true;
    }
    return false;
}

int Game::find_obj(int x, int y, Object_type t) {
    for (int i = 0; i < object_list.size(); ++i) {
        if (object_list[i].first->get_cor_x() == x && object_list[i].first->get_cor_y() == y
        && object_list[i].first->get_type() == t) {
            return i;
        }
    }
    return -1;
}

Object* Game::find(int x, int y, Object_type t) {
    for (auto &i : board[y][x]) {
        if (i->get_type() == t) {
            return i;
        }
    }
    return nullptr;
}

bool Game::update_zombie_cd() {
    zombie_cd += zombie_cd_piece;
    bool ret = zombie_cd >= 1;
    if (ret) zombie_cd = 0;
    return ret;
}

bool Game::can_be_planted(int x, int y) {
    if (board[y][x].empty()) return true;
    for (auto &i : board[y][x]) {
        if (i->get_type() == PLANT || i->get_type() == ZOMBIE) return false;
    }
    return true;
}

Game::Game() {
    object_list.clear();

    cursor_x = -1;
    cursor_y = -1;
    store_cursor = -1;

    zombie_cd = 0;
    zombie_cd_piece = 0.1;

    sun = 0;
    score = 0;
    init_board();
    srand((unsigned)time(NULL));
}

void Game::playing() {
    drawInterface();

    int ch;
    while (true) {
        Sleep(500);

        if (update_zombie_cd()) {
            object_list.emplace_back(new Zombie(rand() % 3, 8), false);
        }

        sun+=25;
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) break;
            else if (ch == 98) {//b
                if (store_cursor == -1) store_cursor = 0;
            } else if (ch == 119) {//w
                if (cursor_x > 0) cursor_x--;
            } else if (ch == 115) {//s
                if (cursor_x != -1 && cursor_x < 2) cursor_x++;
            } else if (ch == 100) {//d
                if (cursor_y == -1 && store_cursor != -1) {
                    if (store_cursor < 0) store_cursor++;
                } else if (cursor_y != -1 && cursor_y < 6) {
                    cursor_y++;
                }
            } else if (ch == 97) {//a
                if (cursor_y == -1 && store_cursor != -1) {
                    if (store_cursor > 0) store_cursor--;
                } else if (cursor_y > 0) cursor_y--;
            } else if (ch == 13) {//Enter
                if (store_cursor != -1 && cursor_x == -1 && cursor_y == -1) {
                    if (store_cursor == 0) {
                        cursor_x = 0;
                        cursor_y = 0;
                    }
                } else {
                    if (board[cursor_y][cursor_x].empty()) {
                        if (store_cursor == 0) {
                            PeaShoot* pea_tmp;
                            pea_tmp = new PeaShoot(cursor_x, cursor_y);
                            if (pea_tmp->get_cost() > sun) {
                            } else {
                                sun -= pea_tmp->get_cost();
                                object_list.emplace_back(pea_tmp, false);
                            }
                            cursor_x = -1;
                            cursor_y = -1;
                            store_cursor = -1;
                        }
                    }
                }
            } else if (ch == 120) {//x
                store_cursor = -1;
                cursor_x = -1;
                cursor_y = -1;
            }
        }

        bool tmp_flag = false;
        for (int i = 0; i < object_list.size(); ++i) {
            if (object_list[i].first->get_type() == ZOMBIE) {
                if (object_list[i].first->get_cor_y() <= 0) {
                    tmp_flag = true;
                    cout << endl << "GAME OVER!" << endl << endl;
                    break;
                }
                bool zom_f = false;
                object_list[i].first->move();
                if (encounter(object_list[i].first, PLANT)) {
                    zom_f = true;
                    object_list[i].first->revoke_move();
                }
                if (zom_f) {
                    //a Zombie encounter a plant
                    int tx = object_list[i].first->get_cor_x();
                    int ty = object_list[i].first->get_cor_y() - 1;
                    Zombie* zom_tmp;
                    Plant* pla_tmp;
                    zom_tmp = dynamic_cast<Zombie*>(object_list[i].first);
                    pla_tmp = dynamic_cast<Plant*>(find(tx, ty, PLANT));
                    assert(pla_tmp != nullptr);
                    if (pla_tmp->be_attacked(zom_tmp->get_attack())) {
                        object_list[find_obj(tx, ty, PLANT)].second = true;
                    }
                }
            } else if (object_list[i].first->get_type() == PLANT){
                Plant* pla_tmp;
                pla_tmp = dynamic_cast<Plant*>(object_list[i].first);
                if (pla_tmp->get_plant_type() == PEASHOOT) {
                    PeaShoot* pea_tmp;
                    pea_tmp = dynamic_cast<PeaShoot*>(pla_tmp);
                    if (pea_tmp->update_cd()) {
                        object_list.emplace_back(pea_tmp->generate_bullet(), false);
                    }
                }
            }
        }

        if (tmp_flag) break;

        update_board();
        for (auto &i : object_list) {
            if (i.first->get_type() == BULLET) {
                Bullet* bul_tmp;
                bul_tmp = dynamic_cast<Bullet*>(i.first);
                if ((bul_tmp->get_cor_y() + i.first->get_speed()) >= 7) {
                    i.second = true;
                } else if (encounter(i.first, ZOMBIE)) {
                    int tx = i.first->get_cor_x();
                    int ty = i.first->get_cor_y();
                    Zombie* zom_tmp;
                    zom_tmp = dynamic_cast<Zombie*>(find(tx, ty, ZOMBIE));
                    assert(zom_tmp != nullptr);
                    if (zom_tmp->be_attacked(bul_tmp->get_attack())) {
                        object_list[find_obj(tx, ty, ZOMBIE)].second = true;
                    }
                    i.second = true;
                } else {
                    i.first->move();
                    if (encounter(i.first, ZOMBIE)) {
                        int tx = i.first->get_cor_x();
                        int ty = i.first->get_cor_y();
                        Zombie* zom_tmp;
                        zom_tmp = dynamic_cast<Zombie*>(find(tx, ty, ZOMBIE));
                        assert(zom_tmp != nullptr);
                        if (zom_tmp->be_attacked(bul_tmp->get_attack())) {
                            object_list[find_obj(tx, ty, ZOMBIE)].second = true;
                            score += 10;
                        }
                        i.second = true;
                    }
                }
            }
        }

        int obj_size = object_list.size();
        for (int i = 0; i < obj_size; ++i) {
            if (object_list[i].second) {
                delete object_list[i].first;
                object_list.erase(object_list.begin() + i);
                obj_size--;
                i--;
            }
        }

        update_board();
        system("cls");
        drawInterface();
    }
}



void Game::drawInterface() {
    if (cursor_x == 0 && cursor_y == 0) cout << "+";
    else cout << "#";
    for (int i = 0; i < board_width; i++) {
        if (cursor_x == 0 && cursor_y == i)
            cout << "--------";
        else cout << "########";
        if (cursor_x == 0 && (cursor_y == i || cursor_y == i + 1)) cout << "+";
        else cout << "#";
    }
    cout << endl;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                cout << "|";
            else cout << "#";
            cout << "        ";
        }
        cout << endl;
        for (int j = 0; j < board_width; ++j) {
            if (board[j][i].empty()) {
                if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                    cout << "|";
                else cout << "#";
                cout << "        ";
            } else {
                Object* obj_tmp;
                obj_tmp = board[j][i].front();
                if (obj_tmp->get_type() == BULLET) {
                    for (int k = 1; k < board[j][i].size(); ++k) {
                        if (board[j][i][k]->get_type() == PLANT) obj_tmp = board[j][i][k];
                    }
                }
                if (obj_tmp->get_type() == ZOMBIE) {
                    if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                        cout << "|";
                    else cout << "#";
                    cout << " zombie ";
                } else if (obj_tmp->get_type() == PLANT) {
                    Plant* tmp;
                    tmp = dynamic_cast<Plant*>(obj_tmp);
                    if (tmp->get_plant_type() == PEASHOOT) {
                        if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                            cout << "|";
                        else cout << "#";
                        cout << "Peashoot";
                    }
                } else if (obj_tmp->get_type() == BULLET) {
                    if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                        cout << "|";
                    else cout << "#";
                    cout << "    O   ";
                }
            }
        }
        cout << endl;
        for (int j = 0; j < board_width; ++j) {
            if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                cout << "|";
            else cout << "#";
            cout << "        ";
        }
        cout << endl;
        if ((cursor_x == i || cursor_x == i + 1) && cursor_y == 0) cout << "+";
        else cout << "#";
        for (int j = 0; j < board_width; ++j) {
            if ((cursor_x == i || cursor_x == i + 1) && cursor_y == j)
                cout << "--------";
            else cout << "########";
            if ((cursor_x == i || cursor_x == i + 1) && (cursor_y == j || cursor_y == j + 1)) cout << "+";
            else cout << "#";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < board_width * 9 + 1; i++) cout << "=";
    cout << endl;
    cout << "[Store]             " << "sunshine: " << sun << " | " << "score: " << score << endl;
    for (int i = 0; i < board_width * 9 + 1; i++) cout << "-";
    cout << endl;
    if (store_cursor == 0) {
        cout << "[Peashoot]";
    } else cout << " Peashoot ";
    cout << " " << 100 << endl;
    for (int i = 0; i < board_width * 9 + 1; i++) cout << "-";
    cout << endl;
}