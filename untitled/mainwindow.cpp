#include "mainwindow.h"
#include "canvas.h"
#include "linkedlist.h"
#include "stack.h"
#include "circularqueue.h"

#include <QInputDialog>
#include <QVBoxLayout>
#include <QWidget>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();

    // 菜单栏
    QMenuBar *menuBar = this->menuBar();
    QMenu *menuDS = menuBar->addMenu("数据结构");
    QMenu *menuOp = menuBar->addMenu("操作");
    QMenu *menuFile = menuBar->addMenu("文件");

    //文件菜单
    QAction *actionScreenshot = menuFile->addAction("截图");
    QAction *actionLoad = menuFile->addAction("从文件加载");
    QAction *actionSave = menuFile->addAction("保存到文件");
    actionSave->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionScreenshot, &QAction::triggered, this, &MainWindow::onScreenshot);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::onLoadFromFile);
    connect(actionSave, &QAction::triggered, this, &MainWindow::onSaveToFile);

    // 数据结构菜单
    QAction *actionNewList = menuDS->addAction("链表");
    QAction *actionNewStack = menuDS->addAction("栈");
    QAction *actionNewQueue = menuDS->addAction("循环队列"); // 添加队列菜单
    QAction *actNewCustomQueue = menuDS->addAction("自定义容量循环队列");

    // 操作菜单
    QAction *actionInsertHead = menuOp->addAction("链表：头插");
    QAction *actionInsertTail = menuOp->addAction("链表：尾插");
    QAction *actionDeleteAt = menuOp->addAction("链表：删除");
    QAction *actionTraverse = menuOp->addAction("链表：遍历");
    QAction *actionPush = menuOp->addAction("栈：Push");
    QAction *actionPop = menuOp->addAction("栈：Pop");
    QAction *actEnqueue = menuOp->addAction("入队");
    QAction *actDequeue = menuOp->addAction("出队");

    // 绑定槽函数
    connect(actionNewList, &QAction::triggered, this, &MainWindow::onNewInstance);
    connect(actionNewStack, &QAction::triggered, this, &MainWindow::onNewStackInstance);
    connect(actionInsertHead, &QAction::triggered, this, &MainWindow::onInsertHead);
    connect(actionInsertTail, &QAction::triggered, this, &MainWindow::onInsertTail);
    connect(actionDeleteAt, &QAction::triggered, this, &MainWindow::onDeleteAt);
    connect(actionTraverse, &QAction::triggered, this, &MainWindow::onTraverseLinkedList);
    connect(actionPush, &QAction::triggered, this, &MainWindow::onPush);
    connect(actionPop, &QAction::triggered, this, &MainWindow::onPop);
    connect(actEnqueue, &QAction::triggered, this, &MainWindow::onEnqueue);
    connect(actDequeue, &QAction::triggered, this, &MainWindow::onDequeue);

    // 创建默认链表实例
    onNewInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName("tabWidget");
    tabWidget->setTabsClosable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabCloseRequested);
    setCentralWidget(tabWidget);

    QToolBar *tb = addToolBar("操作");
    actNew = tb->addAction("新建链表实例");
    QAction *actNewStack = tb->addAction("新建栈实例");
    QAction *actNewQueue = tb->addAction("新建队列实例");

    QAction *actNewCustomQueue = tb->addAction("新建自定义容量队列"); // 添加自定义容量按钮

    actInsertHead = tb->addAction("头插");
    actInsertTail = tb->addAction("尾插");
    actDeleteAt = tb->addAction("删除(指定位置)");
    QAction *actTraverse = tb->addAction("遍历链表");

    QAction *actPush = tb->addAction("Push(入栈)");
    QAction *actPop = tb->addAction("Pop(出栈)");

    QAction *actEnqueue = tb->addAction("入队操作");
    QAction *actDequeue = tb->addAction("出队操作");

    QAction *actScreenshot = tb->addAction("截图");
    QAction *actSave = tb->addAction("保存到文件");
    QAction *actLoad = tb->addAction("从文件加载");





    connect(actNew, &QAction::triggered, this, &MainWindow::onNewInstance);
    connect(actNewStack, &QAction::triggered, this, &MainWindow::onNewStackInstance);
    connect(actInsertHead, &QAction::triggered, this, &MainWindow::onInsertHead);
    connect(actInsertTail, &QAction::triggered, this, &MainWindow::onInsertTail);
    connect(actDeleteAt, &QAction::triggered, this, &MainWindow::onDeleteAt);
    connect(actTraverse, &QAction::triggered, this, &MainWindow::onTraverseLinkedList);
    connect(actPush, &QAction::triggered, this, &MainWindow::onPush);
    connect(actPop, &QAction::triggered, this, &MainWindow::onPop);
    connect(actScreenshot, &QAction::triggered, this, &MainWindow::onScreenshot);
    connect(actSave, &QAction::triggered, this, &MainWindow::onSaveToFile);
    connect(actLoad, &QAction::triggered, this, &MainWindow::onLoadFromFile);
    connect(actNewQueue, &QAction::triggered, this, &MainWindow::onNewCircularQueueInstance);
    connect(actEnqueue, &QAction::triggered, this, &MainWindow::onEnqueue);
    connect(actDequeue, &QAction::triggered, this, &MainWindow::onDequeue);
    connect(actNewCustomQueue, &QAction::triggered, this, &MainWindow::onNewCustomCapacityQueueInstance);
}

