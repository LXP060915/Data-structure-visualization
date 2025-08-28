#include "circularqueue.h"

CircularQueue::CircularQueue(int capacity, QObject *parent)
    : DataStructure(parent), cap(capacity), frontIdx(0), rearIdx(0), count(0)
{
    arr.resize(cap);
}

CircularQueue::~CircularQueue() {}

void CircularQueue::enqueue(int v) {
    if (isFull()) return;
    arr[rearIdx] = v;
    rearIdx = nextIndex(rearIdx);
    count++;
    DataStructure::emitChanged();
}

void CircularQueue::dequeue() {
    if (isEmpty()) return;
    frontIdx = nextIndex(frontIdx);
    count--;
    DataStructure::emitChanged();
}

int CircularQueue::front() const {
    return isEmpty() ? -1 : arr[frontIdx];
}

int CircularQueue::rear() const {
    return isEmpty() ? -1 : arr[(rearIdx - 1 + cap) % cap];
}

bool CircularQueue::isEmpty() const { return count == 0; }

bool CircularQueue::isFull() const { return count == cap; }

int CircularQueue::size() const { return count; }

void CircularQueue::clear() {
    frontIdx = 0;
    rearIdx = 0;
    count = 0;
    DataStructure::emitChanged();
}

void CircularQueue::insertAt(int pos, int v) {
    if (isFull() || pos < 0 || pos > count) return;
    // 插入到指定位置（模拟队列中间插入，实际队列通常只在队尾插入）
    if (pos == count) { enqueue(v); return; }
    
    // 移动元素腾出位置
    for (int i = count; i > pos; i--) {
        int idx = (frontIdx + i - 1) % cap;
        int prevIdx = (frontIdx + i - 2 + cap) % cap;
        arr[idx] = arr[prevIdx];
    }
    arr[(frontIdx + pos) % cap] = v;
    rearIdx = nextIndex(rearIdx);
    count++;
    DataStructure::emitChanged();
}

void CircularQueue::removeAt(int pos) {
    if (isEmpty() || pos < 0 || pos >= count) return;
    if (pos == 0) { dequeue(); return; }
    
    // 移动元素覆盖被删除位置
    for (int i = pos; i < count - 1; i++) {
        int idx = (frontIdx + i) % cap;
        int nextIdx = (frontIdx + i + 1) % cap;
        arr[idx] = arr[nextIdx];
    }
    rearIdx = (rearIdx - 1 + cap) % cap;
    count--;
    DataStructure::emitChanged();
}

QList<NodeVisual> CircularQueue::visualNodes() const {
    QList<NodeVisual> nodes;
    if (isEmpty()) return nodes;

    // 确保所有节点形成闭环
    for (int i = 0; i < cap; i++) {
        int actualIdx = (frontIdx + i) % cap;
        bool isActive = i < count;
        // 每个节点的next都是下一个有效索引，形成完整闭环
        nodes.append(NodeVisual(isActive ? arr[actualIdx] : -1, (i + 1) % cap));
    }
    return nodes;
}