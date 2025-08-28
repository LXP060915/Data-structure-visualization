#ifndef STACK_H
#define STACK_H

#include <QObject>
#include <QList>
#include "datastructure.h" // 引用 DataStructure 和 NodeVisual 类型

class Stack : public DataStructure {
    Q_OBJECT
public:
    // 修改构造函数，添加容量参数
    explicit Stack(int capacity = 10, QObject *parent = nullptr);
    ~Stack() override;

    // 实现 DataStructure 接口
    void insertHead(int v) override { push(v); }
    void insertTail(int v) override { push(v); }
    void insertAt(int pos, int v) override; 
    void removeAt(int pos) override;        
    QList<NodeVisual> visualNodes() const override;

    // 栈特有操作
    void push(int v);
    void pop();
    int top() const;
    bool isEmpty() const;
    bool isFull() const;  // 添加栈满判断
    int size() const;
    int capacity() const; // 添加容量获取方法
    void clear() override;
    QList<int> values() const;

private:
    QList<int> elements; 
    int m_capacity; // 添加容量成员变量
};

#endif // STACK_H
