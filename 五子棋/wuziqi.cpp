#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

// -------------------- 数据设计 --------------------
int board[19][19];
int flag;
// -------------------- 数据设计 --------------------

// -------------------- service --------------------
void init();
int isWin(int x, int y);
int playerMove(int x, int y);
// -------------------- service --------------------

// -------------------- view --------------------
void menuView();
void gameView_ShowBoard();
void winView();
void gameView();
// -------------------- view --------------------

int main()
{
    menuView();
    return 0;
}

void init()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            board[i][j] = 0;
        }
    }
    flag = 0;
}

int isWin(int x, int y)
{
    int stone = (flag % 2 == 0) ? 1 : 2;
    int stone_count = 1;
    int index_1 = x;
    int index_2 = x;
    bool left = 1;
    bool right = 1;

    // 1. 水平方向判断
    while (left || right)
    {
        left = (index_1 - 1 >= 0) && (board[y][index_1 - 1] == stone);
        right = (index_2 + 1 < 19) && (board[y][index_2 + 1] == stone);

        if (left) { stone_count++; index_1--; }
        if (right) { stone_count++; index_2++; }
    }
    if (stone_count >= 5) return stone;

    // 2. 垂直方向判断
    stone_count = 1;
    index_1 = y;
    index_2 = y;
    bool under = 1;
    bool above = 1;
    while (above || under)
    {
        under = (index_1 - 1 >= 0) && (board[index_1 - 1][x] == stone);
        above = (index_2 + 1 < 19) && (board[index_2 + 1][x] == stone);

        if (above) { stone_count++; index_2++; }
        if (under) { stone_count++; index_1--; }
    }
    if (stone_count >= 5) return stone;

    // 3. 反斜线(\)方向判断
    stone_count = 1;
    index_1 = index_2 = x;
    int index_3 = y;
    int index_4 = y;
    bool upper_left = 1;
    bool lower_right = 1;
    while (upper_left || lower_right)
    {
        upper_left = (index_1 - 1 >= 0 && index_4 + 1 < 19) && (board[index_4 + 1][index_1 - 1] == stone);
        lower_right = (index_3 - 1 >= 0 && index_2 + 1 < 19) && (board[index_3 - 1][index_2 + 1] == stone);

        if (upper_left) { stone_count++; index_1--; index_4++; }
        if (lower_right) { stone_count++; index_3--; index_2++; }
    }
    if (stone_count >= 5) return stone;

    // 4. 斜线(/)方向判断
    stone_count = 1;
    index_1 = index_2 = x;
    index_3 = index_4 = y;
    bool lower_left = 1;
    bool upper_right = 1;
    while (lower_left || upper_right)
    {
        lower_left = (index_1 - 1 >= 0 && index_3 - 1 >= 0) && (board[index_3 - 1][index_1 - 1] == stone);
        upper_right = (index_4 + 1 < 19 && index_2 + 1 < 19) && (board[index_4 + 1][index_2 + 1] == stone);

        if (lower_left) { stone_count++; index_1--; index_3--; }
        if (upper_right) { stone_count++; index_4++; index_2++; }
    }
    if (stone_count >= 5) return stone;

    return 0;
}

int playerMove(int x, int y)
{
    int stone = (flag % 2 == 0) ? 1 : 2;
    if (board[y][x] == 0)
    {
        board[y][x] = stone;
        return 1;
    }
    return 0;
}

void menuView()
{
    int n;
    while (1)
    {
        system("cls");
        printf("===== 五子棋游戏 =====\n");
        printf("  1. 进入游戏\n");
        printf("  2. 进入设置\n");
        printf("  3. 退出游戏\n");
        printf("=====================\n");
        printf("请选择：");
        scanf_s("%d", &n);
        printf("\n");

        switch (n)
        {
        case 1:
            gameView();
            break;
        case 2:
            printf("敬请期待...\n");
            system("pause");  // 暂停让用户看到提示
            continue;
        case 3:
            exit(0);
            break;
        default:
            printf("输入错误，请重新选择！\n");
            system("pause");
            continue;
        }
    }
}

// 核心修改：替换数字为直观字符，优化棋盘显示
void gameView_ShowBoard()
{
    system("cls");  // 每次打印棋盘前清屏
    // 打印列坐标（0-18）
    printf("   ");
    for (int j = 0; j < 19; j++)
    {
        printf("%2d ", j);  // 占2位，对齐
    }
    printf("\n");

    // 打印棋盘内容 + 行坐标（0-18）
    for (int i = 0; i < 19; i++)
    {
        printf("%2d ", i);  // 行坐标占2位
        for (int j = 0; j < 19; j++)
        {
            if (board[i][j] == 1)
                printf(" ● ");  // 黑子用●表示
            else if (board[i][j] == 2)
                printf(" ○ ");  // 白子用○表示
            else
                printf(" + ");  // 空地用+表示
        }
        printf("\n");
    }
    printf("\n");
}

void winView()
{
    int stone = (flag % 2 == 0) ? 1 : 2;
    printf("\n===================================\n");
    if (stone == 1)
        printf("        黑棋(●) 胜利！ \n");
    else
        printf("        白棋(○) 胜利！ \n");
    printf("===================================\n");

    while (getchar() != '\n');  // 清空缓冲区
    printf("按任意键后回车退出...");
    getchar();
    printf("\n");
}

void gameView()
{
    init();
    int x, y;

    while (1)
    {
        gameView_ShowBoard();

        int stone = (flag % 2 == 0) ? 1 : 2;
        printf("当前回合：%d\n", flag);
        printf("玩家 %s 落子（输入x y，范围0-18）：", (stone == 1) ? "●(黑)" : "○(白)");

        // 检查输入合法性
        int ret = scanf_s("%d %d", &x, &y);
        if (ret != 2 || x < 0 || x > 18 || y < 0 || y > 18)
        {
            while (getchar() != '\n');  // 清空错误输入
            printf("坐标超出范围(0-18)或格式错误，请重新输入!\n");
            system("pause");
            continue;
        }

        printf("\n");

        // 修正坐标逻辑：如果想让输入的y对应棋盘视觉上的行，注释掉这行
        // y = 18 - y;

        int move = playerMove(x, y);
        if (move == 0)
        {
            printf("该位置已有棋子，请选择其他位置！\n");
            system("pause");
            continue;
        }

        int result = isWin(x, y);
        if (result != 0)
        {
            gameView_ShowBoard();
            winView();
            break;
        }

        flag++;
    }
}