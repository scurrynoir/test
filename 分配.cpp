// ——————————————————————————————————————————————————————————### 1. malloc——————————————————————————————————————————————————————————

// 作用：申请指定字节堆内存，**内存不会初始化，里面是随机垃圾值**

// //申请可以存放5个int的空间
int *arr = (int*)malloc(5 * sizeof(int));

arr[0] = 10;
arr[1] = 20;

free(arr);      //用完释放
arr = nullptr;

// ——————————————————————————————————————————————————————————### 2. calloc——————————————————————————————————————————————————————————

// 作用：申请内存 + **自动全部清零**
// 参数格式：`calloc(元素个数, 单个元素字节大小)`

int *arr = (int*)calloc(5, sizeof(int));
//所有 arr[0]~arr[4] 默认等于0
free(arr);

// ——————————————————————————————————————————————————————————### 3. realloc —— **C 语言唯一扩容函数**——————————————————————————————————————————————————————————

// 语法：`realloc(旧指针, 新总字节数)`
// 特性：
// 1. 后面有足够空闲内存：直接原地扩容，旧数据保留
// 2. 原地空间不足：在堆上新找一块更大内存，拷贝旧数据，自动释放旧空间
// 3. 传入 nullptr，等价 malloc；大小写 0 等价 free

// #### 扩容实例

#include<iostream>
#include<stdlib.h>
using namespace std;

int main()
{
    //初始容量 3个int
    int* arr = (int*)malloc(3 * sizeof(int));
    for(int i = 0; i < 3; i ++) arr[i] = i+1;

    //扩容至存放6个int
    int* newArr = (int*)realloc(arr,6 * sizeof(int));
    
    //realloc失败返回NULL，旧指针不会自动释放！
    if(newArr == nullptr)
    {
        free(arr);
        return -1;
    }
    arr = newArr;

    arr[3]=4; arr[4]=5; arr[5]=6;
    for(int i=0;i<6;i++) cout<<arr[i]<<" ";

    free(arr);
    arr=nullptr;
    return 0;
}


// > 
// > 重要坑：不要直接 `arr = realloc(arr,size)`；扩容失败返回 null，你会丢失原数组指针，造成内存泄漏

// ——————————————————————————————————————————————————————————### 4. free——————————————————————————————————————————————————————————

// 释放 malloc、calloc、realloc 申请的堆内存
// > 释放之后指针变成野指针，建议手动赋值 nullptr


// ——————————————————————————————————————————————————————————# 二、C++ 动态内存 new /delete（推荐 C++ 使用）——————————————————————————————————————————————————————————

// ## 1. 单个对象申请释放

struct Node{
    int val;
    Node* next;
};

//分配单个结点
Node* p = new Node;
p->val = 10;
p->next = nullptr;

delete p;
p = nullptr;
```

// ——————————————————————————————————————————————————————————## 2. new [] 申请数组、delete [] 释放数组——————————————————————————————————————————————————————————

// 硬性配对：`new[] ↔ delete[]`，不可混用普通 delete

```
int* arr = new int[5]{1,2,3,4,5};

delete[] arr;
arr = nullptr;
```

// ——————————————————————————————————————————————————————————## 3.C++ 没有内置扩容函数，数组扩容手动实现——————————————————————————————————————————————————————————

// 步骤：
// 1. 创建更大容量新数组
// 2. 拷贝旧数组全部元素
// 3. 释放旧数组
// 4. 指针指向新数组

#include<iostream>
using namespace std;

int main()
{
    int size = 3;
    int* arr = new int[size]{1,2,3};

    //扩容到6
    int newSize = 6;
    int* newArr = new int[newSize];

    //拷贝数据
    for(int i=0;i<size;i++)
        newArr[i] = arr[i];

    delete[] arr;   //释放旧数组
    arr = newArr;   //指针转移

    arr[3]=4; arr[4]=5; arr[5]=6;

    for(int i=0;i<newSize;i++)
        cout<<arr[i]<<" ";

    delete[] arr;
    return 0;
}


// ——————————————————————————————————————————————————————————## 4. C++ STL vector（最省心自动扩容）——————————————————————————————————————————————————————————

// vector 底层堆数组，**超出容量自动扩容**，程序员不用手动操作内存
// 扩容机制：一般旧容量满了之后，新容量 = 旧容量 * 2，拷贝元素、销毁旧内存

#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> vec;
    for(int i=1;i<=5;i++)
    {
        vec.push_back(i);
        cout<<"容量:"<<vec.capacity()<<" 大小:"<<vec.size()<<endl;
    }
    return 0;
}
// 另一个例子
std::vector<double>arr={1,2,3};
arr.push_back(1000);
for (auto num:arr){    
    cout<<num<<" ";
}
//**auto = 右边初始化值是什么类型，变量就是什么类型(必须初始化，`auto a;` 报错，编译器没有依据推类型。)

for(const auto& num : vec)  //const auto& 常量引用，只读、不拷贝（最推荐遍历容器）
{
    cout << num;
}
return 0;
