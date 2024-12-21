#ifndef CELL_H
#define CELL_H

#include <GL/freeglut.h>
#include <cmath>

enum Player {EMPTY, PLAYER_X, PLAYER_O};

class Cell {
private:
    float x;
    float y;
    float size;
    Player player;

public:
    Cell() {
        x = 0.0f;
        y = 0.0f;
        size = 0.2f;
        player = EMPTY;
    }

    Cell(float x, float y, float size) {
        this->x = x;
        this->y = y;
        this->size = size;
        player = EMPTY;
    }

    void draw() {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);

        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + size, y);

            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);

            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);

            glVertex2f(x, y - size);
            glVertex2f(x, y);
        glEnd();

        if (player == PLAYER_X) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glLineWidth(1.0f);

            glBegin(GL_LINES);
                glVertex2f(x + 0.1f, y - 0.1f);
                glVertex2f(x + size - 0.1f, y - size + 0.1f);

                glVertex2f(x + size - 0.1f, y - 0.1f);
                glVertex2f(x + 0.1f, y - size + 0.1f);
            glEnd();
        }
        else if (player == PLAYER_O) {
            glColor3f(0.0f, 0.0f, 1.0f);
            glLineWidth(1.0f);

            glBegin(GL_LINES);
                float inc = (2 * M_PI) / 60;
                for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta), (y - (size / 2)) + (size / 2 - 0.1f) * sin(theta));
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta + inc), (y - (size / 2)) + (size / 2 - 0.1f) * sin(theta + inc));
                }
            glEnd();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + size && my <= y && my >= y - size) {
            return true;
        }
        return false;
    }

    bool isEmpty() {
        return player == EMPTY;
    }

    void playX() {
        player = PLAYER_X;
    }

    void playO() {
        player = PLAYER_O;
    }

    Player getPlayer() {
        return player;
    }

    ~Cell() {
        //
    }
};

#endif