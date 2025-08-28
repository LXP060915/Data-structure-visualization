#include "linkedlist.h"
#include <QDebug>

LinkedList::LinkedList(QObject *parent): DataStructure(parent), head(nullptr), count(0) {}

LinkedList::~LinkedList() { clear(); }

void LinkedList::clear() {
    Node *p = head;
    while(p) { Node *n=p->next; delete p; p=n; }
    head=nullptr; count=0;
    emitChanged();
}

void LinkedList::insertHead(int v) {
    Node *n = new Node(v);
    n->next = head;
    head = n;
    ++count;
    emitChanged();
}

void LinkedList::insertTail(int v) {
    Node *n = new Node(v);
    if (!head) { head=n; count=1; emitChanged(); return; }
    Node *p=head; while(p->next) p=p->next;
    p->next = n;
    ++count;
    emitChanged();
}

void LinkedList::insertAt(int pos,int v) {
    if (pos<=0) { insertHead(v); return; }
    if (pos>=count) { insertTail(v); return; }
    Node *p=head;
    for(int i=0;i<pos-1 && p;i++) p=p->next;
    if (!p) { insertTail(v); return; }
    Node *n = new Node(v);
    n->next = p->next;
    p->next = n;
    ++count;
    emitChanged();
}

void LinkedList::removeAt(int pos) {
    if (!head || pos<0 || pos>=count) return;
    if (pos==0) {
        Node *n=head; head=head->next; delete n; --count; emitChanged(); return;
    }
    Node *p=head;
    for(int i=0;i<pos-1 && p;i++) p=p->next;
    if (!p || !p->next) return;
    Node *del = p->next;
    p->next = del->next;
    delete del;
    --count;
    emitChanged();
}

QList<NodeVisual> LinkedList::visualNodes() const {
    QList<NodeVisual> out;
    Node *p = head;
    int idx = 0;
    QList<Node*> ptrs;
    while(p) { ptrs.append(p); p=p->next; }
    for (int i=0;i<ptrs.size();++i) {
        int nextIdx = (i+1 < ptrs.size()) ? (i+1) : -1;
        out.append(NodeVisual(ptrs[i]->val, nextIdx));
    }
    return out;
}
