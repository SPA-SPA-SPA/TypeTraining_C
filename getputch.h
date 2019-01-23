/*用于getch/putch的通用头文件"getputch.h"。
这里用了包含头文件保护的头文件的设计。*/
#ifndef __GETPUTCH
    #define __GETPUTCH
    #if defined(_MSC_VER) || (__TURBOC__) || (LST_C) || (__MINGW32__)
        /*MS-Windows/MS-DOS(Visual C++, Borland C++, LSI-C 86 etc ...)
        以上是visual C++、Borland C++（Turbo C++）、LSI C等编程环境各自定义的宏，用于识别环境的。
        如果想用于其他的Windows编程环境，要追加该环境单独定义的宏。*/
        #include <conio.h>
        static void init_getputch(void) {/*空*/}
        static void term_getputch(void) {/*空*/}
    #else
        /*提供了Curses库的UNIX/Linux/OS X环境*/
        #include <curses.h>

        #undef putchar
        #undef puts
        #undef printf
        static char __buf[4096];

        /*---__putchar：相当于putchar函数（用\n\r（换行符+回车符）代替\n进行输出）---*/
        static int __putchar(int ch)
        {
            if(ch == '\n')
                putchar('\r');
            return putchar(ch);
        }

        /*---putch：显示1个字符，清除缓冲区---*/
        static int __putch(int ch)
        {
            int result = putchar(ch);
            fflush(stdout);
            return result;
        }

        /*---__printf：相当于printf函数（用\n\r代替\n进行输出）---*/
        static int __printf(const char *format, ...)
        {
            va_list ap;
            int count;

            __va_start(ap, format);
            vsprintf(__buf, format, ap);
            va_end(ap);
            
            for( count = 0; __buf[count]; count++)
            {
                putchar(__buf[count]);
                if(__buf[count] == '\n')
                    putchar('\r');
            }
            return count;
        }

        /*---__puts：相当于puts函数（用\n\r代替\n进行输出）---*/
        static int __puts(const char *s)
        {
            int i, j;
            
            for( i = 0, j = 0; s[i]; i++)
            {
                __buf[j++] = s[i];
                if(s[i] == '\n')
                    __buf[j++] = '\r';
            }
            return puts(__buf);
        }

        /*---库初始处理---*/
        static void init_getputch(void)
        {
            initscr();
            cbreak();
            noecho();
            refresh();
        }

        /*---库终止处理---*/
        static void term_getputch(void)
        {
            endwin();
        }
        #define putchar __putchar       // 替换调用的函数
        #define printf __printf
        #define puts __puts
    #endif
#endif