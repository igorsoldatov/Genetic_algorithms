//
// Created by sabster on 13.10.17.
//

#include "Predator.h"

Predator::Predator(void) {
    life = 1;
    w = 30;
    h = 30;
    num = rand() % 10000;
    range = 250;
    speed = 10.2;
    hungry = 0;//1*1000/20;
    //srand(time(0));
    x = rand() % (winW - (int) w);
    y = rand() % (winH - (int) h);
    //srand(time(0));
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    lifetime = 0;
    aim_id = -1;
}

void Predator::Set(int a, int b) {
    x = a;
    y = b;
    life = true;
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
}

void Predator::Aim(float vect, float x2, float y2) {
    dx = ((x2 - x) * vect) / sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    dy = ((y2 - y) * vect) / sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}

void Predator::turn(float vect, int deg) {
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

void Predator::collx() {
    if (x - w / 2 < 0) {
        x = winW
            - w / 2;
    }
    if (x + w / 2 > winW) {
        x = w / 2;
    }
}

void Predator::colly() {
    if (y - h / 2 < 0) {
        y = h / 2;
        dy = -dy;
    }
    if (y + h / 2 > winH) {
        y = winH
            - h / 2;
        dy = -dy;
    }
}

void Predator::Draw() {
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
        if (hungry >=0)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(0.0f, 0.0f, 1.0f);

        glVertex2f(_x + 0.0f, _y + 0.0f);
        for (int i = 0; i <= number; ++i)
            glVertex2f(_x + radius * cosf(i * twopi / number), _y + radius * sinf(i * twopi / number));
        glEnd();
    }
}