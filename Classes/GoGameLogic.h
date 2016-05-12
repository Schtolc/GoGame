//
// Created by pavelgolubev345 on 12.05.16.
//

#ifndef MYGAME_GOGAMELOGIC_H
#define MYGAME_GOGAMELOGIC_H



#include <iostream>
#include <stdio.h>
#include <string.h>
#include "GameLogic.h"

using namespace std;

#define EMPTY 0
#define WHITE 1
#define BLACK 2
//для функций подсчета очков
#define BSIZE 19
#define ENDLIST 1000
#define QSIZE 150
#define GREY  3
#define NODES BSIZE*BSIZE
//



struct gameRes {
    int *scores;

    gameRes(int N) {
        scores = new int[N];
        for (int i = 0; i < N; ++i) {
            scores[i] = 0;
        }

    };

    ~gameRes() {
        delete[] scores;
    }
};

class GoGameLogic : public GameLogic {
private:

    friend class BoardManager;

    int p[19][19];//доска

    int l[19][19];//матрица свобод каждого камня

    unsigned char ma[19][19];//2 матрицы для маркирования

    unsigned char ml[19][19];//вспомогательая матрица, которую юзаем при заполнении матрицы l

    int currentStep;//какой из игроков ходит

    int umove, mymove;//

    int lib;//текущая количество свобод камня

    int mik, mjk;

    int uik, ujk;
    //позиции пойманых камней игрока???????????????
    //2 вспомогательных индекса, которые нужны, когда чекаем, не надо ли что нибудь удалить с доски
    int mk, uk;
    //количество камней, пойманых игроком и компьютером

///////////////////////////ФУНКЦИИ///////////////////////

    bool getmove(char move[], int *i, int *j);

    int getij(char move[], int *i, int *j);

    //проверка хода на суицидальность
    int suicide(int i, int j);

    //заполнение матрицы l
    void countlib(int m, int n, int color);

//количество свобод для 1го камня
    void count(int i, int j, int color);

    void eval(int color);

    void examboard(int color);


public:
    typedef int (*desk)[19];

    void showboard();

    bool setChipin(char *move, int i, int j, int team);

    gameRes endgame();

    void showHelpMat();

    //установка камня по номерам
    bool setChip(int i, int j, int team);

    int getCell(int x, int y) const {
        return p[x][y];
    }
//получение указателя на ключевую доску
    const desk getDesk() {
        return p;
    }

    GoGameLogic();

    ~GoGameLogic();
};


#endif //MYGAME_GOGAMELOGIC_H
