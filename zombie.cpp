//
// Created by d on 2020/9/25.
//

#include "zombie.h"

Zombie::Zombie(double x, double y) {
    name = new char[7];
    strcpy(name, "Zombie");
    objects_type = ZOMBIE;
    cor_x = x;
    cor_y = y - 0.25;
    blood = 270;
    attack = 20;
    speed = - 0.4;
    ice_flag = false;
    zombie_type = ZOM;
}

int Zombie::get_attack() const {
    return attack;
}

bool Zombie::be_attacked(Bullet* bullet, clock_t time) {
    blood -= bullet->get_attack();
    if (bullet->get_bullet_type() == ICE) {
        ice_time = time;
        if (!ice_flag) {
            ice_flag = true;
            speed /= 2;
        }
    }
    if (zombie_type == NEW) {
        NewsZom* tmp;
        tmp = dynamic_cast<NewsZom*>(this);
        tmp->update_flag();
    }
    return blood <= 0;
}

void Zombie::process_iced(clock_t time) {
    if (!ice_flag) return;
    if (time - ice_time >= 10 * CLOCKS_PER_SEC) {
        ice_flag = false;
        speed *= 2;
    }
}

void Zombie::another_line() {
    if (cor_x == 0 || cor_x == 2) cor_x = 1;
    else cor_x = (rand() % 2 ? 0 : 2);
}

Zombie_type Zombie::get_zombie_type() const {
    return zombie_type;
}

int Zombie::get_blood() const {
    return blood;
}

bool Zombie::get_ice_flag() const {
    return ice_flag;
}

clock_t Zombie::get_ice_time() const {
    return ice_time;
}

void Zombie::set_ice_time(clock_t _ice_time) {
    ice_time = _ice_time;
}

Conehead::Conehead(double x, double y) : Zombie(x, y) {
    delete name;
    name = new char[9];
    strcpy(name, "conehead");

    blood = 640;
    zombie_type = CON;
}

NewsZom::NewsZom(double x, double y) : Zombie(x, y) {
    delete name;
    name = new char[8];
    strcpy(name, "NewsZom");

    blood = 420;
    zombie_type = NEW;
    Newspaper = true;
}

void NewsZom::update_flag( ) {
    if (Newspaper && blood <= 270) {
        Newspaper = false;
        delete name;
        name = new char[4];
        strcpy(name, "Zom");
        speed /= 0.3;
    }
}

PoleVZom::PoleVZom(double x, double y) : Zombie(x, y) {
    delete name;
    name = new char[9];
    strcpy(name, "PoleVZom");

    blood = 500;
    zombie_type = POLE;
    pole = true;
}

bool PoleVZom::is_jump(bool is_tallnut) {
    if (pole) {
        if (is_tallnut) {
            pole = false;
            return false;
        }
        return true;
    }
    return false;
}

void PoleVZom::jump_to(double y) {
    cor_y = y;
}

BoxZom::BoxZom(double x, double y) : Zombie(x, y) {
    delete name;
    name = new char[7];
    strcpy(name, "BoxZom");

    blood = 500;
    speed *= 2.8;
    zombie_type = BOX;
}

bool BoxZom::is_boom() {
    return rand() % 100 < 3;
}

CatapultZombie::CatapultZombie(double x, double y) : Zombie(x, y) {
    delete name;
    name = new char[14];
    strcpy(name, "CatapultZombie");

    blood = 850;
    speed *= 2;
    attack = 15;
    zombie_type = CATAPULT;

    stone_num = 20;
}

bool CatapultZombie::is_move() {
    return cor_y > 56 || !stone_num;
}

void CatapultZombie::use_one_stone() {
    stone_num --;
}
