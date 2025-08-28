#include "binarysearchtree.h"

BinarySearchTree::BinarySearchTree(QObject *parent) : TreeStructure(parent), root(nullptr)
{
}

void BinarySearchTree::insertValue(int value)
{
    insertRecursive(root, value);
    emit dataChanged();
}

void BinarySearchTree::removeValue(int value)
{
    if (removeRecursive(root, value)) {
        emit dataChanged();
    }
}

bool BinarySearchTree::contains(int value) const
{
    Node *current = root;
    while (current) {
        if (current->value == value) return true;
        if (value < current->value) current = current->left;
        else current = current->right;
    }
    return false;
}

QList<QVector<int>> BinarySearchTree::visualNodes() const
{
    nodeData.clear();
    int currentIndex = 0;
    collectNodes(root, -1, currentIndex);
    return nodeData;
}

void BinarySearchTree::insertRecursive(Node *&node, int value)
{
    if (!node) {
        node = new Node(value);
        return;
    }
    if (value < node->value) insertRecursive(node->left, value);
    else insertRecursive(node->right, value);
}

bool BinarySearchTree::removeRecursive(Node *&node, int value)
{
    if (!node) return false;
    if (value < node->value) return removeRecursive(node->left, value);
    if (value > node->value) return removeRecursive(node->right, value);

    // 找到要删除的节点
    if (!node->left && !node->right) { // 叶子节点
        delete node;
        node = nullptr;
    } else if (!node->left || !node->right) { // 一个子节点
        Node *temp = node;
        node = node->left ? node->left : node->right;
        delete temp;
    } else { // 两个子节点
        Node *temp = findMin(node->right);
        node->value = temp->value;
        removeRecursive(node->right, temp->value);
    }
    return true;
}

BinarySearchTree::Node *BinarySearchTree::findMin(Node *node) const
{
    while (node->left) node = node->left;
    return node;
}

void BinarySearchTree::collectNodes(Node *node, int parentIndex, int &currentIndex) const
{
    if (!node) return;
    int currentNodeIndex = currentIndex++;
    // 存储节点数据: [值, 父节点索引, 左子节点索引, 右子节点索引]
    QVector<int> nodeInfo = {node->value, parentIndex, -1, -1};
    nodeData.append(nodeInfo);

    // 递归处理左右子树
    if (node->left) {
        nodeData[currentNodeIndex][2] = currentIndex; // 更新左子节点索引
        collectNodes(node->left, currentNodeIndex, currentIndex);
    }
    if (node->right) {
        nodeData[currentNodeIndex][3] = currentIndex; // 更新右子节点索引
        collectNodes(node->right, currentNodeIndex, currentIndex);
    }
}