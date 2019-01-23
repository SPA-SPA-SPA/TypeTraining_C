/*多个字符串的键盘打字练习（其一）*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "getputch.h"

#define QNO 12              // 题目数量

int main(int argc, char const *argv[])
{
    char *str[QNO] = {"book", "computer", "default", "comfort",
                      "monday", "power", "light", "music",
                      "programming", "dog", "video", "include",};
    int i, stage;
    clock_t start, end;     // 开始时钟数和结束时钟数

    init_getputch();
    printf("开始打字练习。\n");
    printf("按下空格键开始。\n");
    while(getch() != ' ')     // 一直等待到玩家按下空格键
        ;
    start = clock();        // 开始时钟数
    
    for( stage = 0; stage < QNO; stage++)
    {
        int len = strlen(str[stage]);       // 字符串str[stage]的字符数量
        for( i = 0; i < len; i++)
        {                                   // 显示str[stage][i]以后的字符并把光标返回开头
            printf("%s \r", &str[stage][i]);
            fflush(stdout);
            while(getch() != str[stage][i])
                ;
        }
    }
    end = clock();          // 结束时钟数
    printf("\r用时%.1f秒。\n", (double)(end -start) / CLOCKS_PER_SEC);
    term_getputch();
    return 0;
}
