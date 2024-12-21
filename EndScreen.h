#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "Button.h"
#include "Board.h"
#include <iostream>
#include "Board.h"

class EndScreen{    
private:
    Button* restart;
    Button* quit;
    bool restartGame;
    std:: string displayWinner;


public:
    EndScreen(std::string result){
        restart = new Button(-0.3f, -0.1f, "Restart");
        quit = new Button(0.1f, -0.1f, "Quit");
        restartGame = false;
        displayWinner = "";
    }

    void handleMouseClick(float mx, float my){
        if (restart->contains(mx, my)) {
            restartGame = true;
        }
        else if(quit->contains(mx, my)) {
            exit(0);
        }
    }


    void draw(){
        restart->draw();
        quit->draw();

        //if(!gameResult.empty())



    }

    bool getRestartGame(){
        return restartGame;
    }





~EndScreen(){
    delete restart;
    delete quit;
}


};

#endif