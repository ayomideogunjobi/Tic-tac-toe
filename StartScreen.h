#ifndef STARTSCREEN_H
#define STARTSCREEN_H

//#include "Board.h"
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <iostream>
#include "Button.h"
#include "Cell.h"
#include "Board.h"

class StartScreen{
private:
    Button* button3;
    Button* button4;
    Button* button5;
    Button* multiP;
    Button* singleP;
    int boardSize;
    bool singlePlayer;

public:
    StartScreen(){
        button3 = new Button(-0.5f, 0.0f, "3 x 3");
        button4 = new Button(-0.15f, 0.0f, "4 x 4");
        button5 = new Button(0.2f, 0.0f, "5 x 5");
        multiP = new Button(-0.5f,0.4f, "Multiplayer");
        singleP = new Button(0.1f, 0.4f, "Single Player");
        boardSize = 0;
        singlePlayer = false;

    }

    void draw(){
        button3->draw();
        button4->draw();
        button5->draw();
        //start->draw();
        multiP->draw();
        singleP->draw();
    }

    void handleMouseClick(float mx, float my){
        if (button3->contains(mx, my)) {
            std::cout << "Created 3 x 3 board" << std::endl;
            //playerBoard->cleanup();
            button3->setPressed(true);
            button4->setPressed(false);
            button5->setPressed(false);
            boardSize = 3;
            //playerBoard->initBoard();
        }
        else if (button4->contains(mx, my)) {
            std::cout << "Created 4 x 4 board" << std::endl;
            //playerBoard->cleanup();
            button4->setPressed(true);
            button3->setPressed(false);
            button5->setPressed(false);
            boardSize = 4;
            //playerBoard->initBoard();
        }
        else if (button5->contains(mx, my)) {
            std::cout << "Created 5 x 5 board" << std::endl;
            //playerBoard->cleanup();
            button5->setPressed(true);
            button3->setPressed(false);
             button4->setPressed(false);
            boardSize = 5;
            //playerBoard->initBoard();
        }
        else if(singleP->contains(mx,my)){
            singleP->setPressed(true);
            multiP->setPressed(false);
            singlePlayer = true;
        }
        else if(multiP->contains(mx,my)){
            multiP->setPressed(true);
            singleP->setPressed(false);
            singlePlayer = false;
        }


    }

    int getBoardSize(){
        return boardSize;
    }

    /*int getPlayerMode(){
        return singlePlayer;
    }*/

    bool getPlayerMode(){
        return singleP->isPressed();
    }

 

~StartScreen(){
    delete button3;
    delete button4;
    delete button5;
    //delete start;
    delete multiP;
    delete singleP;
}



};

#endif

