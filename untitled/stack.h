#ifndef STACK_H
#define STACK_H

#include <QObject>
#include <QList>
#include "datastructure.h" // 引用 DataStructure 和 NodeVisual 类型

class Stack : public DataStructure {
    Q_OBJECT
public:
    explicit Stack(QObject *parent = nullptr);
    ~Stack() override;

    // 实现 DataStructure 接口
    void insertHead(int v) override { push(v); }
    void insertTail(int v) override { push(v); }
    void insertAt(int pos, int v) override; // 可以忽略或实现特定逻辑
    void removeAt(int pos) override;        // 可以忽略或实现特定逻辑
    QList<NodeVisual> visualNodes() const override;

    // 栈特有操作
    void push(int v);
    void pop();
    int top() const;
    bool isEmpty() const;
    int size() const;
    void clear() override;      // 清空栈（实现基类纯虚函数）
    QList<int> values() const;  // 返回所有元素

private:
    QList<int> elements; // 存储栈元素
};

#endif // STACK_H
