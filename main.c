// #include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "include/a.h"
/*
include头文件其实就是复制粘贴头文件里面的内容到这里.a.h包含了一个静态全局变量static int a = 0;
a.c里定义了一个打印函数打印a的值
*/

//运算类错误
void operation() {
    // 除零错误（ub行为） undefined behaviour，会造成程序崩溃或其他不可预知的问题
    int a = 1, b = 0;
    float c = a / b;
    printf("%f\n", c);

    // 整数相除
    a = 100000000, b = 99999999; // 两个整数相除返回一个整数，比如float d = 10 / 3;此时d = 3.0000000； 
    float d = (float)a / b;
    printf("%.7f\n", d); //精度有限，float型大概在小数点后7位，double大概在小数点后15位

    //数据比较
    printf("%d\n", 1 == d); //此时1 == d是正确的
    unsigned int u_a = 1; //二进制：00000000000000000000000000000001
    int s_a = -1; // 二进制：11111111111111111111111111111111
    /*
    原码：例子，2的二进制是0010，3的二进制是0011。
    补码：正数和原码相同，负数为其相反数原码先减一再按位取反。 例子：-2的二进制是1110，-3的二进制是1101(但是INT_MIN不是，INT_MIN是10000000000000000000000000000000看起来像一个“-0”)
    int型数据第一位是符号位，0表示非负数，1表示负数(通过补码也不难看出负数的最高位绝对是1)
    int型数据占4个字节，也就是32位，表示的数的范围是-2^31 -> 2^31 - 1(其二进制为10000000000000000000000000000000 -> 01111111111111111111111111111111)
    unsigned int的表示范围为0 -> 2^32 - 1(unsigned int型数据没有符号位，所以最大值是11111111111111111111111111111111)
    */
    printf("%d\n", s_a > u_a); //会把s_a当作unsigned int来解释，故肯定比1大

    // //逻辑运算
    printf("%d\n", (0 && 1) || 1);
    printf("%d %d\n", !(0 && 0), !0 && 0);//!是否，~它是位运算符号
    // & | ~
    printf("%d\n", 2 & 3);// 0010 & 0011 = 0010
    printf("%d\n", 2 | 3);// 0010 | 0011 = 0011
    printf("%d\n", ~2);// ~0010 = 1101 = -3

    // //逻辑短路
    if (a || b ++)//a为true后面不会再判断了
        printf("%d\n", b); 
    if (0 && b ++);//0为false后面不会再判断了
    printf("%d\n", b);

    // //p ++和++ p
    int num[] = {0, 1, 2};
    int *p = num;
    printf("%d\n", *p++);//先返回p,再+1
    printf("%d\n", *++p);//p先+1,再返回p
}

//变量类错误
void variable() {
    static int a = 7; // 虽然是局部变量,但是和程序整个生命周期一样,只会被初始化一次,和全局变量之间可以重名,互不干扰.
    a++;
    printf("%d\n", a);

    //静态全局变量
    print();//每个文件里的静态全局变量互不干扰,每个文件都有自己的副本且作用域就只在那个文件内,如果有重名的局部变量,编译器会自动帮你使用合适的变量.在这个例子中,如果你把局部变量的static int给删除掉也不会影响print函数中打印的a全局变量的值.

    //整型变量
    printf("%d\n", INT_MAX + 1); //INT_MAX是0 + 31个1, INT_MIN是1 + 31个0

    // //浮点型变量
    float f_a = 47.2; //0.2*2=0.4 0.4*2=0.8 0.8*2=1.6 0.6*2=1.2 0.2,不可能精确表示小数点0.2
    double d_a = 47.2;
    printf("%.15lf\n", d_a);
    printf("%d\n", f_a == 47.2);
}

//数组类错误
void array() {
    //数组下标越界（ub行为）
    int num[5] = {0, 1, 2, 3, 4};
    for (int i = -1; i < 6; i ++) { //ub行为造成的垃圾值
        printf("%d ", num[i]);
    }
    printf("\n");

    //字符串长度（重点是ub行为）
    char str1[6] = {'H', 'e', 'l', 'l', 'o'};//字符串以'\0'结尾,第六个空间会自动给你赋成'\0',如果只给了str1[5]且已经赋了五个非零值,那么有可能会出现ub行为
    printf("%s\n", str1);
    printf("%d\n", strlen(str1));//strlen函数会找到'\0'来自动结束查找,你可以在上面的初始化中将中间的某个值改成'\0'再来看看这个strlen返回多少的值.
    int len = 0;
    for (int i = 0; str1[i] != '\0'; i++) {
        len++;
    } //模拟strlen函数
    printf("%d\n", len);
    char *str2 = (char *) malloc(sizeof(char) * 5);
    // memset(str2, 0, 5); 初始化
    printf("%s\n", str2);        // 只是开辟空间没有初始化会有ub行为产生垃圾值
    printf("%d\n", strlen(str2));//这里因为ub行为甚至会输出6,超过了我们给的空间的最大长度5
    free(str2);
}

//输入和输出
void input_and_output() {
    //输入
    char str1[4] = { 0 };
    for (int i = 0; i < 3; i++) {
        scanf("%c ", &str1[i]);
    }//空格会匹配任意多个空白符(常见的包括空格,tab和回车),所以在这里你敲多少个回车都没有用,除非输入一个非空白字符
    for (int i = 0; i < 3; i++) {
        printf("%c ", str1[i]);
    }
    printf("\n");
    char tmp1;
    scanf("%c", &tmp1);//上面的例子中你最后敲的非空白符会停留在输入流中,这个scanf会直接读取输入流,然后发现有可以匹配的字符(你那个非空白符),于是直接读入,不会等待用户输入
    printf("%c\n", tmp1);
    char *str2 = (char *) malloc(sizeof(char) * 10);
    // fgets(str2, 10, stdin);这里上课讲错了,它可以读入任意的字符,无论是空白符还是非空白符,其读入的长度是第二个参数(这里是10),长度一般和你定义的数组的长度保持一致即可,它会自己在末尾补'\0',也就是说有效读入长度还是9.
    scanf("%9s", str2);//不是一个安全的函数,当没有限制长度(这里用了%9s来限制读入的长度)的时候很容易发生ub行为
    printf("%s\n", str2);
    //getchar();截取任意一个字符,这里是因为scanf后的回车不会被读入而留在了输入流中,如果不限读取这个回车,那么下一个tmp2就会被直接赋值为'\n'
    char tmp2;
    scanf("%c", &tmp2);
    printf("%c", tmp2);
    free(str2);

    //输出
    char str3[] = "114514";
    printf(" %d", printf("%10s", str3));//printf这个函数会返回str的长度,如果返回值小于1说明printf函数出错了
}

int main() {
    operation();
    for (int i = 0; i < 10; i ++) {
        variable();
    }
    variable();
    array();
    input_and_output();
}