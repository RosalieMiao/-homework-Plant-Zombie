//
// Created by d on 2020/11/15.
//

#ifndef PLANTS_ZOMBIES_MYHEAD_H
#define PLANTS_ZOMBIES_MYHEAD_H

#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <conio.h>
#include <cstdlib>
using namespace std;

#define board_width 79
#define board_height 3

#define bullet_speed 1
#define bullet_attack 20

enum Plant_type {SUNFLOWER, PEASHOOT, WALLNUT, SQUASH, CHERRY, GRALIC, PUMPKIN};
enum Nut_type {LOW, TALL};
enum Zombie_type {ZOM, CON, NEW, POLE, BOX, CATAPULT};
enum Bullet_type {SIMPLE, ICE};

#endif //PLANTS_ZOMBIES_MYHEAD_H
