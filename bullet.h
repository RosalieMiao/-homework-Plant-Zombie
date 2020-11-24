//
// Created by d on 2020/10/4.
//

#ifndef PLANTS_ZOMBIES_BULLET_H
#define PLANTS_ZOMBIES_BULLET_H
#include "object.h"

class Bullet : public Object {
    const int attack;
 protected:
    Bullet_type bullet_type;
 public:
    ~Bullet() override {delete name; name = nullptr;}
    Bullet(double x, double y);
    int get_attack() const ;
    Bullet_type get_bullet_type() const;
    int get_blood() const override;
};

class IceBullet : public Bullet {
 public:
    IceBullet(double x, double y);
};

#endif //PLANTS_ZOMBIES_BULLET_H
