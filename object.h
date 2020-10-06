//
// Created by d on 2020/10/4.
//

#ifndef PLANTS_ZOMBIES_OBJECT_H
#define PLANTS_ZOMBIES_OBJECT_H
enum Object_type {ZOMBIE, PLANT, BULLET};
class Object {
 protected:
    double cor_x;
    double cor_y;
    double speed;
    Object_type objects_type;
 public:
    virtual ~Object() = default;
    Object_type get_type() const;
    int get_cor_x() const;
    int get_cor_y() const;
    double get_speed() const;
    void move();
    void revoke_move();
};

#endif //PLANTS_ZOMBIES_OBJECT_H
