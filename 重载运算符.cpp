# C++ 运算符重载通俗讲解 + 全套实例

> 
> 核心：运算符重载本质就是**给类自定义运算符对应的函数**，让 + - * = []> < 等符号可以操作对象
> 格式：`返回值 operator运算符(参数)`

分为两类：**成员函数重载**、**全局友元重载**

## 实例 1：重载 + （成员重载，加法，自定义 Point 坐标相加）

```
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

int main()
{
    Point a(1,2);
    Point b(3,4);
    Point c = a + b;
    cout << c.x << " " << c.y; //4 6
    return 0;
}
```

## 实例 2：重载 == 、> 比较运算符

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

## 实例 3：重载 = 赋值运算符（深拷贝重点，最常考）

浅拷贝只会复制指针地址，两个对象共用一块内存，析构时重复 delete 崩溃，需要重载 = 实现深拷贝

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

    //赋值重载
    Arr& operator=(const Arr& other)
    {
        if(this == &other) return *this; //防止自己赋值自己

        delete[] data; //释放自身旧空间
        data = new int[3];
        for(int i = 0; i < 3; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
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
```

## 实例 4：重载 [] 下标运算符，像数组一样访问

```
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
```

## 实例 5：重载 << 输出运算符（必须友元，全局重载）

> 
> 因为 cout 在左边，不能写成类的成员函数

```
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

## 实例 6：重载 ++ 前置后置自增

```
#include<iostream>
using namespace std;

class Num
{
public:
    int val;
    Num(int v=0):val(v){}

    //前置 ++n
    Num& operator++()
    {
        val++;
        return *this;
    }

    //后置 n++，必须多加int占位参数区分
    Num operator++(int)
    {
        Num temp = *this;
        val++;
        return temp;
    }
};

int main()
{
    Num n(10);
    ++n;
    cout << n.val << endl; //11
    n++;
    cout << n.val << endl; //12
    return 0;
}
```

# 基础规则总结

1. 成员重载：`对象A + 对象B`，A 是调用者，B 是函数参数
2. `<< >>` 只能全局友元重载
3. 后置自增必须带上 `(int)` 占位参数
4. 赋值运算符 `operator=` 返回引用 `T&`，支持链式赋值 `a=b=c`
5. 不要重载 && || 这类逻辑运算符，会短路失效

需要我再写链表类运算符重载、或者 - * / 例子吗？

Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){}

搜索一下

# 整句拆解：`Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){}`

这是 **Point 类的构造函数 + 默认参数 + 成员初始化列表**，我拆开每一段讲解

```
class Point
{
public:
    int x, y;
    // 下面这句就是构造函数
    Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){}
};
```

## 分段解析

1. **`Point`**
构造函数，名字必须和类名一模一样，创建对象自动调用。
2. **`(int x1 = 0, int y1 = 0)` 默认参数**

- `x1=0`：不传 x 参数，默认等于 0
- `y1=0`：不传 y 参数，默认等于 0

所以你有 4 种创建方式全部合法：

```
Point p1;        // x=0,y=0
Point p2(5);     // x=5,y=0
Point p3(2,3);   // x=2,y=3
```

3. **`:` 冒号 → 开启【成员初始化列表】**

> 
> 重点：**初始化列表执行时机早于花括号里面的代码**，是直接初始化成员，不是赋值Microsoft ...

4. **`x(x1), y(y1)`**
把形参 `x1` 赋值给成员变量 `x`；`y1` 赋值成员 `y`
等价于但优于下面这种在函数体内赋值：

```
Point(int x1=0,int y1=0)
{
    x = x1;
    y = y1;
}
```

5. **`{}`**
构造函数函数体，这里是空，没有额外代码。

---

## 初始化列表 和 函数体内赋值核心区别

1. 初始化列表：**初始化**，对象诞生的时候直接给初始值
2. 花括号里面：先创建成员变量（随机垃圾值），之后再赋值覆盖

### 必须用初始化列表的三种成员

- `const int num;` 常量成员
- `int& ref;` 引用成员
- 别的自定义类成员（没有默认构造函数）

示例

```
class Test{
public:
    const int a;
    int &b;
    Test(int x,int &r):a(x),b(r){} //只能初始化列表
};
```

---

## 通俗对比两种写法

写法 A（初始化列表，推荐）

```
Point(int x1=0,int y1=0):x(x1),y(y1){}
```

写法 B（构造体内赋值）

```
Point(int x1=0,int y1=0)
{
    x = x1;
    y = y1;
}
```

内置 int 效果差不多；**自定义对象、const、引用必须选 A**

---

## 拓展花括号初始化（C++11）

```
Point p{10,20};
```

同样调用该构造函数，x=10，y=20

如果你需要，我给你整理一份**构造函数、拷贝构造、初始化列表速查表**。

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

// 赋值重载
Arr& operator=(const Arr& other)
{
if (this == &other) return *this; // 防止自己赋值自己

delete [] data; // 释放自身旧空间
data = new int [3];
for (int i = 0; i < 3; i++)
{
data [i] = other.data [i];
}
return *this;
}

};

int main ()
{
Arr a,b;
a.data [0] = 10;
b = a;
cout << b.data [0];
return 0;
}
解释一下

# 通俗讲解 friend（友元）

## 1. friend 含义

`friend` 代表**友元**，可以让外部函数、别的类，拥有访问本类私有成员的权限。

先梳理 `operator<<` 输出运算符的困境：

```
cout << p
```

等价于：`operator<<(cout, p)`

- 左边参数是 `ostream` 对象（cout），右边才是你的 Point
- 运算符重载成员函数，只能**对象在左边** `p << cout`，不符合使用习惯

所以 << 不能写成 Point 的成员函数，只能写成**全局普通函数**。
如果你的 x、y 改成 private 私有属性，全局函数正常情况下访问不到私有变量。
这时就需要 `friend`，把输出函数声明成 Point 的好朋友，可以读取私有成员。

## 2. 逐行解析

```
friend ostream& operator<<(ostream& out,const Point& p)
```

1. `friend`：告知编译器，该全局函数是本类的友元
2. 即便 x,y‑设置成 private，函数依旧能够读取 p.x、p.y
3. 函数本身不属于这个类，依旧是全局函数

## 3. 举例子区分公有和私有

### ①成员全部 public，不用 friend 也能访问

你现在代码 x、y 是 public，公开成员，外面函数本来就能访问，friend 此时可有可无。

### ②x,y 改成 private，就必须友元

```
class Point
{
private:
    int x,y;
public:
    Point(int a=0,int b=0):x(a),y(b){}

    friend ostream& operator<<(ostream& out,const Point& p);
};

ostream& operator<<(ostream& out,const Point& p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}
```

> 
> x、y 被私有化，外部普通函数无权访问；只有被 friend 标记的友元函数可以访问私有变量

## 4. 友元两类形式

1. **友元函数**：现在这种重载 <<
2. **友元类**

```
friend class Test;
```

Test 类全部函数都可以访问当前类私有成员

## 5. 重点注意事项

1. 友元声明只是授权访问权限，**友元函数并不是类的成员函数**
2. 友元关系单向：A 把 B 当作朋友，A 允许 B 访问自己私有；A 不能访问 B 私有
3. 友元不能继承、不能传递
4. 日常固定套路：`<<` 输出重载、`>>` 输入重载几乎都要用 friend

## 简单总结

> 
> friend = 好朋友通行证，拿到权限，可以读取类里面的私有成员。
