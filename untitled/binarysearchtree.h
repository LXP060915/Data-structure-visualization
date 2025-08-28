#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "datastructure.h"

class BinarySearchTree : public TreeStructure
{
    Q_OBJECT
public:
    explicit BinarySearchTree(QObject *parent = nullptr);
    ~BinarySearchTree();

    void insertValue(int value) override;
    void removeValue(int value) override;
    bool contains(int value) const override;
    QList<QVector<int>> visualNodes() const override;
    void clear();

private:
    struct Node {
        int value;
        Node *left;
        Node *right;
        
        explicit Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };
    
    Node *root;
    mutable QList<QVector<int>> nodeData;
    
    void insertRecursive(Node *&node, int value);
    bool removeRecursive(Node *&node, int value);
    bool containsRecursive(Node *node, int value) const;
    Node* findMin(Node *node) const;
    void collectNodes(Node *node, QList<QVector<int>> &nodes, int &index, int parentIndex) const;
    void clearRecursive(Node *node);
};

#endif // BINARYSEARCHTREE_H