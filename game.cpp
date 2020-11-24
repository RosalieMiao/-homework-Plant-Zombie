//
// Created by d on 2020/10/3.
//

#include "game.h"

void Game::init_board() {
    //移动光标
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    //初始化board
    for (auto &i : board)
        for (auto &j : i)
            j.clear();
}

void Game::update_board() {
    init_board();

    for (auto &i : object_list) {
        int x = i.first->get_cor_x();
        int y = i.first->get_cor_y();
        if (!(i.first->get_type() == BULLET && !board[y][x].empty())) {
            board[y][x].push_back(i.first);
        }
    }
}

vector <int> Game::find_obj(int x, int y, Object_type t) {
    vector <int> ret;
    ret.clear();
    for (int i = 0; i < object_list.size(); ++i) {
        if (t == PLANT) {
            int len = strlen(object_list[i].first->get_name());
            for (int j = 0; j < len; ++j) {
                if (object_list[i].first->get_cor_x() == x
                    && object_list[i].first->get_cor_y() == y - j
                    && object_list[i].first->get_type() == t) {
                    ret.push_back(i);
                    break;
                }
            }
        } else {
            if (object_list[i].first->get_cor_x() == x && object_list[i].first->get_cor_y() == y
                && object_list[i].first->get_type() == t) {
                ret.push_back(i);
            }
        }
    }
    return ret;
}

bool Game::update_zombie_cd() {
    zombie_cd --;
    bool ret = zombie_cd <= 0;
    if (ret) zombie_cd = 100;
    return ret;
}

bool Game::can_be_planted() {
    for (int i = cursor_y * 11; i < cursor_y * 11 + 11; ++i) {
        for (auto &j : board[i][cursor_x]) {
            if (j->get_type() == PLANT) return false;
        }
    }
    return true;
}

bool Game::exist_zombie(int x) {
    for (auto &i : board) {
        for (auto &j: i[x]) {
            if (j->get_type() == ZOMBIE) return true;
        }
    }
    return false;
}

bool Game::exist_plant(int x, int y) {
    for (int i = 0; i < y; ++i) {
        for (auto &j : board[i][x]) {
            if (j->get_type() == PLANT) return true;
        }
    }
    return false;
}

int Game::get_printed(int x, int y) {
    //如果有南瓜头就输出南瓜头
    //否则输出队列里第一个不是BULLET的，如果都是就输出一个BULLET
    int ret = 0;
    while (ret < board[y][x].size()) {
        if (board[y][x][ret]->get_type() == PLANT) {
            Plant* pla_tmp;
            pla_tmp = (Plant*) (board[y][x][ret]);
            if (pla_tmp->get_plant_type() == PUMPKIN) return ret;
        }
        ret ++;
    }
    ret = 0;
    while (ret < board[y][x].size() && board[y][x][ret]->get_type() == BULLET){
        ret++;
    }
    if (ret == board[y][x].size()) ret--;
    return ret;
}

void Game::box_boom(BoxZom *boxZom) {
    int x = boxZom->get_cor_x();
    int y = boxZom->get_cor_y();

    for (int i = max(0, x - 1); i < min(3, x + 2); ++i) {
        for (int j = max(1, y - 11); j < min(78, y + 21); ++j) {
            vector<int> ind = find_obj(i, j, PLANT);
            for (int i_ind :ind) {
                object_list[i_ind].second = true;
            }
        }
    }
}

void Game::throw_stone(CatapultZombie *catapultZombie) {
    int x = catapultZombie->get_cor_x();
    int y = catapultZombie->get_cor_y();
    for (int i = 0; i < y; ++i) {
        vector<int> ind = find_obj(x, i, PLANT);
        if (!ind.empty()) {
            catapultZombie->use_one_stone();
            if (ind.size() == 1) {
                if (((Plant*)object_list[ind[0]].first)->be_attacked(catapultZombie))
                    object_list[ind[0]].second = true;
            } else {
                //优先攻击南瓜下的植物
                unsigned short tmp = 0;
                if (((Plant*)object_list[ind[0]].first)->get_plant_type() != PUMPKIN) {
                    tmp = 0;
                } else tmp = 1;
                if (((Plant*)object_list[ind[tmp]].first)->be_attacked(catapultZombie)) {
                    object_list[ind[0]].second = true;
                    object_list[ind[1]].second = true;
                }
            }
            return;
        }
    }
}

