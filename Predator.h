//
// Created by sabster on 13.10.17.
//

#ifndef EVOLUTION_LIVE_ORGANISMS_PREDATOR_H
#define EVOLUTION_LIVE_ORGANISMS_PREDATOR_H

#include "config.h"
#include "bio.h"
#include <cstdlib>
#include <cmath>
#include <GL/gl.h>

class Predator {
public:
    float x,y,dx,dy,speed;
    bool life;
    float w,h;
    int num;
    int lifetime;
    int aim_id;    // идентификатор цели
    float range;
    float hungry;

    Predator();
    void Set(int _x, int _y);
    void Aim(float vect, float x2, float y2);
    void turn(float vect, int deg);
    void collx();
    void colly();
    void Draw();
};


#endif //EVOLUTION_LIVE_ORGANISMS_PREDATOR_H
