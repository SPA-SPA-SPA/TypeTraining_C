/*一个字符串的键盘打字练习（其一）*/

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "getputch.h"

int main(int argc, char const *argv[])
{
    int i;
    char *str = "How do you do?";           // 要输入的字符串
    int len = strlen(str);                  // 字符串的字符数量
    clock_t start, end;                     // 开始时钟数和结束时钟数

    init_getputch();                        // 表示初始化getput.h的意思吧，去掉也没有什么编译问题，我试过了。
                                            // 下面的term_getput()也一样。毕竟头文件中的定义是空的函数。
    printf("请照着输入。\n");
    printf("%s\n", str);                    // 显示要输入的字符串
    fflush(stdout);

    start = clock();                        // 开始时钟数
    
    for( i = 0; i < len; i++)
    {
        int ch;
        do
        {
            ch = getch();                   // 从键盘读取信息
            if (isprint(ch)) {
                putch(ch);                  // 显示按下的键
                if(ch != str[i])            // 如果按错了键
                    putch('\b');            // 把光标往前退一格
            }
        } while (ch != str[i]);
    }
    end = clock();                          // 结束时钟数
    printf("\n用时%.1f秒。\n", (double)(end - start) / CLOCKS_PER_SEC);
    term_getputch();

    return 0;
}
