#include <stdio.h>

// 输入完后使用此函数清空输入缓冲区
void clean_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
