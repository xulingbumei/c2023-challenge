#include <stdio.h>
#include <stdlib.h>
#include<conio.h>//_getch()//输入一个按键，才执行下一个语句
#include <Windows.h>

//chuansong
const WORD FORE_BLUE = FOREGROUND_BLUE;
const WORD FORE_GREEN = FOREGROUND_GREEN;
const WORD FORE_RED = FOREGROUND_RED;
const WORD FORE_PURPLE = FORE_BLUE | FORE_RED;
const WORD FORE_CYAN = FORE_BLUE | FORE_GREEN;
const WORD FORE_YELLOW = FORE_RED | FORE_GREEN;
const WORD FORE_GRAY = FOREGROUND_INTENSITY;
const WORD BACK_BLUE = BACKGROUND_BLUE;
const WORD BACK_GREEN = BACKGROUND_GREEN;
const WORD BACK_RED = BACKGROUND_RED;
const WORD BACK_PURPLE = BACK_BLUE | BACK_RED;
const WORD BACK_CYAN = BACK_BLUE | BACK_GREEN;
const WORD BACK_YELLOW = BACK_RED | BACK_GREEN;
const WORD BACK_GRAY = BACKGROUND_INTENSITY;

//空地 0 墙壁 1 人 2 箱子 3 目标点 4
//关卡数组Map 三维数组
int Map[3][10][10] =
        {
                {//第一关
                        {1,1,1,1,1,1,1,1,1,1},
                        {1,2,0,1,0,1,0,0,0,1},
                        {1,0,0,1,0,0,0,0,0,1},
                        {1,3,3,4,1,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,4,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,0,0,0,3,0,4,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1}, },
                {//第二关
                        {1,1,1,1,1,1,1,1,1,1},
                        {1,2,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,1,0,1},
                        {1,3,3,4,0,0,0,0,0,1},
                        {1,0,0,0,1,0,0,0,0,1},
                        {1,4,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,1,0,0,0,1},
                        {1,0,0,0,3,0,4,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1}, },
                {//第三关
                        {1,1,1,1,1,1,1,1,1,1},
                        {1,2,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,3,3,4,0,0,0,0,0,1},
                        {1,0,0,0,0,3,0,0,0,1},
                        {1,4,0,0,0,4,0,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,0,1,0,3,0,4,0,0,1},
                        {1,0,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1}, }
        };
int level = 0;
int maparr[10][10] = { 0 };


void initGame();
//地图加载函数
void initMap();
//绘制函数
void drawMap();
//更新游戏数据
void runGame();
//人物的移动函数
void moveInmap(int off_x, int off_y);
//结束函数
int endGame();


int main()
{
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle_out, &csbi);
    SetConsoleTextAttribute(handle_out, BACK_BLUE | BACK_RED | BACK_GREEN);    initGame();
    L:initMap();
    while (endGame())
    {
        runGame();

    }
    if (level < 3)
    {
        level++;
        if (level != 3)
            printf("恭喜通过本关，按任意键进入下一关\n");
        goto L;
    }
    printf("游戏胜利\n");
    return 0;
}
//初始化游戏
void initGame()
{
    printf("\n\n\n    推箱子--按任意键开始");
    _getch();
}
//地图加载函数
void initMap()
{
    //加载当前关卡地图
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            maparr[i][j] = Map[level][i][j];
        }
    }
}
void drawMap()
{
    system("cls");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (maparr[i][j])
            {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("■");
                    break;
                case 2:
                    printf("♀");
                    break;
                case 3:
                    printf("●");
                    break;
                case 4:
                    printf("☆");
                    break;
                case 2 + 4:
                    printf("♀");
                    break;
                case 3 + 4:
                    printf("★");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}
//更新游戏数据
void runGame()
{

    switch (_getch())
    {
        case 'w':
        case 'W':
            moveInmap(-1, 0);
            break;
        case 's':
        case 'S':
            moveInmap(1, 0);
            break;
        case 'a':
        case 'A':
            moveInmap(0, -1);
            break;
        case 'd':
        case 'D':
            moveInmap(0, 1);
            break;
        default:
            break;

    }
    drawMap();

}

//人物的移动函数
void moveInmap(int off_x, int off_y)
{

    int playerPos_X = 0;
    int playerPos_Y = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (2 == maparr[i][j] || 2 + 4 == maparr[i][j])
            {
                playerPos_X = i;
                playerPos_Y = j;

            }
        }
    }


    //移动
    if (0 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
        4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//空地、目标点
    {
        maparr[playerPos_X][playerPos_Y] -= 2;
        maparr[playerPos_X + off_x][playerPos_Y + off_y] += 2;
    }
    else if (3 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
             3 + 4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//箱子、箱子在点上
    {
        if (0 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] ||
            4 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2])//空地、目标点
        {
            maparr[playerPos_X][playerPos_Y] -= 2;
            maparr[playerPos_X + off_x][playerPos_Y + off_y] += (2 - 3);
            maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] += 3;
        }
    }
}
//结束函数
int endGame()
{
    //遍历
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (3 == maparr[i][j])
            {
                return 1;
            }
        }
    }
    return 0;

}