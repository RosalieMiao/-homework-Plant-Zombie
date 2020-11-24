//
// Created by d on 2020/9/25.
//

#ifndef PLANTS_ZOMBIES_PLANT_H
#define PLANTS_ZOMBIES_PLANT_H

#include "zombie.h"

class Plant : public Object{
 protected:
    int cost;
    int blood;
    Plant_type plant_type;
    double cd;
 public:
    ~Plant() override { delete name; name = nullptr; }
    Plant(double x, double y);
    int get_cost() const ;
    Plant_type get_plant_type() const ;
    bool be_attacked(Zombie* zombie);
    double get_cd() const;
    int get_blood() const override;
};

class Sunflower: public Plant {
    int sunplus;
    int gen_cd;
 public:
    Sunflower(double x, double y);
    int get_sunplus() const ;
    bool update_cd();
};

class PeaShoot: public Plant {
 protected:
    int shoot_cd;
    int shoot_cd_limit;
    Bullet_type bullet_type;
 public:
    PeaShoot(double x, double y);
    Bullet* generate_bullet();
    bool update_cd();
};

class DoublePea: public PeaShoot {
 public:
    DoublePea(double x, double y);
};

class SnowPea: public PeaShoot {
 public:
    SnowPea(double x, double y);
};

class WallNut : public Plant {
 protected:
    Nut_type nut_type;
 public:
    WallNut(double x, double y);
    Nut_type get_nut_type() const;
};

class TallNut : public WallNut {
 public:
    TallNut(double x, double y);
};

class Squash : public Plant {
 public:
    Squash(double x, double y);
};

class CherryBoom : public Plant {
    double boom_cd;
 public:
    CherryBoom(double x, double y);
    bool update_cd();
};

class Gralic : public Plant {
 public:
    Gralic(double x, double y);
};

class Pumpkin : public Plant {
 public:
    Pumpkin(double x, double y, const char* _name);
};


#endif //PLANTS_ZOMBIES_PLANT_H
