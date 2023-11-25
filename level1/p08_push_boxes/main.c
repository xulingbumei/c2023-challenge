#include <stdio.h>
#include <stdlib.h>
#include<conio.h>//_getch()//����һ����������ִ����һ�����
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

//�յ� 0 ǽ�� 1 �� 2 ���� 3 Ŀ��� 4
//�ؿ�����Map ��ά����
int Map[3][10][10] =
        {
                {//��һ��
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
                {//�ڶ���
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
                {//������
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
//��ͼ���غ���
void initMap();
//���ƺ���
void drawMap();
//������Ϸ����
void runGame();
//������ƶ�����
void moveInmap(int off_x, int off_y);
//��������
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
            printf("��ϲͨ�����أ��������������һ��\n");
        goto L;
    }
    printf("��Ϸʤ��\n");
    return 0;
}
//��ʼ����Ϸ
void initGame()
{
    printf("\n\n\n    ������--���������ʼ");
    _getch();
}
//��ͼ���غ���
void initMap()
{
    //���ص�ǰ�ؿ���ͼ
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
                    printf("��");
                    break;
                case 2:
                    printf("��");
                    break;
                case 3:
                    printf("��");
                    break;
                case 4:
                    printf("��");
                    break;
                case 2 + 4:
                    printf("��");
                    break;
                case 3 + 4:
                    printf("��");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}
//������Ϸ����
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

//������ƶ�����
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


    //�ƶ�
    if (0 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
        4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//�յء�Ŀ���
    {
        maparr[playerPos_X][playerPos_Y] -= 2;
        maparr[playerPos_X + off_x][playerPos_Y + off_y] += 2;
    }
    else if (3 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
             3 + 4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])//���ӡ������ڵ���
    {
        if (0 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] ||
            4 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2])//�յء�Ŀ���
        {
            maparr[playerPos_X][playerPos_Y] -= 2;
            maparr[playerPos_X + off_x][playerPos_Y + off_y] += (2 - 3);
            maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] += 3;
        }
    }
}
//��������
int endGame()
{
    //����
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