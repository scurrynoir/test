#include <stdio.h>

struct example {
	int integer;
};                                   //定义结构体

int main (void)
{
	struct example *ptr;               //定义结构体指针ptr，目前是随机垃圾地址
	struct example test;               //栈上创建结构体变量test

	ptr = &test;

	test.integer = 5;                  //或 ptr->intger
	printf("%d\n", test.integer);

	(*ptr).integer = 6;                // *ptr解引用得到test本体； . 访问成员
	printf("%d\n", test.integer);

	ptr->integer = 7;
	printf("%d\n", test.integer);

	return 0;
}
