#include "binarysearchtree.h"
#include "datastructure.h"

BinarySearchTree::BinarySearchTree(QObject *parent) : TreeStructure(parent), root(nullptr)
{
}

BinarySearchTree::~BinarySearchTree()
{
    clear();
}

void BinarySearchTree::insertValue(int value)
{
    insertRecursive(root, value);
    emit changed();
}

void BinarySearchTree::removeValue(int value)
{
    if (removeRecursive(root, value)) {
        emit changed();
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
    collectNodes(root, nodeData, currentIndex, -1);
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

void BinarySearchTree::collectNodes(Node *node, QList<QVector<int>> &nodes, int &index, int parentIndex) const
{
    if (!node) return;
    int currentNodeIndex = index++;
    // 存储节点数据: [值, 父节点索引, 左子节点索引, 右子节点索引]
    QVector<int> nodeInfo = {node->value, parentIndex, -1, -1};
    nodes.append(nodeInfo);

    // 递归处理左右子树
    if (node->left) {
        nodes[currentNodeIndex][2] = index; // 更新左子节点索引
        collectNodes(node->left, nodes, index, currentNodeIndex);
    }
    if (node->right) {
        nodes[currentNodeIndex][3] = index; // 更新右子节点索引
        collectNodes(node->right, nodes, index, currentNodeIndex);
    }
}

void BinarySearchTree::clear()
{
    clearRecursive(root);
    root = nullptr;
    emit changed();
}

void BinarySearchTree::clearRecursive(Node *node)
{
    if (node) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}