void Game::set_text_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Game::update_zombie_step() {
    if (zombie_step < 4) {
        if (zombie_step == 0) {
            if (zombie_time_count >= 900) {
                zombie_step ++;
                zombie_time_count = 0;
            } else zombie_time_count ++;
        } else {
            if (zombie_time_count >= 1500) {
                zombie_step ++;
                zombie_time_count = 0;
            } else zombie_time_count ++;
        }
    }
}

void Game::generate_zombie() {
    update_zombie_step();
    //前三分钟：每20秒随机位置产生一个僵尸
    //第一阶段：普通僵尸，每1/5秒1/30概率生成一个，共5分钟
    //第二阶段：+路障僵尸+读报僵尸，每1/5秒1/30概率生成一个，共5分钟
    //第三阶段：+撑杆跳僵尸+小丑僵尸，每1/5秒1/30概率生成一个，共5分钟
    //第四阶段：+投石僵尸，每1/5秒1/30概率生成一个，这个有1/11概率是投石僵尸
    if (zombie_step == 0) {
        if (update_zombie_cd()) {
            int tmp_x = rand() % 3;
            object_list.emplace_back(new Zombie(tmp_x, 78), false);
        }
    } else if (zombie_step == 1) {
        if (rand() % 30 == 1) {
            int tmp_x = rand() % 3;
            object_list.emplace_back(new Zombie(tmp_x, 78), false);
        }
    } else if (zombie_step == 2) {
        if (rand() % 30 == 1) {
            int tmp_x = rand() % 3;
            int tmp_t = rand() % 3;
            if (tmp_t == 0) {
                object_list.emplace_back(new Zombie(tmp_x, 78), false);
            } else if (tmp_t == 1) {
                object_list.emplace_back(new Conehead(tmp_x, 78), false);
            } else if (tmp_t == 2) {
                object_list.emplace_back(new NewsZom(tmp_x, 78), false);
            }
        }
    } else if (zombie_step == 3) {
        if (rand() % 30 == 1) {
            int tmp_x = rand() % 3;
            int tmp_t = rand() % 5;
            if (tmp_t == 0) {
                object_list.emplace_back(new Zombie(tmp_x, 78), false);
            } else if (tmp_t == 1) {
                object_list.emplace_back(new Conehead(tmp_x, 78), false);
            } else if (tmp_t == 2) {
                object_list.emplace_back(new NewsZom(tmp_x, 78), false);
            } else if (tmp_t == 3) {
                object_list.emplace_back(new PoleVZom(tmp_x, 78), false);
            } else if (tmp_t == 4) {
                object_list.emplace_back(new BoxZom(tmp_x, 78), false);
            }
        }
    } else if (zombie_step == 4) {
        if (rand() % 30 == 1) {
            int tmp_x = rand() % 3;
            int tmp_t = rand() % 11;
            if (tmp_t == 0 || tmp_t == 1) {
                object_list.emplace_back(new Zombie(tmp_x, 78), false);
            } else if (tmp_t == 2 || tmp_t == 3) {
                object_list.emplace_back(new Conehead(tmp_x, 78), false);
            } else if (tmp_t == 4 || tmp_t == 5) {
                object_list.emplace_back(new NewsZom(tmp_x, 78), false);
            } else if (tmp_t == 6 || tmp_t == 7) {
                object_list.emplace_back(new PoleVZom(tmp_x, 78), false);
            } else if (tmp_t == 8 || tmp_t == 9) {
                object_list.emplace_back(new BoxZom(tmp_x, 78), false);
            } else if (tmp_t == 10) {
                object_list.emplace_back(new CatapultZombie(tmp_x, 78), false);
            }
        }
    }
}

