#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>

int map[10][10]={
        {1,1,1,1,1,1,1,1,1,1},
        {1,2,0,1,0,1,0,0,0,1},
        {1,1,0,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,0,0,1},
        {1,0,1,0,1,0,1,1,1,1},
        {1,0,1,0,1,0,0,0,0,1},
        {1,0,0,0,1,1,1,1,0,1,},
        {1,0,1,0,1,0,0,0,3,1},
        {1,1,1,1,1,1,1,1,1,1}
};

void initGame();
void drawmap();
void runGame();
void movemap(int off_x,int off_y);
int endGame();


int main(){
    initGame();
    while(endGame()){
        runGame();
    }
    printf("游戏胜利！\n");
    return 0;

}

void initGame(){
    printf("\n\n\n---走迷宫，按任意键开始");
    _getch();
}


void drawmap(){
    system("cls");
    for(int i=0;i<10;i++) {
        for (int j = 0; j < 10; j++) {
            switch (map[i][j]) {
                case 0 :
                    printf(" ");
                    break;
                case 1:
                    printf("■");
                    break;
                case 2:
                    printf("♀");
                    break;
                case 3:
                    printf("☆");
                    break;
                case 3 + 2:
                    printf("★");
                    break;
            }
        }
        printf("\n");
    }
}

void runGame(){
    switch(_getch()){
        case 'w':
        case 'W'://注意x和y与是纵坐标和横坐标
        {
            movemap(-1,0);
            break;
        }
        case's':
        case'S':{
            movemap(1,0);
            break;
        }
        case'a':
        case'A':{
            movemap(0,-1);
            break;
        }
        case'd':
        case'D':{
            movemap(0,1);
            break;
        }
        default:
            break;
    }
    drawmap();
};

void movemap(int off_x,int off_y){
    int Playerpos_X=0;
    int Playerpos_Y=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j]==2||map[i][j]==2+3){
                Playerpos_X=i;
                Playerpos_Y=j;
            }
        }
    }

    if(map[Playerpos_X+off_x][Playerpos_Y+off_y]==0||map[Playerpos_X+off_x][Playerpos_Y+off_y]==3){
        map[Playerpos_X][Playerpos_Y]-=2;
        map[Playerpos_X+off_x][Playerpos_Y+off_y]+=2;
    }
}

int endGame(){
    if (map[8][8]==2+3){
        return 0;
    }
    return 1;
}