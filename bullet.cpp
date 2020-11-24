//
// Created by d on 2020/10/4.
//

#include "bullet.h"

Bullet::Bullet(double x, double y): attack(bullet_attack) {
    bullet_type = SIMPLE;
    name = new char[2];
    strcpy(name, "o");
    speed = bullet_speed;
    objects_type = BULLET;
    cor_x = x;
    cor_y = y;
}

int Bullet::get_attack() const {
    return attack;
}

Bullet_type Bullet::get_bullet_type() const {
    return bullet_type;
}

IceBullet::IceBullet(double x, double y) : Bullet(x, y) {
    bullet_type = ICE;
}

int Bullet::get_blood() const {
    return 0;
}