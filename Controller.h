#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <GL/freeglut.h>
#include "AppController.h"

#include "Board.h"
#include "StartScreen.h"
#include "EndScreen.h"

class Controller : public AppController {

    Board* board;
    StartScreen* startScreen;
    EndScreen* endScreen;
    bool gameActive;
    bool gameOver;
    int size; //size of board
    bool playerX;
    bool singlePlayer;
    //std::string gameResult;

    void cleanUp(){
        if (board != nullptr){
            delete board;
            board = nullptr;
        }
        if(endScreen != nullptr){
            delete endScreen;
            endScreen = nullptr;
        }
    }

public:
    Controller(){
        // Initialize your state variables
        board = nullptr;
        startScreen = new StartScreen();
        endScreen = nullptr;
        size = 0;
        playerX = true;
        singlePlayer = false;
        gameActive = false;
        gameOver = false;
        
    }

    void render() {
        // Render some graphics
        if(gameActive == false){
            startScreen->draw();
        }
        else if(board != nullptr && gameOver == false){
            board->draw();
        }
        else if(endScreen != nullptr && gameOver == true){
            endScreen->draw();
        }
    }

    void leftMouseDown(float mx, float my) {
        if(!gameActive){ //game hasn't started
            startScreen->handleMouseClick(mx,my);

            if (startScreen->getBoardSize() > 0){
                size = startScreen->getBoardSize();
                singlePlayer = startScreen->getPlayerMode();
                cleanUp();
                board = new Board(size, singlePlayer);
                gameActive = true;
            }
        }
        else if (board != nullptr && gameOver == false){ //while game is going
            board->handleMouseClick(mx, my);
            board->checkWinner();
            if(board->getGameOver()){
                gameOver = true;
                std::cout << board->getWinner() << std::endl;
                endScreen = new EndScreen(board->getWinner());
            }
        }
        else if(gameOver && endScreen != nullptr){
            endScreen->handleMouseClick(mx, my);
            if(endScreen->getRestartGame()){
                cleanUp();
                startScreen = new StartScreen();
                //board = new Board(size, singlePlayer);
                gameActive = false;
                gameOver = false;
                size = 0;
                singlePlayer = false;
                playerX = true;
                std::cout << "Game restarted" << std::endl;
            }
        }
    }
    

    ~Controller(){
        // Release memory
        delete board; 
        delete startScreen;
        delete endScreen;

    }
};

#endif