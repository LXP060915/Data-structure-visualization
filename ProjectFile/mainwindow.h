#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>

class LinkedList;
class Stack;
class CircularQueue; // 添加前向声明

namespace Ui {
class MainWindow;  // Qt Designer UI
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // -------------------- 原来的工具栏槽函数 --------------------
    void onNewInstance();
    void onInsertHead();
    void onInsertTail();
    void onDeleteAt();

    // -------------------- 栈相关 --------------------
    void onNewStackInstance();
    void onPush();
    void onPop();

    // -------------------- 链表遍历 --------------------
    void onTraverseLinkedList();

    // -------------------- 循环队列相关 --------------------
    void onNewCircularQueueInstance(); // 循环队列实例创建
    void onNewCustomCapacityQueueInstance(); // 新增自定义容量队列槽函数
    void onEnqueue(); // 入队操作
    void onDequeue(); // 出队操作

    // -------------------- 其他 --------------------
    void onScreenshot();         // 截图
    void onSaveToFile();         // 保存到文件
    void onLoadFromFile();       // 从文件加载
    void onTabCloseRequested(int index);

private:
    Ui::MainWindow *ui;   // Qt Designer UI

    // -------------------- 成员变量 --------------------
    QTabWidget *tabWidget;
    int listCount = 0;    // 链表计数
    int stackCount = 0;   // 栈计数
    int queueCount = 0; // 添加循环队列计数器

    // 工具栏 QAction
    QAction *actNew;
    QAction *actInsertHead;
    QAction *actInsertTail;
    QAction *actDeleteAt;

    // -------------------- 辅助函数 --------------------
    void setupUI();  // 初始化界面

};

#endif // MAINWINDOW_H