bool Game::update_test_zombie_cd() {
    test_zombie_cd --;
    bool ret = test_zombie_cd <= 0;
    if (ret) test_zombie_cd = 25;
    return ret;
}

void Game::test_generate_zombie() {
    if (update_test_zombie_cd()) {
//        object_list.emplace_back(new Zombie(0, 78), false);
//        object_list.emplace_back(new Conehead(0, 78), false);
//        object_list.emplace_back(new NewsZom(0, 78), false);
//        object_list.emplace_back(new PoleVZom(0, 78), false);
//        object_list.emplace_back(new BoxZom(0, 78), false);
        object_list.emplace_back(new CatapultZombie(0, 78), false);
    }
}

Game::Game() {
    object_list.clear();

    cursor_x = -1;
    cursor_y = -1;
    store_cursor = -1;
    root_out = false;

    zombie_cd = 100;
    zombie_step = 0;
    zombie_time_count = 0;

    test_zombie_cd = 25;

    sun = 0;
    score = 0;
    init_board();
    srand((unsigned)time(nullptr));

    store_objects.clear();
    store_objects.emplace_back(new Sunflower(0, 0), -1);
    store_objects.emplace_back(new PeaShoot(0, 0), -1);
    store_objects.emplace_back(new DoublePea(0, 0), -1);
    store_objects.emplace_back(new SnowPea(0, 0), -1);
    store_objects.emplace_back(new WallNut(0, 0), -1);
    store_objects.emplace_back(new TallNut(0, 0), -1);
    store_objects.emplace_back(new Squash(0, 0), -1);
    store_objects.emplace_back(new CherryBoom(0, 0), -1);
    store_objects.emplace_back(new Gralic(0, 0), -1);
    store_objects.emplace_back(new Pumpkin(0, 0, nullptr), -1);

    //隐藏光标
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.bVisible = 0;
    cinfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
}

