#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct node
{
    int value;
    node* next;
};

//———————————————————————————————————————————————————————————————————— 1.创建链表 尾插法————————————————————————————————————————————————————————————————
node* create(int arr[], int n)
{
    // 哨兵结点，不存有效数据
    node* head = new node{0, nullptr};
    node* tail = head;
    for (int i = 0; i < n; i++)
    {
        node* newNode = new node{arr[i], nullptr};
        tail->next = newNode;
        tail = tail->next;
    }
    return head;
}

// ——————————————————————————————————————————————————————————————————————2.头插：在最前面插入新元素————————————————————————————————————————————————————————————————
void headInsert(node* head, int val)
{
    node* newNode = new node{val, nullptr};
    newNode->next = head->next;
    head->next = newNode;
}

//—————————————————————————————————————————————————————————————————3.尾插————————————————————————————————————————————————————————————————————————
void tailInsert(node* head, int val)
{
    node* cur = head;
    while (cur->next != nullptr)
        cur = cur->next;

    node* newNode = new node{val, nullptr};
    cur->next = newNode;
}

//————————————————————————————————————————————————————————————————4.查找数值，找到返回结点指针，找不到返回nullptr————————————————————————————————————————————————————————————————
node* find(node* head, int target)
{
    node* cur = head->next;
    while (cur != nullptr)
    {
        if (cur->value == target)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

// ————————————————————————————————————————————————————————————————5.删除指定值的后一个结点————————————————————————————————————————————————————————————————
void delVal(node* head, int target)
{
    node* cur = head;
    while (cur->next != nullptr)
    {
        if (cur->next->value == target)
        {
            node* del = cur->next;
            cur->next = del->next;
            delete del;
            return;
        }
        cur = cur->next;
    }
}

//————————————————————————————————————————————————————————————————6.链表反转——————————————————————————————————————————————————————————————————————
node* reverseList(node* head)
{
    // 跳过哨兵，拿到第一个数据结点
    node* pre = nullptr;
    node* cur = head->next;
    while (cur != nullptr)
    {
        node* nextTemp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nextTemp;
    }
    head->next = pre;
    return head;
}

//或用递归算法：
node* reverseRecursion(node* cur)
{
    if(cur == nullptr || cur->next == nullptr)
        return cur;
    node* newHead = reverseRecursion(cur->next);
    cur->next->next = cur;
    cur->next = nullptr;
    return newHead;
}

//调用方式（哨兵链表）
head->next = reverseRecursion(head->next);

// ————————————————————————————————————————————————————————————————7.打印链表————————————————————————————————————————————————————————————————
void print(node* head)
{
    node* cur = head->next;
    while (cur != nullptr)
    {
        cout << cur->value << " ";
        cur = cur->next;
    }
    cout << endl;
}

//———————————————————————————————————————————————————————————————— 8.释放全部内存————————————————————————————————————————————————————————————————
void freeList(node* head)
{
    node* cur = head;
    while (cur != nullptr)
    {
        node* del = cur;
        cur = cur->next;
        delete del;
    }
}

int main()
{
    int arr[] = {1,2,3,4};
    node* head = create(arr,4);
    cout << "初始链表：";
    print(head);

    headInsert(head,99);
    cout << "头插99：";
    print(head);

    tailInsert(head,66);
    cout << "尾插66：";
    print(head);

    delVal(head,3);
    cout << "删掉3：";
    print(head);

    reverseList(head);
    cout << "链表反转：";
    print(head);

    freeList(head);
    return 0;
}
