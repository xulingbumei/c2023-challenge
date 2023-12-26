//
// Created by ying on 2023/11/6.
//

#ifndef C2023_CHALLENGE_AI_H
#define C2023_CHALLENGE_AI_H
#pragma once

#include "Chess.h"
#include<cmath>
#include<map>


#define select_num 300        //选择次数
#define sta_num 15            //每个状态模拟次数
#define mp(x,y) make_pair(x,y)
const int tol_row = 13, tol_col = 13;//棋盘的行和列
const int search_range = 2;//搜索范围
const double inf = 1e9 + 7;

extern pair<int, int> center;//搜索中心

class AI
{
public:
    void init(Chess* chess);
    void go(chessmap now,pair<int,int>center,int i));

private:
    Chess* chess;
    vector<vector<int>>scoreMap;

private:
    void calculateScore();
    ChessPos think();
    chessmap UCT_search(chessmap x, pair<int, int> center, int player);//蒙特卡洛树搜索
    pair<chessmap, int> tree_policy(chessmap x, pair<int, int> center, int player);//选择子节点
    chessmap expand(chessmap x, pair<int, int> center, int player);//扩展当前节点
    double UCB(chessmap x, int player);//计算节点的UCB值
    pair<int, int> cal_centre(chessmap x);//计算当前局面的搜索中心
    double default_policy(chessmap x, int player);//模拟结果
    void back_up(chessmap x, chessmap y, int value);//反向传播
    pair< int, pair<int, int> > check_four(chessmap x);//预言胜利
    pair< int, pair<int, int> > check_three(chessmap x);//预言胜利优化
    int is_terminal(chessmap x);//判断是否是叶子节点
    int cnt_num(chessmap x, int x1, int x2, int y1, int y2);//查看节点的棋子数量
    int check(chessmap x);
    int check_win(chessmap x, int player);

};



#endif //C2023_CHALLENGE_AI_H
