//
// Created by ying on 2023/11/6.
//

#ifndef C2023_CHALLENGE_CHESS_H
#define C2023_CHALLENGE_CHESS_H
#pragma once

#include<graphics.h>
#include<vector>
#include<map>
using namespace std;

typedef struct chessmap {
    int g[13][13];
}chessmap;//示例中的chess，这里写为chessmap

bool operator <(chessmap x, chessmap y);
bool operator ==(chessmap x, chessmap y);

typedef struct property {//棋盘状态的一些特质
    double a, b;
    vector<chessmap>vec;
}property;


/*表示落子位置*/
struct ChessPos {
    int row;
    int col;

    ChessPos(int r=0,int c=0):row(r),col(c){}
};

enum chess_kind_t{
    CHESS_WHITE = -1,//白棋（空子是0）
    CHESS_BLACK = 1//黑棋
};

class Chess
{
public:
    Chess(int gradeSize, int marginX, int marginY, float chessSize);

    //棋盘初始化
    void init();
    //初始化棋盘状态
    void init_chess(chessmap x);
    //判断是否有效点击，有效点击则存储点击位置在参数pos中
    bool clickBoard(int x, int y, ChessPos* pos);
    //在棋盘的指定位置（pos）,落子(kind)
    void chessDown(ChessPos* pos, chess_kind_t kind);
    int getGradeSize();//获取棋盘大小（13，15，19）



    // 获取指定位置是白棋，黑棋，还是空白
    int getGradeData(ChessPos* pos);
    int getGradeData(int row, int col);
    //判断棋局是否结束
    bool checkOver(chessmap x,int player);
    bool checkWin(chessmap tocheck_chessMap,int player);//如果胜负已分就返回true

    //存储当前棋局的棋子分布数据(当前的棋盘状况)
    //chessMap[3][5]表示棋盘的第3行第5列的落子情况（0空白，1黑子，-1白子）
    vector<vector<int>>chessMap;
    int rd = 0;//回合数
    map<chessmap, property> mp;//用于记录棋盘状态的一些特质
    map<chessmap, chessmap> fa;//棋盘状态的父节点用于反向传播

private:
    IMAGE chessBlackImg;//黑棋棋子
    IMAGE chessWhiteImg;//白棋棋子
    ChessPos lastPos; //最近落子位置, Chess的private数据成员

    int gradeSize;//棋盘大小
    int margin_x;//棋盘的左侧边界
    int margin_y;//棋盘的顶部边界
    float chessSize;//棋子大小（棋盘方格大小）


    //表示现在该谁下棋
    bool playerFlag;//true:该黑子走，flase该白子走

    void updateGameMap(ChessPos* pos);


};
#endif //C2023_CHALLENGE_CHESS_H
