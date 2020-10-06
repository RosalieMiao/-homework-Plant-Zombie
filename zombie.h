//
// Created by d on 2020/9/25.
//

#ifndef PLANTS_ZOMBIES_ZOMBIES_H
#define PLANTS_ZOMBIES_ZOMBIES_H
#include "object.h"
class Zombie : public Object{
    int blood;
    int attack;
 public:
    Zombie(int x, int y);
    int get_attack() const ;
    bool be_attacked(int at);
};

#endif //PLANTS_ZOMBIES_ZOMBIES_H
