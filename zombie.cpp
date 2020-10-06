//
// Created by d on 2020/9/25.
//

#include "zombie.h"

Zombie::Zombie(int x, int y) {
    objects_type = ZOMBIE;
    cor_x = x;
    cor_y = y - 0.25;
    blood = 5;
    attack = 2;
    speed = -0.25;
}

int Zombie::get_attack() const {
    return attack;
}

bool Zombie::be_attacked(int at) {
    blood -= at;
    return blood <= 0;
}