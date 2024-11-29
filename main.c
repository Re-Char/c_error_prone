#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
// #include "include/a.h"

//运算类错误
void operation() {
    // 除零错误（ub行为）
    int a = 1, b = 0;
    float c = a / b;
    printf("%f\n", c);

    // 整数相除
    a = 100000000, b = 99999999;
    float d = (float) a / b;
    printf("%.7f\n", d);

    //数据比较
    printf("%d\n", 1 == d);
    unsigned int u_a = 1;
    int s_a = -1;
    printf("%d\n", s_a >  u_a);

    //逻辑运算
    printf("%d\n", 0 && 1 || 1);
    printf("%d %d\n", !(0 && 0), !0 && 0);

    //逻辑短路
    if (a || b ++)
        printf("%d\n", b);
    if (0 && b ++);
    printf("%d\n", b);

    //p ++和++ p
    int num[] = {0, 1, 2};
    int *p = num;
    printf("%d\n", *p++);
    printf("%d\n", *++p);
}

//变量类错误
void variable() {
    //静态局部变量
    static int a = 7;
    a++;
    printf("%d\n", a);

    //静态全局变量
    // print();

    //整型变量
    printf("%d\n", INT_MAX);

    //浮点型变量
    float f_a = 47.2;
    double d_a = 47.2;
    printf("%.15f\n", f_a);
    printf("%d\n", f_a == 47.2);
}

//数组类错误
void array() {
    //数组下标越界（ub行为）
    int num[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i ++) {
        printf("%d ", num[i]);
    }
    printf("\n");

    //字符串长度（重点是ub行为）
    char str1[6] = {'H', 'e', 'l', 'l', 'o'};
    printf("%s\n", str1);
    printf("%d\n", strlen(str1));
    int len = 0;
    for (int i = 0; str1[i] != '\0'; i++) {
        len++;
    }
    printf("%d\n", len);
    char *str2 = (char *) malloc(sizeof(char) * 5);
    printf("%s\n", str2);
    printf("%d\n", strlen(str2));
    free(str2);
}

//输入和输出
void input_and_output() {
    //输入
    char str1[3] = { 0 };
    for (int i = 0; i < 3; i++) {
        scanf("%c ", &str1[i]);
    }
    for (int i = 0; i < 3; i++) {
        printf("%c ", str1[i]);
    }
    printf("\n");
    char tmp1;
    scanf("%c", &tmp1);
    printf("%c\n", tmp1);
    char *str2 = (char *) malloc(sizeof(char) * 10);
    scanf("%9s", str2);
    printf("%s\n", str2);
    char tmp2;
    scanf("%c", &tmp2);
    printf("%c", tmp2);
    free(str2);

    //输出
    char str3[] = "114514";
    printf(" %d", printf("%010s", str3));
}

int main() {
    // operation();
    // for (int i = 0; i < 10; i ++) {
    //     variable();
    // }
    // variable();
    // array();
    // input_and_output();
}
