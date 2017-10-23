//
// Created by sabster on 13.10.17.
//

#include "Game.h"
#include <GL/glut.h>
#include <stdio.h>
#include <algorithm>

Game::Game(int count_bio, int count_predator) {

    texture_predator = LoadTexture("./virus.png");
    texture_bio = LoadTexture("./virus.png");

    for (int i = 0; i < count_bio; ++i) {
        bio b;
        bios.push_back(b);
    }
    for (int i = 0; i < count_predator; ++i) {
        Predator p;
        preds.push_back(p);
    }
}

void Game::Step() {
    for (auto b = bios.begin(); b != bios.end(); b++) {
        if (b->dx == 0)
            b->dx = rand() % 30 / 10 + 1;
        if (b->dy == 0)
            b->dy = rand() % 30 / 10 + 1;

        //УБЕГАЙ
        float min = b->range;
        bool ok = false;
        float x2, y2;

        for (auto p = preds.begin(); p != preds.end(); p++) {
            if (sqrt((b->x - p->x) * (b->x - p->x) + (b->y - p->y) * (b->y - p->y)) < min) {
                min = sqrt((b->x - p->x) * (b->x - p->x) + (b->y - p->y) * (b->y - p->y));
                ok = true;
                x2 = p->x;
                y2 = p->y;
            }
        }

        if (ok) {
            b->runaway(b->code.maxspeed, x2, y2);
            b->turn(b->code.maxspeed, (rand() % (2 * (int) b->code.maxturn + 1) * 10) / 10 - (int) b->code.maxturn);
        } else {
            int turnX_rand = rand();
            int turnY_rand = rand();
            float turnX = (turnX_rand % (int) ((b->code.maxspeed - b->code.minspeed + 1) * 10)) / 10 + b->code.minspeed;
            float turnY = (turnY_rand % (2 * (int) b->code.maxturn + 1) * 10) / 10 - (int) b->code.maxturn;
            b->turn(turnX, turnY);
        }
        b->x += b->dx;
        b->collx();
        b->y += b->dy;
        b->colly();

        //ДЕТИ
        Makechild(*b);
        //ПРОД. ЖИЗНИ
        b->lifetime++;
        if (b->lifetime > b->code.maxltime)
            b->life = 0;
        //РОСТ
        b->w = b->lifetime / 40 + 20;
        b->h = b->lifetime / 40 + 20;
    }

    bios.remove_if([](bio b) { return (b.life == 0); });

    for (auto p = preds.begin(); p != preds.end(); p++) {
        if (p->life) {
            if (p->dx == 0)
                p->dx = rand() % 30 / 10 + 1;
            if (p->dy == 0)
                p->dy = rand() % 30 / 10 + 1;

            //ПОИСК ЕДЫ
            bool ok = 0;
            float x2, y2;
            int aim_id = -1;
            if (p->hungry <= 0) {
                float min = p->range;

                for (auto b = bios.begin(); b != bios.end(); b++) {
                    float distance = sqrt((p->x - b->x) * (p->x - b->x) + (p->y - b->y) * (p->y - b->y));
                    if (distance < p->w / 2 + b->w / 2 - 10) {
                        b->life = 0;
                        p->hungry = 100;
                    } else if (distance < min) {
                        auto iter = std::find_if(preds.begin(), preds.end(), [&b, &p](Predator pred) { return pred.aim_id == b->num && pred.num != p->num; });
                        if (!iter->life) {
                            min = distance;
                            ok = 1;
                            x2 = b->x;
                            y2 = b->y;
                            aim_id = b->num;
                        }
                    }
                }
            }
            if (ok) {
                p->Aim(p->speed, x2, y2);
                p->aim_id = aim_id;
            }
            else
                p->turn(6, (rand() % (2 * 15 + 1) * 10) / 10 - 15);

            p->x += p->dx;
            p->collx();
            p->y += p->dy;
            p->colly();


            //ПРОД. ЖИЗНИ

            //РОСТ
            //ГОЛОД
            p->hungry -= 5;
        }

    }
}

void Game::Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (auto b : bios) {
        b.draw();
    }
    for (auto p : preds) {
        p.Draw();
    }

    glFlush();
}

void Game::Makechild(bio &b) {
    std::list<bio>::iterator i = bios.begin();
    for (; i != bios.end(); i++) {
        if (b.num != i->num) {
            if ((b.lifetime > 200) && (i->lifetime > 200)) {
                if (sqrt((b.x - i->x) * (b.x - i->x)) + ((b.y - i->y) * (b.y - i->y)) < b.w + i->w) {
                    b.life = 0;
                    i->life = 0;
                    int c;
                    if (bios.size() < 20)
                        c = rand() % 4 + 1;
                    else if (bios.size() < 150)
                        c = rand() % 3 + 1;
                    else if (bios.size() < 250)
                        c = rand() % 2 + 1;
                    else if (bios.size() < 400)
                        c = 1;
                    else if (bios.size() > 600)
                        c = 0;
                    else
                        c = rand() % 3 + 1;

                    for (int j = 0; j < c; j++) {
                        bio b;
                        b.code = b.childcode(b.code, i->code);
                        bios.push_back(b);
                    }
                }
            }
        }
    }
}

float Game::get_average_maxspeed(){

    if (bios.size() == 0)
        return 0;

    float maxspeed = 0;
    for (auto b : bios){
        maxspeed += b.code.maxspeed;
    }

    return maxspeed / bios.size();
}

int Game::get_bio_amount(){
    return bios.size();
}

GLuint Game::LoadTexture(const char *filename) {
    GLuint texture;

    int width, height;

    unsigned char *data;

    FILE *file;

    file = fopen(filename, "rb");

    if (file == NULL) return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *) malloc(width * height * 3);
    //int size = fseek(file,);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}