static DataStructure* currentDataStructureFromTab(QTabWidget *tabs) {
    QWidget *w = tabs->currentWidget();
    if (!w) return nullptr;
    CanvasWidget *c = qobject_cast<CanvasWidget*>(w);
    if (!c) return nullptr;
    return c->dataStructure();
}

static LinkedList* currentListFromTab(QTabWidget *tabs) {
    QWidget *w = tabs->currentWidget();
    if (!w) return nullptr;
    CanvasWidget *c = qobject_cast<CanvasWidget*>(w);
    if (!c) return nullptr;
    return qobject_cast<LinkedList*>(c->dataStructure());
}

void MainWindow::onNewInstance()
{
    // First create canvas with temporary null data structure
    CanvasWidget *canvas = new CanvasWidget(nullptr);
    // Then create linked list with canvas as parent
    LinkedList *list = new LinkedList(canvas);
    // Set the data structure for the canvas
    canvas->setDataStructure(list);
    int idx = tabWidget->addTab(canvas, QString("链表_%1").arg(++listCount));
    tabWidget->setCurrentIndex(idx);
}

void MainWindow::onNewStackInstance()
{
    // First create canvas with temporary null data structure
    CanvasWidget *canvas = new CanvasWidget(nullptr);
    // Then create stack with canvas as parent
    Stack *stack = new Stack(canvas);
    // Set the data structure for the canvas
    canvas->setDataStructure(stack);
    int idx = tabWidget->addTab(canvas, QString("栈_%1").arg(++stackCount));
    tabWidget->setCurrentIndex(idx);
}

void MainWindow::onInsertHead()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    LinkedList *list = qobject_cast<LinkedList*>(ds);
    if (!list) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是链表!");
        return;
    }

    bool ok = false;
    int v = QInputDialog::getInt(this, "头插", "值:", 0, -2147483647, 2147483647, 1, &ok);
    if (ok) {
        list->insertHead(v);
        CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
        if (canvas) canvas->update();
    }
}

void MainWindow::onInsertTail()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    LinkedList *list = qobject_cast<LinkedList*>(ds);
    if (!list) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是链表!");
        return;
    }

    bool ok = false;
    int v = QInputDialog::getInt(this, "尾插", "值:", 0, -2147483647, 2147483647, 1, &ok);
    if (ok) {
        list->insertTail(v);
        CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
        if (canvas) canvas->update();
    }
}

void MainWindow::onDeleteAt()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    LinkedList *list = qobject_cast<LinkedList*>(ds);
    if (!list) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是链表!");
        return;
    }

    bool ok = false;
    int pos = QInputDialog::getInt(this, "删除位置", "位置(0-based):", 0, 0, 1000, 1, &ok);
    if (ok) {
        list->removeAt(pos);
        CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
        if (canvas) canvas->update();
    }
}

void MainWindow::onPush()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    Stack *stack = qobject_cast<Stack*>(ds);
    if (!stack) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是栈!");
        return;
    }

    bool ok = false;
    int v = QInputDialog::getInt(this, "Push", "值:", 0, -2147483647, 2147483647, 1, &ok);
    if (ok) {
        stack->push(v);
        CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
        if (canvas) canvas->update();
    }
}

void MainWindow::onPop()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    Stack *stack = qobject_cast<Stack*>(ds);
    if (!stack) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是栈!");
        return;
    }

    if (stack->isEmpty()) {
        QMessageBox::warning(this, "操作失败", "栈为空，无法Pop!");
        return;
    }
    stack->pop();
    CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
    if (canvas) canvas->update();
}

void MainWindow::onTraverseLinkedList()
{
    LinkedList *list = currentListFromTab(tabWidget);
    if (!list) return;

    QList<NodeVisual> nodes = list->visualNodes();
    QString result = "链表遍历结果:\n";
    for (int i = 0; i < nodes.size(); ++i) {
        result += QString("节点 %1: %2\n").arg(i).arg(nodes[i].first);
    }
    result += "遍历完成\n";

    QMessageBox::information(this, "链表遍历", result);
}

