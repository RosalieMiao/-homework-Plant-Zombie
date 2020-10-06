//
// Created by d on 2020/10/4.
//

#ifndef PLANTS_ZOMBIES_BULLET_H
#define PLANTS_ZOMBIES_BULLET_H
#define bullet_speed 0.5
#define bullet_attack 1
#include "object.h"
class Bullet : public Object {
    const int attack;
 public:
    Bullet(double x, double y): attack(bullet_attack) {
        speed = bullet_speed;
        objects_type = BULLET;
        cor_x = x;
        cor_y = y;
    }
    int get_attack() const ;
};

#endif //PLANTS_ZOMBIES_BULLET_H
