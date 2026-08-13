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

int main ()
{
    Point p (5,6);
    cout << p; //(5,6)
    return 0;
}




# 通俗讲解 friend（友元）

## 1. friend 含义 ———— `friend` 代表**友元**，可以让外部函数、别的类，拥有访问本类私有成员的权限。

先梳理 `operator<<` 输出运算符的困境：

```
```plaintext
cout << p

```
```

等价于：`operator<<(cout, p)`

- 左边参数是 `ostream` 对象（cout），右边才是你的 Point
- 运算符重载成员函数，只能对象在左边 `p << cout`，不符合使用习惯
所以 << 不能写成 Point 的成员函数，只能写成**全局普通函数**。
如果你的 x、y 改成 private 私有属性，全局函数正常情况下访问不到私有变量。
这时就需要 `friend`，把输出函数声明成 Point 的好朋友，可以读取私有成员。

## 2. 逐行解析

```
```plaintext
friend ostream& operator<<(ostream& out,const Point& p)

```
```

1. `friend`：告知编译器，该全局函数是本类的友元
2. 即便 x,y‑设置成 private，函数依旧能够读取 p.x、p.y
3. 函数本身不属于这个类，依旧是全局函数

## 3. 举例子区分公有和私有

### ①成员全部 public，不用 friend 也能访问

你现在代码 x、y 是 public，公开成员，外面函数本来就能访问，friend 此时可有可无。

### ②x,y 改成 private，就必须友元

```
```plaintext
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
```

> 
> x、y 被私有化，外部普通函数无权访问；只有被 friend 标记的友元函数可以访问私有变量
> // 逐行解释：

1. `operator<<` 就是重载 `cout <<` 输出运算符
2. 运算符左边是 `cout`，也就是 `ostream& out`，**不能写成类的成员函数**（成员函数第一个参数必须是 this‑指针）
3. 所以只能做成普通全局函数
4. 可是 x、y 是 private 私有，全局函数不能读取
5. `friend`：声明该全局函数是 Point 的好朋友，可以访问类里面所有私有成员

## 4. 友元两类形式

1. **友元函数**：现在这种重载 <<
2. **友元类**

```
```plaintext
friend class Test;

```
```

Test 类全部函数都可以访问当前类私有成员

## 5. 重点注意事项

1. 友元声明只是授权访问权限，**友元函数并不是类的成员函数**
2. 友元关系单向：A 把 B 当作朋友，A 允许 B 访问自己私有；A 不能访问 B 私有
3. 友元不能继承、不能传递
4. 日常固定套路：`<<` 输出重载、`>>` 输入重载几乎都要用 friend

## 简单总结： friend = 好朋友通行证，拿到权限，可以读取类里面的私有成员。
