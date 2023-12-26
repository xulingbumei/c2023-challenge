#pragma once

#include "Chess.h"
#include "AI.h"

pair<int, int> center;

void AI::init(Chess* chess)
{
    this->chess = chess;// 指定内部成员chess和chess一致

    int size = chess->getGradeSize();

    for (int i = 0; i < size; i++) {
        vector<int>row;
        for (int j = 0; j < size; j++) {
            row.push_back(0);
        }

        scoreMap.push_back(row);
    }
}

void AI::go(chessmap now,pair<int,int>center,int i)
{
    chessmap next = UCT_search(now, center, i);//注意蒙特卡洛树搜索的返回结果是一张棋盘，后面还要写一个读取下了那

    ChessPos pos=think();
    Sleep(1000);
    chess->chessDown(&pos,CHESS_WHITE);
}

bool operator<(chessmap x, chessmap y)//判断父子节点之间是谁在下棋
{
    for (int i = 0; i < tol_row; i++) {
        for (int j = 0; j < tol_col;j++) {
            if (x.g[i][j] < y.g[i][j]) return 1;
            else if (x.g[i][j] > y.g[i][j])return 0;
        }
    }
}

bool operator==(chessmap x, chessmap y)//判断两个棋盘状况是否相同（为后面判断父子节点关系做铺垫）
{
    for (int i = 0; i < tol_row; i++) {
        for (int j = 0; j < tol_col; j++) {
            if (x.g[i][j] != y.g[i][j])return 0;
        }
    }
    return 1;
}

void AI::calculateScore()//少了跳三的情况，只是静态
{
    int personNum = 0;// 人（黑棋）有多少个棋子连续
    int aiNum = 0;//AI（白棋）方连续有多少颗棋子
    int emptyNum = 0;//该方向上空白位的个数


    //评分数组清零
    for (int i=0; i < scoreMap.size(); i++) {
        for (int j=0; j < scoreMap.size(); j++) {
            scoreMap[i][j] = 0;
        }
    }

    int size = chess->getGradeSize();
    for (int row=0; row < size; row++) {
        for (int col=0; col < size; col++) {

            //对棋盘上每个点进行计算
            if (chess->getGradeData(row, col))continue;

            for (int y = -1; y <= 0; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (y == 0 && x == 0)continue;
                    if (y == 0 && x != 1)continue;//只搜索四个方向

                    aiNum = 0;
                    personNum = 0;
                    emptyNum = 0;

                    //假设黑棋在该位置落子，会构成什么棋型
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;

                        if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
                            &&chess->getGradeData(curRow,curCol)==1) {
                            personNum++;
                        }
                        else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
                                 && chess->getGradeData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else{
                            break;
                        }
                    }

                    //反向继续计算
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
                            && chess->getGradeData(curRow, curCol) == 1) {
                            personNum++;
                        }
                        else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
                                 && chess->getGradeData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }

                    if (personNum == 1) {//连两颗子
                        scoreMap[row][col] += 10;
                    }
                    else if (personNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 30;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 40;
                        }
                    }
                    else if (personNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 60;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 200;
                        }
                    }
                    else if (personNum == 4) {
                        scoreMap[row][col] += 20000;
                    }

                    //假设黑棋在该位置落子，会构成什么棋型
                    emptyNum = 0;

                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size
                            && chess->getGradeData(curRow, curCol) == -1) {
                            aiNum++;
                        }
                        else if (curRow >= 0 && curRow < size
                                 && curCol >= 0 && curCol < size
                                 && chess->getGradeData(curRow, curCol) == 0) {
                            emptyNum ++;
                            break;
                        }
                        else {
                            break;
                        }
                    }

                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size
                            && chess->getGradeData(curRow, curCol) == -1) {
                            aiNum++;
                        }
                        else if (curRow >= 0 && curRow < size
                                 && curCol >= 0 && curCol < size
                                 && chess->getGradeData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }

                    if (aiNum == 0) {
                        scoreMap[row][col] += 5;
                    }
                    else if (aiNum == 1) {
                        scoreMap[row][col] += 10;
                    }
                    else if (aiNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 25;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 50;
                        }
                    }
                    else if (aiNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 55;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 10000;
                        }
                    }
                    else if (aiNum >= 4) {
                        scoreMap[row][col] += 30000;
                    }
                }
            }
        }
    }
}

ChessPos AI::think()
{
    calculateScore();

    vector<ChessPos>maxPoints;
    int maxScore = 0;
    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (chess->getGradeData(row, col) == 0) {
                if (scoreMap[row][col] > maxScore) {
                    maxScore = scoreMap[row][col];
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(row, col));
                }
                else if (scoreMap[row][col] == maxScore) {
                    maxPoints.push_back((ChessPos(row, col)));
                }
            }
        }
    }

    int index = rand() % maxPoints.size();
    return maxPoints[index];
}

chessmap AI::UCT_search(chessmap x, pair<int, int>, int player)
{
    chessmap y = x;
    chessmap ans = y;
    if (check_four(y).first) {
        pair<int, int>u = check_four(y).second;
        ans.g[u.first][u.second] = player + 1;
        return ans;
    }
    if (check_three(y).first) {
        pair<int, int>u = check_three(y).second;
        ans.g[u.first][u.second] = player + 1;
        return ans;
    }
    if (chess->mp.find(x) == chess->mp.end())
    {
        chess->init_chess(x);
    }
    int cnt = 0;//选择次数
    while (cnt <= select_num) {
        cnt++;
        pair<chessmap, int>select_point = tree_policy(x, center, 1);
        for (int j = 0; j < sta_num; j++) {//多次模拟增强效果,再反向传播
            double s = default_policy(select_point.first, select_point.second ^ 1);
            back_up(select_point.first, y, s);
        }
        vector<chessmap>::iterator it;//初始化一个迭代器
        double maxn = UCB(*(chess->mp[y].vec.begin()), player);
        for (it = chess->mp[y].vec.begin(); it != chess->mp[y].vec.end(); it++) {
            if (UCB(*it, player) >= maxn) {
                maxn = UCB(*it, player);
                ans = *it;
            }
        }
    }
    vector<chessmap>().swap(chess->mp[y].vec);//释放内存

    return ans;
}

