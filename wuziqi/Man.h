//
// Created by ying on 2023/11/6.
//

#ifndef C2023_CHALLENGE_MAN_H
#define C2023_CHALLENGE_MAN_H


#pragma once
#include"Chess.h"

class Man
{
public:
    void init(Chess*chess);
    void go();

private:
    Chess *chess;//用指针实现短暂调用（人不可能拥有棋盘）
};


#endif //C2023_CHALLENGE_MAN_H
