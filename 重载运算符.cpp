// ——————————————————————————————————————————————————————————————# C++ 运算符重载通俗讲解 + 全套实例——————————————————————————————————————————————————————————————

// > 核心：运算符重载本质就是**给类自定义运算符对应的函数**，让 + - * = []> < 等符号可以操作对象
// > 格式：`返回值 operator运算符(参数)`

// 分为两类：**成员函数重载**、**全局友元重载**

// ——————————————————————————————————————————————————————————————## 实例 1：重载 + （成员重载，加法，自定义 Point 坐标相加）———————————————————————————————————————————————————

#include<iostream>
using namespace std;

class Point
{
public:
    int x, y;
    Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){}

    //重载 +
    Point operator+(const Point& other)
    {
        Point res;
        res.x = this->x + other.x;
        res.y = this->y + other.y;
        return res;
    }
};
// 1. **`Point`**
// 构造函数，名字必须和类名一模一样，创建对象自动调用。

// 2. **`(int x1 = 0, int y1 = 0)` 默认参数**
// - `x1=0`：不传 x 参数，默认等于 0
// - `y1=0`：不传 y 参数，默认等于 0
// 所以你有 4 种创建方式全部合法：
// Point p1;        // x=0,y=0
// Point p2(5);     // x=5,y=0
// Point p3(2,3);   // x=2,y=3

// 3. **`:` 冒号 → 开启【成员初始化列表】**
// 重点：**初始化列表执行时机早于花括号里面的代码**，是直接初始化成员，不是赋值
// ### 必须用初始化列表的三种成员
// (i. `const int num;` 常量成员
// (ii. `int& ref;` 引用成员
// (iii. 别的自定义类成员（没有默认构造函数）

// 4. **`x(x1), y(y1)`**
// 把形参 `x1` 赋值给成员变量 `x`；`y1` 赋值成员 `y`，等价于但优于下面这种在函数体内赋值：
// Point(int x1=0,int y1=0)
// {
//     x = x1;
//     y = y1;
// }

// 5. **`{}`**
// 构造函数函数体，这里是空，没有额外代码。

int main()
{
    Point a(1,2);
    Point b(3,4);
    Point c = a + b;
    cout << c.x << " " << c.y; //4 6
    return 0;
}
```

// ————————————————————————————————————————————————————————————————## 实例 2：重载 == 、> 比较运算符——————————————————————————————————————————————————————————

```
#include<iostream>
using namespace std;

class Student
{
public:
    int score;
    Student(int s = 0):score(s){}

    bool operator==(const Student& s)
    {
        return score == s.score;
    }

    bool operator>(const Student& s)
    {
        return score > s.score;
    }
};

int main()
{
    Student a(88), b(90);
    cout << (a == b) << endl;
    cout << (b > a) << endl;
    return 0;
}
```

// ————————————————————————————————————————————————————————————## 实例 3：重载 = 赋值运算符（深拷贝重点，最常考）——————————————————————————————————————————————————————————
// 浅拷贝只会复制指针地址，两个对象共用一块内存，析构时重复 delete 崩溃，需要重载 = 实现深拷贝

```
#include<iostream>
using namespace std;

class Arr
{
public:
    int* data;
    Arr(){
        data = new int[3];
    }
    ~Arr(){
        delete[] data;
    }
// 类名是 `Arr`，析构函数格式：`~类名()`，`~` 波浪号是析构函数专属标记
// ——————### 析构函数特性
// 1. 没有返回值、不加 void
// 2. 不能够带参数，所以析构函数只能有一个，不能重载
// 3. 对象生命周期结束时，编译器会自动调用析构函数

//—————— ###什么时候自动执行
// 1. 局部对象离开所在函数作用域
// void test()
// {
//     Arr a;
// } //函数结束，a销毁 → 调用 ~Arr()

// 2. `new` 创建的对象执行 `delete` 的瞬间
// Arr* p = new Arr;
// delete p; //触发析构函数

// ——————###这段代码作用
// 构造函数 `Arr()` 使用 `new[]` 在堆区申请了数组；
// 析构函数 `~Arr()` 里面用 `delete[] data;` 释放堆内存，**防止内存泄漏**。
// ——————### 对比构造‑析构一对搭档

// ```
// Arr()     //构造：创建对象、申请堆内存
// ~Arr()    //析构：销毁对象、释放堆内存
// ```
// ——————### 简单记忆> 构造诞生对象，析构销毁对象；堆里申请的内存，析构负责回收。
    

//赋值重载
    Arr& operator=(const Arr& other)
    {
        if(this == &other) return *this; //防止自己赋值自己

        delete[] data; //先释放左边对象原本持有的旧堆数组，不然旧内存丢失 → **内存泄漏**
        data = new int[3]; //给左边对象开辟一块全新独立的堆数组
        for(int i = 0; i < 3; i++)
        {
            data[i] = other.data[i];
        }
        return *this; //即返回data数组的首地址/指针
    }
};

int main()
{
    Arr a,b;
    a.data[0] = 10;
    b = a;
    cout << b.data[0];
    return 0;
}

// ————————————————————————————————————————————————————————————————## 实例 4：重载 [] 下标运算符，像数组一样访问————————————————————————————————————————————————————————————

#include<iostream>
using namespace std;

class MyArray
{
private:
    int arr[5];
public:
    int& operator[](int index)
    {
        return arr[index];
    }
};

int main()
{
    MyArray a;
    a[0] = 99;
    cout << a[0];
    return 0;
}


// ————————————————————————————————————————————————————————————## 实例 5：重载 << 输出运算符（必须友元，全局重载）————————————————————————————————————————————————————————————————
// 因为 cout 在左边，不能写成类的成员函数

#include<iostream>
using namespace std;

class Point
{
public:
    int x,y;
    Point(int a=0,int b=0):x(a),y(b){}
    friend ostream& operator<<(ostream& out,const Point& p)
    {
        out << "(" << p.x << "," << p.y << ")";
        return out;
    }
};

int main()
{
    Point p(5,6);
    cout << p; //(5,6)
    return 0;
}
```

// ——————————————————————————————————————————————————————————————————## 实例 6：重载 ++ 前置后置自增——————————————————————————————————————————————————————————————————

```
#include<iostream>
using namespace std;

class Num
{
public:
    int val;
    Num(int v=0):val(v){}
    //前置 ++n——————`Num&` = 返回当前对象的引用
    Num& operator++()
    {
        val++;
        return *this;
    }

    //后置 n++，必须多加int占位参数区分——————如果写成 `Num operator++()`（值返回），会产生临时副本，连续自增就会失效
    Num operator++(int)
    {
        Num temp = *this;   //这里没有 &，返回值拷贝；后置 `n++` 需要返回自增之前旧的临时对象
                            // temp 是局部变量，函数结束局部变量会销毁，不能返回引用，只能返回副本。
        val++;
        return temp;
    }
};

// Num n(10);
// ++++n;
// // 前置返回引用，可以等价于 ++(++n)，正常生效
// (n++)++;
// // n++ 返回临时拷贝，第二个++只会操作临时对象，本体不受影响

int main()
{
    Num n(10);
    ++n;
    cout << n.val << endl; //11
    n++;
    cout << n.val << endl; //12
    return 0;
}


# 基础规则总结
1. 成员重载：`对象A + 对象B`，A 是调用者，B 是函数参数
2. `<< >>` 只能全局友元重载
3. 后置自增必须带上 `(int)` 占位参数
4. 赋值运算符 `operator=` 返回引用 `T&`，支持链式赋值 `a=b=c`
5. 不要重载 && || 这类逻辑运算符，会短路失效

