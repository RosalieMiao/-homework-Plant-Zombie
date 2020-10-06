//
// Created by d on 2020/9/25.
//

#ifndef PLANTS_ZOMBIES_PLANT_H
#define PLANTS_ZOMBIES_PLANT_H

#include "bullet.h"
enum Plant_type {SUNFLOWER, PEASHOOT};

class Plant : public Object{
 protected:
    int cost;
    int blood;
    Plant_type plant_type;
 public:
    int get_cost() const ;
    Plant_type get_plant_type() const ;
    bool be_attacked(int at);
};
/*
class Sunflower: public Plant {
    int speed;
    int sunplus;
 public:
    Sunflower(int x, int y, int plant_id);
    int get_speed() const ;
    int get_sunplus() const ;
};*/

class PeaShoot: public Plant {
    double cd;
    double cd_piece;
 public:
    PeaShoot(int x, int y);
    Bullet* generate_bullet();
    bool update_cd();
};

#endif //PLANTS_ZOMBIES_PLANT_H