pair<chessmap, int> AI::tree_policy(chessmap x, pair<int, int> center, int player)
{
    while (!check(x)&&!is_terminal(x)) {
        int col = chess->getGradeSize(), row = chess->getGradeSize();
        int x1 = max(0, center.first - search_range);
        int x2 = min(row, center.first + search_range);
        int y1 = max(0, center.first - search_range);
        int y2 = min(col, center.first + search_range);
        if (cnt_num(x, x1, x2, y1, y2) + chess->mp[x].vec.size() < (x2 - x1 + 1) * (y2 - y1 + 1))
        {//如果节点数量少就拓展
            return mp(expand(x, center, player), player);
        }
        else {
            chessmap y = x;
            vector<chessmap>::iterator it;
            if (chess->mp[y].vec.size() == 0)break;
            double maxn = UCB(*(chess->mp[y].vec.begin()), player);
            for (it = chess->mp[y].vec.begin(); it != chess->mp[y].vec.end(); it++)
            {
                if (UCB(*it, player) >= maxn)
                {
                    maxn = UCB(*it, player);
                    x = *it;
                }
            }
            chess->fa[x] = y;
        }
        player^=1;
    }
    return mp(x,player);
}

chessmap AI::expand(chessmap x, pair<int, int> center, int player)
{
    int row = chess->getGradeSize(), col = chess->getGradeSize();
    chessmap y = x;
    int x1 = max(0, center.first - search_range);
    int x2 = min(row, center.first + search_range);
    int y1 = max(0, center.second - search_range);
    int y2 = min(col, center.second + search_range);
    int cnt = 0;
    while (cnt <= 1000)
    {
        int i = x1 + rand() % (x2 - x1 + 1);
        int j = y1 + rand() % (y2 - y1 + 1);
        int o = x.g[i][j];
        y.g[i][j] = player + 1;
        if (!x.g[i][j] && chess->mp.find(y) == chess->mp.end())
        {
            chess->init_chess(y);
            chess->mp[x].vec.push_back(y);
            chess->fa[y] = x;
            return y;
        }
        y.g[i][j] = o;
        cnt++;
    }
    while (1)
    {
        int i = x1 + rand() % (x2 - x1 + 1);
        int j = y1 + rand() % (y2 - y1 + 1);
        int o = x.g[i][j];
        y.g[i][j] = player + 1;
        if (!x.g[i][j]) {
            if (chess->mp.find(y) == chess->mp.end()) {
                chess->init_chess(y);
            }
            return y;
        }
        y.g[i][j] = o;
    }
}

double AI::UCB(chessmap x, int player)//计算UCB值
{
    if (chess->mp[x].b == 0)return 0;
    double a1 = chess->mp[x].a, b1 = chess->mp[x].b;
    if (a1 + b1 == 0)return inf;
    if (player == 1)return a1 / b1 + sqrt(log(a1 + b1) / b1);
    else if (player == 0)return -a1 / b1+ sqrt(log(a1 + b1) / b1);
}

pair<int, int> AI::cal_centre(chessmap x)
{
    int row = chess->getGradeSize(), col = chess->getGradeSize();
    int cnt = 0, p1 = 0, p2 = 0;
    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j <= col; j++)
        {
            if (x.g[i][j]) {
                cnt++;
                p1 += i;
                p2 += j;
            }
        }
    }
    p1 = max(0, p1 / cnt);
    p2 = max(0, p2 / cnt);
    return mp(p1, p2);
}

double AI::default_policy(chessmap x, int player)//随机走子模拟胜利
{
    int row = chess->getGradeSize(), col = chess->getGradeSize();
    while (1) {
        if (check(x) || is_terminal(x))break;
        pair<int, int>h = cal_centre(x);
        int o = rand() % 100;
        int i, j;
        if (o < 75) {
            i = min(max(0, h.first - search_range + rand() % (search_range * 2 + 1)), row);
            j = min(max(0, h.second - search_range + rand() % (search_range * 2 + 1)), col);
        }
        else {
            i = rand() % (row + 1);
            j = rand() % (col + 1);
        }if (!x.g[i][j]) {
            x.g[i][j] = player + 1;
            player ^= 1;
        }
        if (check(x) == 1)return -1;
        else if (check(x) == 2)return 1;
        else return 0;
    }
}

void AI::back_up(chessmap x, chessmap y, int value)
{
    chess->mp[x].a += value;
    chess->mp[x].b++;
    while (!(x == y) ){
        if (chess->fa.find(x) == chess->fa.end()) { break; }
        x = chess->fa[x];
        chess->mp[x].a += value;
        chess->mp[x].b++;
    }
}

pair<int, pair<int, int>> AI::check_four(chessmap x)
{
    return pair<int, pair<int, int>>();
}

pair<int, pair<int, int>> AI::check_three(chessmap y)
{
    return pair<int, pair<int, int>>();
}

int AI::check(chessmap x)
{
    return 0;
}

int AI::check_win(chessmap x, int player)
{
    return 0;
}
int AI::is_terminal(chessmap x)
{
    return 0;
}

int AI::cnt_num(chessmap x, int x1, int x2, int y1, int y2)
{
    return 0;
}
