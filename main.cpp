#include <GL/glut.h>
#include <iostream>
#include "Game.h"

#define WINDOWS_TITLE "Evolution_live_organisms..."
#define winW 1000
#define winH 1000

Game game;

void update(int value) {

    game.Step();

    std::string bio_amount = std::to_string(game.get_bio_amount());
    std::string max_speed = std::to_string(game.get_average_maxspeed());

    std::string title = std::string(WINDOWS_TITLE) + " bio: " + bio_amount +  " max speed: " + max_speed;
    glutSetWindowTitle(title.c_str());

    glutPostRedisplay(); // Inform GLUT that the display has changed
    glutTimerFunc(10, update, 0);//Call update after each 25 millisecond
}

void drawScene(){
    game.Draw();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(winW, winH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOWS_TITLE);
    glutDisplayFunc(drawScene);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}

