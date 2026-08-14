具有C风格的写法：（或者就是C的写法hhh）

#include <stdio.h>
#include <string.h>

struct data {
	char first[20];
	char last[20];
	int employee_id;
	int last_4_SSN;
	char title[20];
};

struct employees {
	struct data employee1;
	struct data employee2;
} engineering_dept;  // 声明全局变量 engineering_dept

int main(void)
{
	for(int i = 0; i < 2; i++) {
		struct data *employee = &engineering_dept.employee1;     // employ为 data类型结构体的指针， 指向 engineering_dept.employee_的地址
		if(i > 0)
			employee = &engineering_dept.employee2;

		printf("Enter the employee's first name: ");
		scanf("%s", employee->first);                            //不用&，直接指向的是首个字母的地址

		printf("Enter the employee's last name: ");
		scanf("%s", employee->last);    

		printf("Enter the employee's ID number: ");
		scanf("%d", &employee->employee_id);                     // int 类型则需要取地址

		printf("Enter the last four digits of the employee's SSN: ");
		scanf("%d", &employee->last_4_SSN);

		printf("Enter the employee's job title (do not include the word 'Engineer'): ");
		scanf("%s", employee->title);    

		puts("");
	}

	for(int i = 0; i < 2; i++) {
		struct data *employee = &engineering_dept.employee1;
		if(i > 0)
			employee = &engineering_dept.employee2;

		printf("\nEmployee information for %s %s: ", employee->first, employee->last);  
		printf("\nID: %d", employee->employee_id);
		printf("\nSSN: %d", employee->last_4_SSN);
		printf("\nTitle: %s Engineer\n", employee->title);
	}

	return 0;
}

————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

现在员工数量不再固定写死 2 个，由用户输入 n。
不能再写固定的`employee1、employee2`，要用**结构体动态数组（malloc）**。

完整 C 代码：

```
#include <stdio.h>
#include <stdlib.h>

//单个员工的数据结构
struct data {
    char first[20];
    char last[20];
    int employee_id;
    int last_4_SSN;
    char title[20];
};

int main(void)
{
    int n;
    printf("请输入员工数量：");
    scanf("%d", &n);

    // 动态分配：n个struct data大小的数组
    struct data* dept = (struct data*)malloc(n * sizeof(struct data));
    if(dept == NULL)
    {
        printf("内存分配失败\n");
        return -1;
    }

    //输入n位员工信息
    for(int i = 0; i < n; i++)
    {
        printf("\n---输入第 %d 位员工信息---\n", i+1);

        printf("Enter the employee's first name: ");
        scanf("%s", dept[i].first);

        printf("Enter the employee's last name: ");
        scanf("%s", dept[i].last);

        printf("Enter the employee's ID number: ");
        scanf("%d", &dept[i].employee_id);

        printf("Enter the last four digits of the employee's SSN: ");
        scanf("%d", &dept[i].last_4_SSN);

        printf("Enter the employee's job title: ");
        scanf("%s", dept[i].title);
    }

    //打印全部员工
    for(int i = 0; i < n; i++)
    {
        printf("\n==== Employee information for %s %s ====\n",
               dept[i].first, dept[i].last);
        printf("ID: %d\n", dept[i].employee_id);
        printf("SSN: %d\n", dept[i].last_4_SSN);
        printf("Title: %s Engineer\n", dept[i].title);
    }

    free(dept);   //释放动态结构体数组
    dept = NULL;

    return 0;
}
```

#########   关键点讲解    ##########

1. `struct data* dept = (struct data*)malloc(n * sizeof(struct data));`
- 在堆上开辟一块连续内存，可以存放 `n` 个`struct data`员工结构体。
- `dept`是指针，可以像数组一样用 `dept[i]`访问第 i 个员工。（即 `dept[i]` 是 `*(dept + i)` 的**语法糖**。）


2. 访问成员
```
dept[i].first;         //dept[i]是结构体变量，用 . 点号
&dept[i].employee_id;  //int变量scanf需要&
```
> `dept[i]`等价于 `*(dept+i)`，结构体变量，用`.`，**不是 ->**。

#######   用指针写法（等价）  #######
```
struct data* p = dept;         //第0位员工
scanf("%s", p->first);
scanf("%d", &p->employee_id);
p++;                           //指针往后移动一个结构体大小，到下一位员工
```

3. 用完必须 `free(dept)`，防止内存泄漏。
