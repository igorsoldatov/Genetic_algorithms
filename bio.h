//
// Created by sabster on 13.10.17.
//

#ifndef EVOLUTION_LIVE_ORGANISMS_BIO_H
#define EVOLUTION_LIVE_ORGANISMS_BIO_H

#include "config.h"
#include <cstdlib>
#include <cmath>
#include <list>
#include <GL/gl.h>

struct Code_bio
{
    int maxltime;
    float minspeed, maxspeed;
    int maxturn;
};

class bio {
public:
    Code_bio code;      /// генетический код
    float x, y, dx, dy; /// координаты и скорость
    bool life;          /// жив или мертв
    float w, h;         /// линейные размеры
    int num;            /// личный номер
    int lifetime;       /// продолжительность жизни
    float range;        /// радиус обнаружения хищника

    bio(void);
    void set(int a, int b);
    void turn(float vect, int deg);
    void collx();
    void colly();
    void runaway(float vect, float x2, float y2);
    Code_bio childcode(Code_bio c1, Code_bio c2);
    void draw();
};


#endif //EVOLUTION_LIVE_ORGANISMS_BIO_H
