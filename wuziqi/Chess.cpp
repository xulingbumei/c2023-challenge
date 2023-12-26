//
// Created by ying on 2023/11/6.
//


#include "Chess.h"
#include<math.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                             | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize) {
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;
    playerFlag = CHESS_BLACK;

    for (int i = 0; i < gradeSize; i++) {
        vector<int> row;
        for (int j = 0; j <= gradeSize; j++) {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}


void Chess::init()
{
    //创建游戏窗口
    initgraph(897, 895, EX_SHOWCONSOLE);
    IMAGE img ;
    //加载棋盘图片
    loadimage(&img, L"res/棋盘2.jpg");
    //播放开始提示音
    mciSendString(L"res/start.wav", 0, 0, 0);
    //
    putimage(0, 0, &img);
    //加载黑棋和白棋的图片
    loadimage(&chessBlackImg, L"res/black.png", chessSize, chessSize, true);
    loadimage(&chessWhiteImg, L"res/white.png", chessSize, chessSize, true);


    //棋盘清零
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++)
            chessMap[i][j] = 0;
    }

    playerFlag = true;
}

void Chess::init_chess(chessmap x)
{
    property p;
    p.a = p.b = 0.0;
    mp[x] = p;
}




bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.4;

    int len;
    bool ret = false;//点击是否有效

    do {
        // 左上角判断
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        //右上角判断
        int x2 = leftTopPosX + chessSize,y2=leftTopPosY;
        len = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
        if (len < offset) {
            pos->row = row;
            pos->col = col+1;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        //左下角判断
        x2 = leftTopPosX, y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            pos->row = row+1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        //右下角判断
        x2 = leftTopPosX + chessSize, y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            pos->row = row+1;
            pos->col = col+1;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }
    } while (0);

    return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;//注意打印图片时坐标是要打印的图像的左上角，而我们要它在正中心
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == CHESS_WHITE) {
        putimagePNG(x, y, &chessWhiteImg);// 曾经因为文件目录从“E:/。。。”出现只有背景而没有棋子的情况，要直接“/res/black.png"(想知道原因)
    }
    else {
        putimagePNG(x, y, &chessBlackImg);
    }

    updateGameMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getGradeData(ChessPos* pos)
{
    return chessMap[pos->row][pos->col];
}

int Chess::getGradeData(int row, int col)
{
    return chessMap[row][col];
}
bool Chess::checkOver(chessmap x,int player)
{
    if (checkWin(x,player)) {
        Sleep(1500);
        if (playerFlag==false) {
            //刚才走的是黑方（人），所以黑方获胜
            loadimage(0, L"res/胜利.jpg");
        }
        else {
            loadimage(0, L"res/失败.jpg");
        }

        _getch();//暂停
        return true;
    }

    return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag; // 黑白方交换行棋
    lastPos = *pos;
}

bool Chess::checkWin(chessmap tocheck_chessMap,int player)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    int row = getGradeSize(),col=getGradeSize();
    int cnt = 0;
    // 水平方向
    for (int i = 0; i <= row; i++) {
        cnt = 0;
        for (int j = 0; j <= col; j++) {
            if (tocheck_chessMap.g[i][j] == player) {
                cnt++;
            }
            else {
                cnt = 0;
            }
            if (cnt >= 5) {
                return true;
            }
        }
    }
    cnt = 0;
    //竖直方向
    for (int j = 0; j <=col; j++) {
        cnt = 0;
        for (int i = 0; i <= row;i++) {
            if (tocheck_chessMap.g[i][j] == player) {
                cnt++;
            }
            else {
                cnt = 0;
            }
            if (cnt >= 5) {
                return true;
            }
        }
    }
    cnt = 0;
    //斜方向"\"
    //下三角区域搜索
    for (int i = 0; i <= row; i++) {
        cnt = 0;
        int l = i, r = 0;
        while (l <= col && r <= col) {
            if (tocheck_chessMap.g[l][r] == player)cnt++;
            else cnt = 0;
            if (cnt >= 5)return true;
            l++; r++;
        }
    }
    //上三角区域搜索
    for (int i = 0; i <= row; i++) {
        cnt = 0;
        int l = i, r = 0;
        while (l <= col && r <= col) {
            if (tocheck_chessMap.g[r][l] == player)cnt++;
            else cnt = 0;
            if (cnt >= 5)return true;
            l++; r++;
        }
    }
    cnt = 0;
    //“/”方向搜索
    //左上三角形搜索
    for (int i =row; i >=0; i--) {
        cnt = 0;
        int l = i, r = 0;
        while (l >= 0 && r <= col) {
            if (tocheck_chessMap.g[r][l] == player)cnt++;
            else cnt = 0;
            if (cnt >= 5)return true;
            l--; r++;
        }
    }
    cnt = 0;
    //右下三角形搜索
    for (int i = 0; i <= row; i++) {
        cnt = 0;
        int l = i, r = col;
        while (l <= col&&r>=0) {
            if (tocheck_chessMap.g[l][r] == player)cnt++;
            else cnt = 0;
            if (cnt >= 5)return true;
            l++; r--;
        }
    }
    return false;
}