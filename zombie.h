//
// Created by d on 2020/9/25.
//

#ifndef PLANTS_ZOMBIES_ZOMBIES_H
#define PLANTS_ZOMBIES_ZOMBIES_H
#include "bullet.h"
class Zombie : public Object{
    bool ice_flag;
    clock_t ice_time;
 protected:
    int attack;
    Zombie_type  zombie_type;
    int blood;
 public:
    ~Zombie() override {delete name; name= nullptr; }
    Zombie(double x, double y);
    int get_attack() const ;
    bool be_attacked(Bullet * bullet, clock_t time);
    void process_iced(clock_t time);
    void another_line();
    Zombie_type get_zombie_type() const;
    int get_blood() const override;
    bool get_ice_flag() const;
    clock_t get_ice_time() const;
    void set_ice_time(clock_t _ice_time);
};

class Conehead : public Zombie {
 public:
    Conehead(double x, double y);
};

class NewsZom : public Zombie {
    bool Newspaper;
 public:
    NewsZom(double x, double y);
    void update_flag();
};

class PoleVZom : public Zombie {
    bool pole;
 public:
    PoleVZom(double x, double y);
    bool is_jump(bool is_tallnut);
    void jump_to(double y);
};

class BoxZom : public Zombie {
 public:
    BoxZom(double x, double y);
    bool is_boom();
};

class CatapultZombie : public Zombie {
    int stone_num;
 public:
    CatapultZombie(double x, double y);
    bool is_move();
    void use_one_stone();
};

#endif //PLANTS_ZOMBIES_ZOMBIES_H
