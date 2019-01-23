/*多个字符串的键盘打字练习（其二：打乱出题顺序“方法一”）*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getputch.h"

#define QNO 12              // 题目数量
#define swap(type, x, y) do{type t = x; x = y; y = t;}while(0)

int main(int argc, char const *argv[])
{
    char *str[QNO] = {"book", "computer", "default", "comfort",
                      "monday", "power", "light", "music",
                      "programming", "dog", "video", "include",};
    int i, stage;
    int qno[QNO];           // 出题顺序
    clock_t start, end;     // 开始时钟数和结束时钟数

    init_getputch();
    srand(time(NULL));      // 设定随机数的种子

    for(i = 0; i < QNO; i++)
        qno[i] = i;
    for( i = QNO - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        if(i != j)
            swap(int, qno[i], qno[j]);
    }
    printf("开始打字练习。\n");
    printf("按下空格键练习。\n");
    while(getch() != ' ')                   // 等待玩家按下空格开始
        ;
    start = clock();                        // 开始时钟数
    for( stage = 0; stage < QNO; stage++)
    {
        int len = strlen(str[qno[stage]]);  // 字符串str[qno[stage]]的字符数量
        for( i = 0; i < len; i++)
        {                                   // 显示str[qno[stage]][i]之后的字符并把光标返回到开头
            printf("%s \r", &str[qno[stage]][i]);
            fflush(stdout);
            while(getch() != str[qno[stage]][i])
                ;
        }
    }
    end = clock();                          // 结束时钟数
    printf("\r用时%.1f秒。\n", (double)(end -start) / CLOCKS_PER_SEC);
    term_getputch();
    return 0;
}
