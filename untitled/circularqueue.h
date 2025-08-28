#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <QObject>
#include <QVector>
#include "datastructure.h"

class CircularQueue : public DataStructure {
    Q_OBJECT
public:
    explicit CircularQueue(int capacity = 5, QObject *parent = nullptr);
    ~CircularQueue() override;

    // 实现DataStructure接口
    void insertHead(int v) override { enqueue(v); }
    void insertTail(int v) override { enqueue(v); }
    void insertAt(int pos, int v) override;
    void removeAt(int pos) override;
    QList<NodeVisual> visualNodes() const override;
    void clear() override;

    // 循环队列特有操作
    void enqueue(int v);
    void dequeue();
    int front() const;
    int rear() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int capacity() const { return arr.size(); }

private:
    QVector<int> arr;      // 存储队列元素
    int frontIdx;          // 队头索引
    int rearIdx;           // 队尾索引
    int count;             // 当前元素数量
    int cap;               // 队列容量

    // 计算下一个索引（循环逻辑）
    int nextIndex(int idx) const { return (idx + 1) % cap; }

public:
    // 添加获取索引的接口（仅用于可视化）
    int frontIndex() const { return frontIdx; }
    int rearIndex() const { return rearIdx; }
};

#endif // CIRCULARQUEUE_H