//
// Created by sabster on 13.10.17.
//

#ifndef EVOLUTION_LIVE_ORGANISMS_GAME_H
#define EVOLUTION_LIVE_ORGANISMS_GAME_H

#include "bio.h"
#include "Predator.h"
#include <cstdlib>
#include <list>
#include <GL/gl.h>

class Game {
private:
    std::list<bio> bios;
    std::list<Predator> preds;
    GLuint texture_predator;
    GLuint texture_bio;
public:
    Game(int count_bio = 205, int count_predator = 20);
    void Step();
    void Draw();
    void Makechild(bio & b);
    int get_bio_amount();
    float get_average_maxspeed();
    GLuint LoadTexture( const char * filename );
};


#endif //EVOLUTION_LIVE_ORGANISMS_GAME_H
