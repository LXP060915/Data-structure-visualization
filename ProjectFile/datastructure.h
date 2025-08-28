#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QVector>

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

// 树结构接口类
class TreeStructure : public QObject
{
    Q_OBJECT
public:
    explicit TreeStructure(QObject *parent = nullptr);
    virtual ~TreeStructure() = default;

    virtual void insertValue(int value) = 0;
    virtual void removeValue(int value) = 0;
    virtual bool contains(int value) const = 0;
    virtual QList<QVector<int>> visualNodes() const = 0;

signals:
    void changed(); // 与DataStructure保持一致的信号名称

protected:
    void emitChanged() { emit changed(); }
};

#endif // DATASTRUCTURE_H