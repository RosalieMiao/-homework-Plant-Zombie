//
// Created by d on 2020/10/4.
//

#include "object.h"

Object::Object() {
    name = nullptr;
    cor_x = 0;
    cor_y = 0;
    speed = 0;
    objects_type = PLANT;
}

Object_type Object::get_type() const {
    return objects_type;
}

int Object::get_cor_x() const {
    return int(cor_x);
}

int Object::get_cor_y() const {
    return int(cor_y);
}

const char* Object::get_name() const {
    return name;
}

void Object::move() {
    cor_y += speed;
}

void Object::revoke_move() {
    cor_y -= speed;
}

double Object::get_speed() const {
    return speed;
}
int Object::get_blood() const {
    return 0;
}
