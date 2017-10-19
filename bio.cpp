//
// Created by sabster on 13.10.17.
//

#include "bio.h"

bio::bio() {
    life = true;
    w = 20;
    h = 20;
    num = rand() % 10000;
    range = 200;
    x = rand() % (winW - int(w));
    y = rand() % (winH - int(h));
    dx = rand() % 8 - 4;
    dx = rand() % 8 - 4;
    lifetime = 0;
    code = {1000,1,rand() % 13 + 1,25};
}

void bio::set(int _x, int _y) {
    x = _x;
    y = _y;
    life = true;
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
}

/*void bio::aim(float vect, float x2, float y2)
{
    dx = ((x2 - x) * vect) / sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
    dy = ((y2 - y) * vect) / sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
}*/

void bio::turn(float vect, int deg) {
    if ((dx != 0) || (dy != 0)) {
        float grad;
        if ((dx >= 0) && (dy < 0)) {
            dy = -dy;
            grad = atan(dx / dy) * 180 / M_PI;
            grad += deg;
            dx = sin(grad * M_PI / 180) * vect;
            dy = cos(grad * M_PI / 180) * vect;
            dy = -dy;
        }
        if ((dx >= 0) && (dy >= 0)) {
            grad = atan(dx / dy) * 180 / M_PI;
            grad = 90 - grad;
            grad += deg;
            grad = 90 - grad;
            dx = sin(grad * M_PI / 180) * vect;
            dy = cos(grad * M_PI / 180) * vect;
        }
        if ((dx < 0) && (dy <= 0)) {
            dy = -dy;
            dx = -dx;
            grad = atan(dx / dy) * 180 / M_PI;
            grad = 90 - grad;
            grad += deg;
            grad = 90 - grad;
            dx = sin(grad * M_PI / 180) * vect;
            dy = cos(grad * M_PI / 180) * vect;
            dy = -dy;
            dx = -dx;
        }
        if ((dx < 0) && (dy >= 0)) {
            dx = -dx;
            grad = atan(dx / dy) * 180 / M_PI;
            grad += deg;
            dx = sin(grad * M_PI / 180) * vect;
            dy = cos(grad * M_PI / 180) * vect;
            dx = -dx;
        }
    }
}

void bio::collx() {
    if (x - w / 2 < 0) {
        x = winW - w / 2;
    }
    if (x + w / 2 > winW) {
        x = w / 2;
    }
}

void bio::colly() {
    if (y - h / 2 < 0) {
        y = h / 2;
        dy = -dy;
    }
    if (y + h / 2 > winH) {
        y = winH - h / 2;
        dy = -dy;
    }
}

Code_bio bio::childcode(Code_bio c1, Code_bio c2) {

    //СКРЕЩИВАНИЕ
    Code_bio c;
    c.maxltime = (c1.maxltime + c2.maxltime) / 2;
    c.minspeed = (c1.minspeed + c2.minspeed) / 2;
    c.maxspeed = (c1.maxspeed + c2.maxspeed) / 2;
    c.maxturn = (c1.maxturn + c2.maxturn) / 2;

    //МУТАЦИЯ
    c.maxltime += c.maxltime / 100 * ((rand() % (MAXLTIME_MUT * 2 + 1)) - MAXLTIME_MUT);
    c.maxspeed += c.maxspeed / 100 * ((rand() % (maxspeed_mut * 2 + 1)) - maxspeed_mut);
    c.minspeed += c.minspeed / 100 * ((rand() % (minspeed_mut * 2 + 1)) - minspeed_mut);
    c.maxturn += c.maxturn / 100 * (rand() % (maxturn_mut * 2 + 1) - maxturn_mut);

    return c;
}

void bio::runaway(float vect, float x2, float y2) {
    dx = ((x - x2) * vect) / sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    dy = ((y - y2) * vect) / sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}

void bio::draw() {
    if (life) {
        /*glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex2f(x - w / 2, y - h / 2);
        glTexCoord2f(1, 1);
        glVertex2f(x + w / 2, y - h / 2);
        glTexCoord2f(1, 0);
        glVertex2f(x + w / 2, y + h / 2);
        glTexCoord2f(0, 0);
        glVertex2f(x - w / 2, y + h / 2);
        glEnd();*/
        int number = 40;
        float radius = w / winW;
        float twopi = 2.0 * M_PI;
        float _x = (x - winW / 2) / (winW / 2);
        float _y = -(y - winH / 2) / (winH / 2);

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(_x + 0.0f, _y + 0.0f);
        for (int i = 0; i <= number; ++i)
            glVertex2f(_x + radius * cosf(i * twopi / number), _y + radius * sinf(i * twopi / number));
        glEnd();
    }
}

