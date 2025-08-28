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
    // 修改容量接口：返回用户指定的容量n，而非数组大小
    int capacity() const { return cap; }
    // 添加获取实际存储大小接口（n+1）
    int bufferSize() const { return arr.size(); }

private:
    QVector<int> arr;      // 存储队列元素（大小为cap+1）
    int frontIdx;          // 队头索引
    int rearIdx;           // 队尾索引
    int count;             // 当前元素数量
    int cap;               // 用户指定的容量n

    // 添加nextIndex函数声明
    int nextIndex(int idx) const;

public:
    // 添加获取索引的接口（仅用于可视化）
    int frontIndex() const { return frontIdx; }
    int rearIndex() const { return rearIdx; }
};

#endif // CIRCULARQUEUE_H