#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QObject>
#include "datastructure.h"

class LinkedList : public DataStructure {
    Q_OBJECT
public:
    explicit LinkedList(QObject *parent = nullptr);
    ~LinkedList() override;

    void insertHead(int v) override;
    void insertTail(int v) override;
    void insertAt(int pos,int v) override;
    void removeAt(int pos) override;
    QList<NodeVisual> visualNodes() const override;

    // ✅ 把 clear 改为 public
    void clear() override;

private:
    struct Node { int val; Node* next; Node(int v):val(v),next(nullptr){} };
    Node* head;
    int count;

    void buildVisualList(QList<NodeVisual> &out) const;

};

#endif // LINKEDLIST_H
