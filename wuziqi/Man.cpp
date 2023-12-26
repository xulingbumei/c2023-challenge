//
// Created by ying on 2023/11/6.
//
#include "Man.h"


void Man::init(Chess* chess)
{
    this->chess = chess;
}

void Man::go()
{
    MOUSEMSG msg;
    ChessPos pos;


    while (1) {
        //获取鼠标点击消息
        msg = GetMouseMsg();

        //通过chess对象，来调用判断落子是否有效，以及落子功能(uMsg 获取鼠标左键还是右键，WM_LBUTTONDOWN是左键单击),用clickBoard判断是否有效点击
        if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
            break;
        }
    }

    printf("%d,%d\n",pos.row,pos.col);
    //落子
    chess->chessDown(&pos, CHESS_BLACK);
}

