#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QObject>
#include <QList>
#include <QPair>

// 可视化节点：first = 值, second = 下一个节点索引 (-1 表示 null)
typedef QPair<int, int> NodeVisual;

class DataStructure : public QObject {
    Q_OBJECT
public:
    explicit DataStructure(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~DataStructure() {}

    // 纯虚函数 - 数据操作接口
    virtual void insertHead(int v) = 0;
    virtual void insertTail(int v) = 0;
    virtual void insertAt(int pos, int v) = 0;
    virtual void removeAt(int pos) = 0;
    virtual QList<NodeVisual> visualNodes() const = 0;
    virtual void clear() = 0;

signals:
    void changed(); // 数据变化信号

protected:
    void emitChanged() { emit changed(); }
};

#endif // DATASTRUCTURE_H