void Game::playing() {
    drawInterface(0);

    int ch;
    srand((unsigned) time(nullptr));
    clock_t last = clock();

    int sun_flag = 0;

    while (true) {
        clock_t now = clock();
        if (now - last < CLOCKS_PER_SEC / 5) continue;
        last = now;

        if (sun_flag == 4) {
            sun+=25;
            sun_flag = 0;
        } else sun_flag ++;
        //键盘控制
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) {
                for (auto &store_object : store_objects) {
                    if (store_object.second != -1) store_object.second = now - store_object.second;
                }
                for (auto &object : object_list) {
                    if (object.first->get_type() == ZOMBIE) {
                        if (((Zombie*)object.first)->get_ice_flag()) {
                            ((Zombie*)object.first)->set_ice_time(now - ((Zombie*)object.first)->get_ice_time());
                        }
                    }
                }
                system("pause");
                now = clock();
                for (auto &store_object : store_objects) {
                    if (store_object.second != -1) {
                        store_object.second = now - store_object.second;
                    }
                }
                for (auto &object : object_list) {
                    if (object.first->get_type() == ZOMBIE) {
                        if (((Zombie*)object.first)->get_ice_flag()) {
                            ((Zombie*)object.first)->set_ice_time(now - ((Zombie*)object.first)->get_ice_time());
                        }
                    }
                }
                COORD cursorPosition;
                cursorPosition.X = 0;
                cursorPosition.Y = 27;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
                cout << "                                          " << endl;
            }
            else if (ch == 98) {//b
                if (store_cursor == -1) store_cursor = 0;
            } else if (ch == 119) {//w
                if (store_cursor != -1 && cursor_y == -1) {//在商店里移动光标
                    if (store_cursor > 4) store_cursor -= 5;
                } else if (cursor_x > 0 || root_out)
                    cursor_x--;//在地块上移动光标
            } else if (ch == 115) {//s
                if (store_cursor != -1 && cursor_y == -1) {//在商店移动光标
                    if (store_cursor < store_objects.size() - 5) store_cursor += 5;
                } else if ((cursor_x != -1 && cursor_x < 2) || root_out)
                    cursor_x++;//在地块上移动光标
            } else if (ch == 100) {//d
                if (cursor_y == -1 && store_cursor != -1) {//在商店里移动光标
                    if (store_cursor < store_objects.size() - 1) store_cursor++;
                } else if ((cursor_y != -1 && cursor_y < 6) || root_out) {
                    cursor_y++;//在地块上移动光标
                }
            } else if (ch == 97) {//a
                if (cursor_y == -1 && store_cursor != -1) {
                    if (store_cursor > 0) store_cursor--;
                } else if (cursor_y > 0 || root_out)
                    cursor_y--;//在地块上移动光标
            } else if (ch == 13) {//Enter
                if (store_cursor != -1 && cursor_x == -1 && cursor_y == -1) {
                    cursor_x = 0;
                    cursor_y = 0;
                } else if (store_cursor != -1 && cursor_x != -1) {
                    // TODO --add plant
                    Plant* pl_tmp = nullptr;
                    if (store_objects[store_cursor].second == -1
                    || now - store_objects[store_cursor].second
                    >= store_objects[store_cursor].first->get_cd() * CLOCKS_PER_SEC) {
                        int tmp_y = cursor_y * 11 + 1;
                        if (can_be_planted()) {
                            if (store_cursor == 0) {
                                pl_tmp = new Sunflower(cursor_x, tmp_y);
                            } else if (store_cursor == 1) {
                                pl_tmp = new PeaShoot(cursor_x, tmp_y);
                            } else if (store_cursor == 2) {
                                pl_tmp = new DoublePea(cursor_x, tmp_y);
                            } else if (store_cursor == 3) {
                                pl_tmp = new SnowPea(cursor_x, tmp_y);
                            } else if (store_cursor == 4) {
                                pl_tmp = new WallNut(cursor_x, tmp_y);
                            } else if (store_cursor == 5) {
                                pl_tmp = new TallNut(cursor_x, tmp_y);
                            } else if (store_cursor == 6) {
                                pl_tmp = new Squash(cursor_x, tmp_y);
                            } else if (store_cursor == 7) {
                                pl_tmp = new CherryBoom(cursor_x, tmp_y);
                            } else if (store_cursor == 8) {
                                pl_tmp = new Gralic(cursor_x, tmp_y);
                            }
                        } else if (store_cursor == 9) {
                            vector<int> ind = find_obj(cursor_x, tmp_y, PLANT);
                            if (ind.size() == 1) {
                                cout << "here" << endl;
                                pl_tmp =
                                    new Pumpkin(cursor_x, tmp_y, object_list[ind[0]].first->get_name());
                            }
                        }
                        if (pl_tmp != nullptr) {
                            if (pl_tmp->get_cost() <= sun) {
                                store_objects[store_cursor].second = now;
                                sun -= pl_tmp->get_cost();
                                object_list.emplace_back(pl_tmp, false);
                            } else delete pl_tmp;
                        }
                    }
                    cursor_x = -1;
                    cursor_y = -1;
                    store_cursor = -1;
                } else if (root_out) {
                    vector <int> ind = find_obj(cursor_x, cursor_y * 11 + 1, PLANT);
                    if (ind.size() == 1) {
                        object_list[ind[0]].second = true;
                    } else if (ind.size() == 2) {
                        int tmp_ind = ind[0];
                        if (((Plant*)object_list[tmp_ind].first)->get_plant_type()
                        != PUMPKIN) tmp_ind = ind[1];
                        object_list[tmp_ind].second = true;
                    }
                    root_out = false;
                    cursor_x = -1;
                    cursor_y = -1;
                }
            } else if (ch == 120) {//x
                store_cursor = -1;
                cursor_x = -1;
                cursor_y = -1;
            } else if (ch == 114) {//r
                root_out = true;
                cursor_x = 0;
                cursor_y = 0;
            }
        }

        //处理object
        bool tmp_flag = false;
        for (int i = 0; i < object_list.size(); ++i) {
            //处理僵尸
            if (object_list[i].first->get_type() == ZOMBIE) {
                Zombie* zom_tmp;
                zom_tmp = (Zombie*)(object_list[i].first);
                zom_tmp->process_iced(now);
                if (zom_tmp->get_cor_y() <= 0) {
                    tmp_flag = true;
                    cout << endl << "GAME OVER!" << endl << endl;
                    break;
                }
                if (zom_tmp->get_zombie_type() == CATAPULT) {
                    int tx = zom_tmp->get_cor_x();
                    int ty = zom_tmp->get_cor_y();
                    if (((CatapultZombie*)zom_tmp)->is_move() || !exist_plant(tx, ty)) {
                        //前进附带碾压效果
                        zom_tmp->move();
                        ty = zom_tmp->get_cor_y();
                        vector <int> ind = find_obj(tx, ty, PLANT);
                        for (int i_ind : ind) {
                            object_list[i_ind].second = true;
                        }
                    } else {
                        //停下来投石
                        throw_stone((CatapultZombie*)zom_tmp);
                    }
                } else {
                    zom_tmp->move();
                    int tx = zom_tmp->get_cor_x();
                    int ty = zom_tmp->get_cor_y();
                    vector<int> ind = find_obj(tx, ty, PLANT);
                    if (!ind.empty()) {
                        //僵尸遇到植物
                        zom_tmp->revoke_move();
                        Plant *pla_tmp;
                        int t_ind = ind[0];
                        if (ind.size() == 1) {
                            t_ind = ind[0];
                            pla_tmp = (Plant *) (object_list[t_ind].first);
                            if (zom_tmp->get_zombie_type() == POLE && pla_tmp->get_plant_type() == WALLNUT) {
                                PoleVZom *pvz_tmp;
                                pvz_tmp = (PoleVZom *) (zom_tmp);
                                WallNut *wn_tmp;
                                wn_tmp = (WallNut *) (pla_tmp);
                                if (pvz_tmp->is_jump(wn_tmp->get_nut_type() == TALL)) {
                                    pvz_tmp->jump_to(pla_tmp->get_cor_y() - 1);
                                    continue;
                                }
                            }
                        } else {
                            pla_tmp = (Plant *) (object_list[t_ind].first);
                            if (pla_tmp->get_plant_type() != PUMPKIN) {
                                if (pla_tmp->get_plant_type() == WALLNUT && zom_tmp->get_zombie_type() == POLE) {
                                    WallNut *wn_tmp;
                                    wn_tmp = (WallNut *) pla_tmp;
                                    PoleVZom *pvz_tmp;
                                    pvz_tmp = (PoleVZom *) zom_tmp;
                                    if (pvz_tmp->is_jump(wn_tmp->get_nut_type() == TALL)) {
                                        pvz_tmp->jump_to(pla_tmp->get_cor_y() - 1);
                                    }
                                }
                                t_ind = ind[1];
                                pla_tmp = (Plant *) (object_list[t_ind].first);
                            }
                            assert(pla_tmp->get_plant_type() == PUMPKIN);
                        }
                        if (pla_tmp->be_attacked(zom_tmp)) {
                            object_list[t_ind].second = true;
                        }
                    }
                }
                if (zom_tmp->get_zombie_type() == BOX) {
                    if (((BoxZom*)zom_tmp)->is_boom()) {
                        box_boom((BoxZom*)zom_tmp);
                        object_list[i].second = true;
                    }
                }
                //处理植物
            } else if (object_list[i].first->get_type() == PLANT){
                // TODO --add plant -- if it need interaction
                Plant* pla_tmp;
                pla_tmp = (Plant*)(object_list[i].first);
                if (pla_tmp->get_plant_type() == PEASHOOT) {
                    PeaShoot* pea_tmp;
                    pea_tmp = (PeaShoot*)(pla_tmp);
                    //豌豆射手发射豌豆
                    if (exist_zombie(pea_tmp->get_cor_x()) && pea_tmp->update_cd())
                        object_list.emplace_back(pea_tmp->generate_bullet(), false);
                }
                if (pla_tmp->get_plant_type() == SUNFLOWER) {
                    Sunflower* sf_tmp;
                    sf_tmp = (Sunflower*)(pla_tmp);
                    if (sf_tmp->update_cd())
                        sun += sf_tmp->get_sunplus();
                }
                if (pla_tmp->get_plant_type() == SQUASH) {
                    int tx = pla_tmp->get_cor_x();
                    int ty = pla_tmp->get_cor_y();
                    bool attack_flag = false;
                    for (int j = max(0, ty - 6); j < min(board_width, ty + 16); ++j) {
                        vector <int> ind = find_obj(tx, j, ZOMBIE);
                        if (!ind.empty()) {
                            attack_flag = true;
                            for (int k : ind) {
                                object_list[k].second = true;
                            }
                        }
                    }
                    if (attack_flag) object_list[i].second = true;
                }
                if (pla_tmp->get_plant_type() == CHERRY) {
                    CherryBoom* cherry_tmp;
                    cherry_tmp = (CherryBoom*) (pla_tmp);
                    if (cherry_tmp->update_cd()) {
                        int tx = cherry_tmp->get_cor_x();
                        int ty = cherry_tmp->get_cor_y();
                        for (int ix = max(0, tx - 1); ix < min(3, tx + 2); ++ix) {
                            for (int iy = max(1, ty - 11); iy < min(78, ty + 21); ++iy) {
                                vector<int> ind = find_obj(ix, iy, ZOMBIE);
                                if (!ind.empty()) {
                                    for (int k : ind) {
                                        object_list[k].second = true;
                                    }
                                }
                            }
                        }
                        object_list[i].second = true;
                    }
                }
            }
        }

        if (tmp_flag) break;

        //处理豌豆
        update_board();
        for (auto &i : object_list) {
            if (i.first->get_type() == BULLET) {
                Bullet* bul_tmp;
                bul_tmp = (Bullet*)(i.first);
                int tx = i.first->get_cor_x();
                int ty = i.first->get_cor_y();
                vector <int> ind = find_obj(tx, ty, ZOMBIE);
                if ((bul_tmp->get_cor_y() + i.first->get_speed()) >= board_width) {
                    i.second = true;
                } else if (!ind.empty()) {
                    Zombie* zom_tmp;
                    zom_tmp = (Zombie*)(object_list[ind[0]].first);
                    if (zom_tmp->be_attacked(bul_tmp, now)) {
                        object_list[ind[0]].second = true;
                    }
                    i.second = true;
                } else {
                    i.first->move();
                    tx = i.first->get_cor_x();
                    ty = i.first->get_cor_y();
                    ind = find_obj(tx, ty, ZOMBIE);
                    if (!ind.empty()) {
                        Zombie* zom_tmp;
                        zom_tmp = (Zombie*)(object_list[ind[0]].first);
                        if (zom_tmp->be_attacked(bul_tmp, now)) {
                            object_list[ind[0]].second = true;
                        }
                        i.second = true;
                    }
                }
            }
        }

        int obj_size = object_list.size();
        for (int i = 0; i < obj_size; ++i) {
            if (object_list[i].second) {
                if (object_list[i].first->get_type() == ZOMBIE) score += 10;
                delete object_list[i].first;
                object_list.erase(object_list.begin() + i);
                obj_size--;
                i--;
            }
        }

        //产生僵尸
        generate_zombie();
