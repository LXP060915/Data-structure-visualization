#include "circularqueue.h"

CircularQueue::CircularQueue(int capacity, QObject *parent)
    : DataStructure(parent), cap(capacity), frontIdx(0), rearIdx(0), count(0) {
    arr.resize(cap + 1); // 明确分配n+1个存储位置
}

// 添加nextIndex实现，使用实际数组大小取模
int CircularQueue::nextIndex(int idx) const {
    return (idx + 1) % arr.size();
}

// 修复rear()函数的索引计算
int CircularQueue::rear() const {
    if (isEmpty()) return -1;
    // 使用arr.size()而非cap进行取模
    return arr[(rearIdx - 1 + arr.size()) % arr.size()];
}

CircularQueue::~CircularQueue() {}

bool CircularQueue::isFull() const {
    // 标准循环队列判满条件：(rear+1) % 数组大小 == front
    return (rearIdx + 1) % arr.size() == frontIdx;
}

void CircularQueue::enqueue(int v) {
    if (isFull()) return;
    arr[rearIdx] = v;
    rearIdx = (rearIdx + 1) % arr.size(); // 使用数组大小取模
    count++;
    DataStructure::emitChanged();
}

void CircularQueue::dequeue() {
    if (isEmpty()) return;
    frontIdx = nextIndex(frontIdx); // 仅移动front指针
    count--;
    DataStructure::emitChanged();
}

int CircularQueue::front() const {
    return isEmpty() ? -1 : arr[frontIdx];
}

bool CircularQueue::isEmpty() const { return count == 0; }

// Remove or comment out the old definition:
// bool CircularQueue::isFull() const { return count == cap; }


int CircularQueue::size() const { return count; }

void CircularQueue::clear() {
    frontIdx = 0;
    rearIdx = 0;
    count = 0;
    DataStructure::emitChanged();
}

void CircularQueue::insertAt(int pos, int v) {
    if (isFull() || pos < 0 || pos > count) return;
    if (pos == count) { enqueue(v); return; }
    
    // 修复索引计算 - 将% cap改为% arr.size()
    for (int i = count; i > pos; i--) {
        int idx = (frontIdx + i - 1) % arr.size();
        int prevIdx = (frontIdx + i - 2 + arr.size()) % arr.size();
        arr[idx] = arr[prevIdx];
    }
    arr[(frontIdx + pos) % arr.size()] = v;
    rearIdx = nextIndex(rearIdx);
    count++;
    DataStructure::emitChanged();
}

void CircularQueue::removeAt(int pos) {
    if (isEmpty() || pos < 0 || pos >= count) return;
    if (pos == 0) { dequeue(); return; }
    
    // 修复索引计算 - 将% cap改为% arr.size()
    for (int i = pos; i < count - 1; i++) {
        int idx = (frontIdx + i) % arr.size();
        int nextIdx = (frontIdx + i + 1) % arr.size();
        arr[idx] = arr[nextIdx];
    }
    rearIdx = (rearIdx - 1 + arr.size()) % arr.size();
    count--;
    DataStructure::emitChanged();
}

QList<NodeVisual> CircularQueue::visualNodes() const {
    QList<NodeVisual> nodes;
    // 遍历所有n+1个位置，确保绘图能显示全部
    for (int i = 0; i < arr.size(); i++) {
        bool isActive = false;
        if (!isEmpty()) {
            // 计算当前索引是否在有效元素范围内
            int distance = (i - frontIdx + arr.size()) % arr.size();
            isActive = distance < count;
        }
        nodes.append(NodeVisual(isActive ? arr[i] : -1, nextIndex(i)));
    }
    return nodes;
}

