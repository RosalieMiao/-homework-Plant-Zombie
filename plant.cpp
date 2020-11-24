//
// Created by d on 2020/9/25.
//

#include "plant.h"

Plant::Plant(double x, double y) {
    cor_x = x;
    cor_y = y;
    plant_type = PEASHOOT;
    cd = 7.5;
}

int Plant::get_cost() const {
    return cost;
}

Plant_type Plant::get_plant_type() const {
    return plant_type;
}

bool Plant::be_attacked(Zombie* zombie) {
    blood -= zombie->get_attack();
    if (plant_type == GRALIC) zombie->another_line();
    return blood <= 0;
}

double Plant::get_cd() const {
    return cd;
}

int Plant::get_blood() const {
    return blood;
}

Sunflower::Sunflower(double x, double y) : Plant(x, y) {
    name = new char[10];
    strcpy(name, "SunFlower");
    plant_type = SUNFLOWER;
    cost = 50;
    blood = 300;
    gen_cd = 120;
    speed = 0;
    sunplus = 25;
}

int Sunflower::get_sunplus() const {
    return sunplus;
}

bool Sunflower::update_cd() {
    gen_cd --;
    bool ret = (gen_cd <= 0);
    if (ret) gen_cd = 100;
    return ret;
}

PeaShoot::PeaShoot(double x, double y) : Plant(x, y) {
    name = new char[9];
    strcpy(name, "PeaShoot");
    plant_type = PEASHOOT;
    bullet_type = SIMPLE;
    cost = 100;
    blood = 300;
    shoot_cd = 8;
    shoot_cd_limit = 8;
    speed = 0;
}

Bullet* PeaShoot::generate_bullet() {
    if (bullet_type == SIMPLE) {
        Bullet *ret;
        ret = new Bullet(cor_x, cor_y);
        return ret;
    } else {
        IceBullet *ret;
        ret = new IceBullet(cor_x, cor_y);
        return ret;
    }
}

bool PeaShoot::update_cd() {
    shoot_cd --;
    bool ret = (shoot_cd <= 0);
    if (ret) shoot_cd = shoot_cd_limit;
    return ret;
}

DoublePea::DoublePea(double x, double y): PeaShoot(x, y) {
    delete []name;
    name = new char[10];
    strcpy(name, "DoublePea");
    shoot_cd = 4;
    shoot_cd_limit = 4;
    cost = 200;
}

SnowPea::SnowPea(double x, double y) : PeaShoot(x, y) {
    delete []name;
    name = new char[8];
    strcpy(name, "SnowPea");
    bullet_type = ICE;
    cost = 175;
}

WallNut::WallNut(double x, double y) : Plant(x, y) {
    name = new char[8];
    strcpy(name, "WallNut");
    plant_type = WALLNUT;
    cost = 50;
    blood = 4000;
    nut_type = LOW;
    cd = 30;
}

Nut_type WallNut::get_nut_type() const {
    return nut_type;
}

TallNut::TallNut(double x, double y) : WallNut(x, y) {
    strcpy(name, "TallNut");
    nut_type = TALL;
    cost = 125;
    blood *= 2;
}

Squash::Squash(double x, double y) : Plant(x, y) {
    name = new char[7];
    strcpy(name, "Squash");
    cost = 50;
    blood = 300;
    plant_type = SQUASH;
    cd = 30;
}

CherryBoom::CherryBoom(double x, double y) : Plant(x, y) {
    name = new char[11];
    strcpy(name, "CherryBoom");
    cost = 150;
    blood = 300;
    plant_type = CHERRY;
    boom_cd = 5;
    cd = 50;
}

bool CherryBoom::update_cd() {
    boom_cd --;
    return boom_cd <= 0;
}

Gralic::Gralic(double x, double y) : Plant(x, y) {
    name = new char[7];
    strcpy(name, "Gralic");
    cost = 50;
    blood = 400;
    plant_type = GRALIC;
}

Pumpkin::Pumpkin(double x, double y, const char* _name) : Plant(x, y) {
    if (_name == nullptr) {
        name = new char[8];
        strcpy(name, "Pumpkin");
    } else {
        name = new char[strlen(_name)];
        strcpy(name, _name);
        strncpy(name, "Pum", 3);
    }
    cost = 125;
    blood = 4000;
    plant_type = PUMPKIN;
    cd = 30;
}