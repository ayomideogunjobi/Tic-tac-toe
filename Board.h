#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include <iostream>
#include <GL/freeglut.h>


class Board{
private:
    Cell** board;
    int size;
    bool gameOver;
    bool playerX;
    bool singlePlayer;
    std::string gameResult;


    void cleanup() {
        for (int i = 0; i < size; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    void computerMove(){
        if(singlePlayer && !playerX && !gameOver){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j].isEmpty()) {
                    board[i][j].playO();
                    playerX = true;
                    return;
                }
            }
        }
        }
    }

    public:

    Board(float _size, bool _singlePlayer) {
        size = _size;
        singlePlayer = _singlePlayer;
        board = new Cell*[size];
        for (int i = 0; i < size; i++) {
            board[i] = new Cell[size];
        }

        float w = 1.5f / size;
        float y = 0.9f;
        for (int i = 0; i < size; i++) {
            float x = -0.75f;
            for (int j = 0; j < size; j++) {
                board[i][j] = Cell(x, y, w);
                x += w;
            }
            y -= w;
        }

        playerX = true;
        gameOver = false;

    }



    void draw(){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j].draw();
            }
        }
    }

    bool checkRow(int row){
        Player firstPlayer = board[row][0].getPlayer();
        if(firstPlayer == Player::EMPTY) {
        return false;
        }
        for(int i = 1; i < size; i++){
            if (board[row][i].getPlayer() != firstPlayer){
                return false;
            }
        }
        return true;
    }

    bool checkCol(int col){
        Player firstPlayer = board[0][col].getPlayer();
        if(firstPlayer == Player::EMPTY) {
        return false;
        }
        for(int i = 1; i < size; i++){
            if (board[i][col].getPlayer() != firstPlayer){
                return false;
            }
        }
        return true;
    }

    bool checkDiag(){
        Player firstPlayer = board[0][0].getPlayer();
        if(firstPlayer != Player::EMPTY) {
            for(int i = 1; i < size; i++){
                if (board[i][i].getPlayer() != firstPlayer){
                    return false;
                }
            }
            return true;
        }
        firstPlayer = board[0][size - 1].getPlayer();
        if(firstPlayer != Player::EMPTY){
            for(int i = 1; i < size; i++){
                if (board[i][size - 1 - i].getPlayer() != firstPlayer){
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool noWinner(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if (board[i][j].isEmpty()){
                    return false;
                }
            }
        }
        return true;
    }

    
    void checkWinner(){

        if(gameOver){
            return;
        }
        for(int i = 0; i < size; i++){
            if(checkRow(i) || checkCol(i)){
                gameOver = true;
                gameResult = playerX ? "Player X Wins!" : "Player O Wins!";
                return;
            }
        
            if(checkDiag()){
                gameOver = true;
                 gameResult = playerX ? "Player X Wins!" : "Player O Wins!"; 
                return;
            }
            

            if (noWinner()){
                gameOver = true;
                gameResult = "It's a Tie!";
            }
        
        }
    }
  

void handleMouseClick(float mx, float my) {
    if (gameOver) return;  // No further moves if the game is over

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].contains(mx, my)) {
                std::cout << "Clicked on board[" << i << "][" << j << "]" << std::endl;

                if (board[i][j].isEmpty()) {
                    if (playerX) {
                        board[i][j].playX();
                    } else {
                        board[i][j].playO(); 
                    }

                    checkWinner();

                    if (gameOver) {
                        return;
                    }

                    playerX = !playerX;

                    if (singlePlayer && !playerX && !gameOver) { 
                        computerMove(); 
                        checkWinner(); 
                        playerX = true; 
                    }
                }
            }
        }
    }
}




    
    bool getGameOver(){
        return gameOver;
    }

    std::string getWinner(){
        return gameResult;
    }



    ~Board(){
        cleanup();
    }

};


#endif