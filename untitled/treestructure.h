#ifndef TREESTRUCTURE_H
#define TREESTRUCTURE_H

#include <QObject>
#include <QList>
#include <QPair>

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
    // Add this signal declaration
    void dataChanged();

};

#endif // TREESTRUCTURE_H