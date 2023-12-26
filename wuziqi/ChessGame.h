//
// Created by ying on 2023/11/6.
//

#ifndef C2023_CHALLENGE_CHESSGAME_H
#define C2023_CHALLENGE_CHESSGAME_H

#pragma once
#include"Chess.h"
#include"AI.h"
#include"Man.h"
#include<time.h>

class ChessGame
{
public:
    ChessGame(Man* man, AI* ai, Chess* chess);
    void play();// 开始对局


    //添加数据成员
private:
    Man* man;
    AI* ai;
    Chess* chess;
};







#endif //C2023_CHALLENGE_CHESSGAME_H