//        test_generate_zombie();

        update_board();
        drawInterface(now);
    }
}



void Game::drawInterface(clock_t now) {
    //输出第一行
    if (cursor_x == 0 && cursor_y == 0) cout << "+";
    else cout << "#";
    for (int i = 0; i < (board_width + 10) / 11 - 1; i++) {
        if (cursor_x == 0 && cursor_y == i)
            cout << "----------";
        else cout << "##########";
        if (cursor_x == 0 && (cursor_y == i || cursor_y == i + 1)) cout << "+";
        else cout << "#";
    }
    for (int i = 0; i < 11; ++i) cout << "=";
    cout << endl;

    for (int i = 0; i < board_height; ++i) {
        //输出每一列第一行
        for (int j = 0; j < (board_width + 10) / 11; ++j) {
            if (cursor_x == i && (cursor_y == j || cursor_y == j - 1))
                cout << "|";
            else cout << "#";
            cout << "          ";
        }
        cout << endl;

        //输出每一列第二行
        for (int j = 0; j < board_width + 9; ++j) {
            if (j >= board_width) {
                cout << " ";
                continue;
            }
            if (!(j % 11)) {
                if (board[j][i].empty()) {
                    if (cursor_x == i && (cursor_y == j / 11 || cursor_y == j / 11 - 1)) cout << "|";
                    else cout << "#";
                } else {
                    Object* out_tmp = board[j][i][get_printed(i, j)];
                    bool ice_flag = false;
                    if (out_tmp->get_type() == BULLET) {
                        if (((Bullet*) out_tmp)->get_bullet_type() == ICE) {
                            ice_flag = true;
                        }
                    }
                    if (ice_flag) set_text_color(FOREGROUND_BLUE);
                    cout << out_tmp->get_name();
                    if (ice_flag) set_text_color(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
                    int name_len = strlen(out_tmp->get_name());
                    int delta = name_len;
                    for (int k = 1; k < name_len && j + k < board_width; ++k) {
                        if (!board[j + k][i].empty()
                        && board[j + k][i][get_printed(i, j + k)]->get_type() != BULLET) {
                            //修改光标位置
                            COORD cursorPosition;
                            cursorPosition.Y = (short) (i * 4 + 2);
                            cursorPosition.X = (short) (j + k);
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
                            delta = k;
                            break;
                        }
                    }
                    j += delta - 1;
                }
            } else {
                if (board[j][i].empty()) {
                    cout << " ";
                } else {
                    Object* out_tmp = board[j][i][get_printed(i, j)];
                    bool ice_flag = false;
                    if (out_tmp->get_type() == BULLET) {
                        if (((Bullet*) out_tmp)->get_bullet_type() == ICE) {
                            ice_flag = true;
                        }
                    }
                    if (ice_flag) set_text_color(FOREGROUND_BLUE);
                    cout << out_tmp->get_name();
                    if (ice_flag) set_text_color(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
                    int name_len = strlen(out_tmp->get_name());
                    int delta = name_len;
                    for (int k = 1; k < name_len && j + k < board_width; ++k) {
                        if (!board[j + k][i].empty()
                        && board[j + k][i][get_printed(i, j + k)]->get_type() != BULLET) {
                            //修改光标位置
                            COORD cursorPosition;
                            cursorPosition.Y = (short) (i * 4 + 2);
                            cursorPosition.X = (short) (j + k);
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
                            delta = k;
                            break;
                        }
                    }
                    j += delta - 1;
                }
            }
        }
        for (int j = 0; j < 11; ++j) cout << " ";
        cout << endl;

        //输出每一列第三行
        for (int j = 0; j < board_width + 9; ++j) {
            if (j >= board_width) {
                cout << " ";
                continue;
            }
            if (!(j % 11)) {
                if (board[j][i].empty()) {
                    if (cursor_x == i && (cursor_y == j / 11 || cursor_y == j / 11 - 1)) cout << "|";
                    else cout << "#";
                } else {
                    if (board[j][i][get_printed(i, j)]->get_type() != BULLET) {
                        int name_len = strlen(board[j][i][get_printed(i, j)]->get_name());
                        cout << left << setw(name_len) << setfill(' ') << board[j][i][get_printed(i, j)]->get_blood();
                        int delta = name_len;
                        for (int k = 1; k < name_len && j + k < board_width; ++k) {
                            if (!board[j + k][i].empty()
                                && board[j + k][i][get_printed(i, j + k)]->get_type() != BULLET) {
                                //修改光标位置
                                COORD cursorPosition;
                                cursorPosition.Y = (short) (i * 4 + 3);
                                cursorPosition.X = (short) (j + k);
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
                                delta = k;
                                break;
                            }
                        }
                        j += delta - 1;
                    } else cout << "#";
                }
            } else {
                if (board[j][i].empty()) {
                    cout << " ";
                } else {
                    if (board[j][i][get_printed(i, j)]->get_type() != BULLET) {
                        int name_len = strlen(board[j][i][get_printed(i, j)]->get_name());
                        cout << left << setw(name_len) << setfill(' ') << board[j][i][get_printed(i, j)]->get_blood();
                        int delta = name_len;
                        for (int k = 1; k < name_len && j + k < board_width; ++k) {
                            if (!board[j + k][i].empty()
                                && board[j + k][i][get_printed(i, j + k)]->get_type() != BULLET) {
                                //修改光标位置
                                COORD cursorPosition;
                                cursorPosition.Y = (short) (i * 4 + 3);
                                cursorPosition.X = (short) (j + k);
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
                                delta = k;
                                break;
                            }
                        }
                        j += delta - 1;
                    } else cout << " ";
                }
            }
        }
        cout << endl;

        //输出列间间隔行
        if ((cursor_x == i || cursor_x == i + 1) && cursor_y == 0) cout << "+";
        else cout << "#";
        for (int j = 0; j < (board_width + 10) / 11 - 1; ++j) {
            if ((cursor_x == i || cursor_x == i + 1) && cursor_y == j)
                cout << "----------";
            else cout << "##########";
            if ((cursor_x == i || cursor_x == i + 1) && (cursor_y == j || cursor_y == j + 1)) cout << "+";
            else cout << "#";
        }
        for (int j = 0; j < 11; ++j) cout << "=";
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < board_width + 11; i++) cout << "=";
    cout << endl;
    cout << "[Store]             " << "sunshine: " << sun << " | " << "score: " << score << endl;
    for (int i = 0; i < board_width + 11; i++) cout << "-";
    cout << endl;
    //输出商店内植物，商店每5个一行
    for (int i = 0; i < store_objects.size(); ++i) {
        if (i && i % 5 == 0) cout << endl;
        if (store_cursor == i) {
            cout << '[';
            double i_cd = store_objects[i].first->get_cd() * CLOCKS_PER_SEC;
            if (store_objects[i].second != -1
            && now - store_objects[i].second < i_cd) {
                const char* ch_tmp = store_objects[i].first->get_name();
                int len = strlen(ch_tmp);
                int white = int(len - (now - store_objects[i].second) / i_cd * len);
                white = min(len, white + 1);
                set_text_color(FOREGROUND_BLUE);
                for (int j = 0; j < white; ++j) cout << setw(1) << ch_tmp[j];
                set_text_color(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
                for (int j = white; j < len; ++j) cout << setw(1) << ch_tmp[j];
            } else cout << store_objects[i].first->get_name();
            cout << ']';
        } else {
            cout << ' ' ;
            double i_cd = store_objects[i].first->get_cd() * CLOCKS_PER_SEC;
            if (store_objects[i].second != -1
                && now - store_objects[i].second < i_cd) {
                const char* ch_tmp = store_objects[i].first->get_name();
                int len = strlen(ch_tmp);
                int white = int(len - (now - store_objects[i].second) / i_cd * len);
                set_text_color(FOREGROUND_BLUE);
                for (int j = 0; j < white; ++j) cout << setw(1) << ch_tmp[j];
                set_text_color(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
                for (int j = white; j < len; ++j) cout << setw(1) << ch_tmp[j];
            } else cout << store_objects[i].first->get_name();
            cout << ' ';
        }
        cout << store_objects[i].first->get_cost();
        if (i == store_objects.size() - 1) cout << endl;
        else cout << '\t';
    }
    for (int i = 0; i < board_width + 11; i++) cout << "-";
    cout << endl;
    cout << "Pause: [esc]" << endl;
    cout << "Enter the store: b" << endl;
    cout << "Move cursor in the store: w & s & a & d" << endl;
    cout << "Buy the plant: [enter]" << endl;
    cout << "Select the position where to plant: w & s & a & d" << endl;
    cout << "Plant the chosen one on the chosen position: [enter]" << endl;
    cout << "Cancel the planting: x; Root out the plant: r" << endl;
}