//
// Created by d on 2020/9/25.
//

#include "plant.h"

int Plant::get_cost() const {
    return cost;
}

Plant_type Plant::get_plant_type() const {
    return plant_type;
}

bool Plant::be_attacked(int at) {
    blood -= at;
    return blood <= 0;
}
/*
Sunflower::Sunflower(int x, int y, int plant_id) {
    objects_type = PLANT;
    plant_type = SUNFLOWER;
    cor_x = x;
    cor_y = y;
    id = plant_id;
    cost = 50;
    blood = 10;
    speed = 5;
    sunplus = 50;
}

int Sunflower::get_speed() const {
    return speed;
}

int Sunflower::get_sunplus() const {
    return sunplus;
}
*/
PeaShoot::PeaShoot(int x, int y) {
    objects_type = PLANT;
    plant_type = PEASHOOT;
    cor_x = x;
    cor_y = y;
    cost = 100;
    blood = 2;
    cd = 0;
    cd_piece = 0.5;
    speed = 0;
}

Bullet* PeaShoot::generate_bullet() {
    Bullet* ret;
    ret = new Bullet(cor_x, cor_y + 1);
    return ret;
}

bool PeaShoot::update_cd() {
    cd += cd_piece;
    bool ret = (cd == 1);
    if (ret) cd = 0;
    return ret;
}