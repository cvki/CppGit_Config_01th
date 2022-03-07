#include "Boardn.h"
#include<iostream>

const int MINS = 16;
const int MAXS = 1024;

Boardn::Boardn() :Boardn(MINS) {}

Boardn::Boardn(int an) {
    n = MINS;
    if (an > MINS && an <= MAXS)
        n = an;
    board = new int* [n];
    for (int i = 0; i < n; ++i)
        board[i] = new int[n]();
}

Boardn::Boardn(const Boardn& bd){
    n = MINS;
    int size = bd.getN();
    if (size > MINS && size <= MAXS)
        n = size;
    this->board = new int* [n];
    for (int i = 0; i < n; ++i)
        board[i] = new int[n]();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            board[i][j] = bd.board[i][j];
    }
}

bool Boardn::setGap(const int& x, const int& y){
    if (x > 0 && x <= MAXS && y > 0 && y <= MAXS) {
        board[x][y] = -1;
        return true;
    }
    std::cerr << "INDEX ERROR!" << std::endl;
    return false;
}

int Boardn::getN()const {
    return n;
}

int Boardn::getDx() const{
    return dx;
}

int Boardn::getDy() const{
    return dy;
}

void Boardn::setvp(int x, int y, int v) {
    board[x][y] = v;
}

void Boardn::show()const {
    if (board) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if(j)
                    std::cout <<" "<<board[i][j];
                else
                    std::cout<< board[i][j];
            }
        std::cout << std::endl;
    }
}

Boardn::~Boardn(){
    for (int i = 0; i < n; i++) {
        delete[] board[i];
    }
    delete[] board;
}
