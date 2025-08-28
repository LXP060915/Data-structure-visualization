#include "stack.h"

// Remove the default constructor without capacity parameter
// Stack::Stack(QObject *parent) : DataStructure(parent) {}

// Keep only the constructor with capacity parameter
Stack::Stack(int capacity, QObject *parent) : DataStructure(parent), m_capacity(capacity) {}
Stack::~Stack() {}

// DataStructure 接口实现（每个只定义一次）


void Stack::insertAt(int, int v) { push(v); }
void Stack::removeAt(int) { if (!isEmpty()) pop(); }

// 栈特有操作
void Stack::push(int v) {
    if (!isFull()) { // 添加栈满判断
        elements.append(v);
        DataStructure::emitChanged();
    }
}

void Stack::pop() { if (!isEmpty()) { elements.removeLast(); DataStructure::emitChanged(); } }
int Stack::top() const { return isEmpty() ? 0 : elements.last(); }
bool Stack::isEmpty() const { return elements.isEmpty(); }

// 添加容量检查和获取方法
bool Stack::isFull() const {
    return elements.size() >= m_capacity;
}

int Stack::capacity() const {
    return m_capacity;
}

int Stack::size() const { return elements.size(); }

// 可视化节点
QList<NodeVisual> Stack::visualNodes() const {
    QList<NodeVisual> out;
    int n = elements.size();
    for (int i = 0; i < n; ++i) {
        int nextIndex = (i == n - 1) ? -1 : i + 1;
        out.append(NodeVisual(elements[i], nextIndex));
    }
    return out;
}

// 新增方法
void Stack::clear() { elements.clear(); DataStructure::emitChanged(); }
QList<int> Stack::values() const { return elements; }