// ==================== 截图功能 ====================
void MainWindow::onScreenshot()
{
    QWidget *w = tabWidget->currentWidget();
    if (!w) return;

    QPixmap pixmap = w->grab();
    QString defaultPath = QFileDialog::getSaveFileName(this, "保存截图",
        QDir::homePath() + "/screenshot_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".png",
        "PNG Files (*.png)");

    if (!defaultPath.isEmpty()) {
        if (!pixmap.save(defaultPath)) {
            QMessageBox::warning(this, "错误", "截图保存失败！");
        }
    }
}

void MainWindow::onSaveToFile()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    QString filePath = QFileDialog::getSaveFileName(this, "保存文件",
        QDir::homePath() + "/data.dsf", "DSF 文件 (*.dsf)");

    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件保存！");
        return;
    }

    QTextStream out(&file);

    QList<int> values;

    if (LinkedList *list = qobject_cast<LinkedList*>(ds)) {
        QList<NodeVisual> nodes = list->visualNodes();
        for (const NodeVisual &node : nodes)
            values.append(node.first);
    } else if (Stack *stack = qobject_cast<Stack*>(ds)) {
        values = stack->values();
    }

    for (int v : values)
        out << v << "\n";

    file.close();
    QMessageBox::information(this, "保存", "保存成功！");
}

void MainWindow::onLoadFromFile()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    QString filePath = QFileDialog::getOpenFileName(this, "加载文件", QDir::homePath(), "DSF 文件 (*.dsf)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件加载！");
        return;
    }

    QTextStream in(&file);
    QList<int> values;
    while (!in.atEnd()) {
        QString line = in.readLine();
        bool ok;
        int v = line.toInt(&ok);
        if (ok) values.append(v);
    }
    file.close();

    if (LinkedList *list = qobject_cast<LinkedList*>(ds)) {
        list->clear();
        for (int v : values)
            list->insertTail(v);
    } else if (Stack *stack = qobject_cast<Stack*>(ds)) {
        stack->clear();
        for (int v : values)
            stack->push(v);
    }

    CanvasWidget *canvas = qobject_cast<CanvasWidget*>(tabWidget->currentWidget());
    if (canvas) canvas->update();

    QMessageBox::information(this, "加载", "加载完成！");
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        int currentIndex = tabWidget->currentIndex();
        onTabCloseRequested(currentIndex);
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::onTabCloseRequested(int index)
{
    QWidget* widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget; // 清理画布和数据结构
}

// 循环队列实例创建
void MainWindow::onNewCircularQueueInstance()
{
    CanvasWidget *canvas = new CanvasWidget(nullptr);
    CircularQueue *queue = new CircularQueue(5, canvas); // 容量为5的循环队列
    canvas->setDataStructure(queue);
    int idx = tabWidget->addTab(canvas, QString("循环队列_%1").arg(++queueCount));
    tabWidget->setCurrentIndex(idx);
}

// 入队操作
void MainWindow::onEnqueue()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    CircularQueue *queue = qobject_cast<CircularQueue*>(ds);
    if (!queue) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是循环队列!");
        return;
    }

    bool ok;
    int value = QInputDialog::getInt(this, "入队操作", "请输入入队值:", 0, -2147483647, 2147483647, 1, &ok);
    if (ok) {
        if (queue->isFull()) {
            QMessageBox::warning(this, "操作失败", "队列已满，无法入队!");
            return;
        }
        queue->enqueue(value);
    }
}

// 出队操作
void MainWindow::onDequeue()
{
    DataStructure *ds = currentDataStructureFromTab(tabWidget);
    if (!ds) return;

    CircularQueue *queue = qobject_cast<CircularQueue*>(ds);
    if (!queue) {
        QMessageBox::warning(this, "操作失败", "当前选中的不是循环队列!");
        return;
    }

    if (queue->isEmpty()) {
        QMessageBox::warning(this, "操作失败", "队列为空，无法出队!");
        return;
    }

    queue->dequeue();
}

// 实现自定义容量队列创建函数
void MainWindow::onNewCustomCapacityQueueInstance()
{
    bool ok;
    int capacity = QInputDialog::getInt(this, "设置队列容量", 
                                        "请输入循环队列容量(1-100):", 
                                        5, 1, 100, 1, &ok);
    if (!ok) return; // 用户取消输入

    CanvasWidget *canvas = new CanvasWidget(nullptr);
    // 创建指定容量的循环队列
    CircularQueue *queue = new CircularQueue(capacity, canvas); 
    canvas->setDataStructure(queue);
    int idx = tabWidget->addTab(canvas, QString("循环队列_%1(容量%2)").arg(++queueCount).arg(capacity));
    tabWidget->setCurrentIndex(idx);
}
