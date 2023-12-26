//
// Created by ying on 2023/11/6.
//

#include "ChessGame.h"

ChessGame::ChessGame(Man* man, AI* ai, Chess* chess) {
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    man->init(chess);
    ai->init(chess);
}


void ChessGame::play()
{

    chess->rd = 0;
    chess->mp.clear(), chess->fa.clear();
    chessmap now;
    int row = 13,col=13;
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j < col; j++) {
            now.g[i][j] = 0;
        }
    }
    center.first = row / 2, center.second = col / 2;
    srand(time(0));
    chess->init();
    chess->init_chess(now);
    while (1) {
        //先由棋手走棋
        man->go();
        if (chess->checkOver(now,1)) {
            chess->init();

            continue;
        }
        //由 ai走
        ai->go();
        if (chess->checkOver(now,-1) ){
            chess->init();
            continue;
        }
        chess->rd++;
    }

}