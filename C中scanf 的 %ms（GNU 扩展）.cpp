——————————————————————————————————————————————————————————————————### `%ms`（GNU 扩展）————————————————————————————————————————————————————————————————————————————————

```
char *p;
scanf("%ms", &p);
```
1. scanf 内部`malloc`堆内存。
2. 将读到的字符串 +`\0`存入 malloc 得到的堆空间。
3. 把 malloc 返回的地址赋值给你的指针变量`p`。
4. **内存是堆上的，使用者必须 free 释放**。

e.g.
#include <stdio.h>
#include <stdlib.h>

int main(void){
  //initialize vars
  char *first;  // 创建两个指向char类型首个字母地址的指针（**没有分配内存，不能直接存字符串**。普通`%s`不能写`scanf("%s",first)`，会崩溃。）
  char *last;

  //prompt user to input first and last name and use scanf() to store those to the initiliazed vars
  printf("Enter your first name: ");
  scanf("%ms", &first);               //  `&first`：取指针变量 first 的地址（类型`char**`）
  printf("Enter your last name: ");
  scanf("%ms", &last);

  //print the welcome message!
  printf("Hello %s %s!\n", first, last);

  free(first);
  free(last);
}
