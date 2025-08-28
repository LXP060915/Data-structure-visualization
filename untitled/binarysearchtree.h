#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "treestructure.h"
#include <QVector>
#include <QList>

class BinarySearchTree : public TreeStructure
{
    Q_OBJECT
public:
    explicit BinarySearchTree(QObject *parent = nullptr);

    void insertValue(int value) override;
    void removeValue(int value) override;
    bool contains(int value) const override;
    QList<QVector<int>> visualNodes() const override;

private:
    struct Node {
        int value;
        Node *left;
        Node *right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node *root;
    mutable QList<QVector<int>> nodeData;

    void insertRecursive(Node *&node, int value);
    bool removeRecursive(Node *&node, int value);
    Node *findMin(Node *node) const;
    void collectNodes(Node *node, int parentIndex, int &currentIndex) const;
};

#endif // BINARYSEARCHTREE_H