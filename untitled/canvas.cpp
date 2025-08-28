#include "canvas.h"
#include "stack.h"  // Add this include for Stack class
#include "linkedlist.h"  // Add this include for LinkedList class
#include "circularqueue.h"
#include <QPainter>
#include <QPaintEvent>
#include <cmath>

CanvasWidget::CanvasWidget(DataStructure *ds_, QWidget *parent)
    : QWidget(parent), ds(ds_)
{
    setAutoFillBackground(true);
    setMinimumSize(400,200);
    if (ds) connect(ds, &DataStructure::changed, this, &CanvasWidget::onDataChanged);
}

void CanvasWidget::onDataChanged() {
    update();
}

void CanvasWidget::paintEvent(QPaintEvent * /*event*/) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), palette().window());

    if (!ds) return;

    // 直接使用基类定义的 NodeVisual 类型
    QList<NodeVisual> nodes = ds->visualNodes();

    int n = nodes.size();
    if (n == 0) {
        // 根据数据结构类型显示不同的空状态文本
        if (dynamic_cast<Stack*>(ds)) {
            p.drawText(rect(), Qt::AlignCenter, "栈空");
        } else {
            p.drawText(rect(), Qt::AlignCenter, "空");
        }
        return;
    }

    bool isStack = dynamic_cast<Stack*>(ds) != nullptr;
    bool isLinkedList = dynamic_cast<LinkedList*>(ds) != nullptr;
    bool isCircularQueue = dynamic_cast<CircularQueue*>(ds) != nullptr;
    // 修复断言逻辑，允许三种类型之一
    Q_ASSERT_X(isStack || isLinkedList || isCircularQueue, "CanvasWidget", "Unsupported data structure type");

    if (isStack) {
        // ================= 栈 =================
        int w = width(), h = height();
        int nodeW = 80, nodeH = 50;
        int gap = 10;
        int totalHeight = n * nodeH + (n - 1) * gap;
        int x = w / 2 - nodeW / 2;
        int y = h / 2 - totalHeight / 2;

        // 添加容量显示
        Stack* stack = dynamic_cast<Stack*>(ds);
        QString capacityText = QString("容量: %1/%2").arg(n).arg(stack->capacity());
        QRect capacityRect(x, y - 55, nodeW, 25);
        p.drawText(capacityRect, Qt::AlignCenter, capacityText);

        QRect topLabelRect(x, y - 30, nodeW, 25);
        p.drawText(topLabelRect, Qt::AlignCenter, "栈顶");

        QRect bottomLabelRect(x, y + totalHeight + 5, nodeW, 25);
        p.drawText(bottomLabelRect, Qt::AlignCenter, "栈底");

        for (int i = 0; i < nodes.size(); ++i) {
            QRect r(x, y + (n - 1 - i) * (nodeH + gap), nodeW, nodeH);

            // 栈满时所有节点变橙色，否则栈顶(最后一个元素)红色、其他节点灰色
            QColor fillColor;
            if (stack->isFull()) {
                fillColor = QColor(255, 165, 0); // 橙色
            } else {
                // i == nodes.size() - 1 表示最后一个元素(栈顶)
                fillColor = (i == nodes.size() - 1) ? QColor(255, 0, 0) : QColor(240, 240, 240);
            }
            p.fillRect(r, fillColor);

            p.drawRoundedRect(r, 8, 8);
            QString txt = QString::number(nodes[i].first);
            p.drawText(r, Qt::AlignCenter, txt);
        }
    } else if(isLinkedList){
        // ================= 链表 =================
        int w = width(), h = height();
        int nodeW = 60, nodeH = 40;
        int gap = qMax(20, (w - n*nodeW) / (n+2));
        int x = gap;
        int y = h/2 - nodeH/2;

        for (int i=0;i<n;i++) {
            QRect r(x,y,nodeW,nodeH);

            // 设置节点颜色
            QColor fillColor;
            if (i == currentHighlightIndex) {
                fillColor = QColor(255,255,153); // 遍历高亮（黄色）
            } else if (i == selectedNodeIndex) {
                fillColor = QColor(255,0,0);     // 鼠标选中（红色）
            } else {
                fillColor = QColor(240,240,240); // 默认（灰色）
            }
            p.fillRect(r, fillColor);

            p.drawRoundedRect(r,8,8);
            QString txt = QString::number(nodes[i].first);
            p.drawText(r, Qt::AlignCenter, txt);

            // 添加节点索引标签
            QString indexText = QString::number(i + 1); // 1-based索引
            QRect indexRect(x, y + nodeH + 5, nodeW, 20); // 位于节点下方5像素处
            p.drawText(indexRect, Qt::AlignCenter, indexText);

            if (nodes[i].second != -1) {
                int x1 = x + nodeW;
                int y1 = y + nodeH/2;
                int x2 = x + nodeW + gap - 10;
                int y2 = y + nodeH/2;
                p.drawLine(x1, y1, x2, y2);
                p.drawLine(x2-6, y2-6, x2, y2);
                p.drawLine(x2-6, y2+6, x2, y2);
            }

            if (i == n-1) {
                int arrowStartX = x + nodeW;
                int arrowStartY = y + nodeH/2;

                int nullBoxX = x + nodeW + gap;
                int nullBoxY = y;
                QRect nullRect(nullBoxX, nullBoxY, 60, nodeH);

                int arrowEndX = nullBoxX;
                int arrowEndY = y + nodeH/2;
                p.drawLine(arrowStartX, arrowStartY, arrowEndX, arrowEndY);
                p.drawLine(arrowEndX-6, arrowEndY-6, arrowEndX, arrowEndY);
                p.drawLine(arrowEndX-6, arrowEndY+6, arrowEndX, arrowEndY);

                QBrush oldBrush = p.brush();
                QPen oldPen = p.pen();

                p.setBrush(QColor(220,220,220));
                QPen dashPen(Qt::black);
                dashPen.setStyle(Qt::DashLine);
                p.setPen(dashPen);

                p.drawRoundedRect(nullRect, 8, 8);
                p.drawText(nullRect, Qt::AlignCenter, "NULL");

                p.setBrush(oldBrush);
                p.setPen(oldPen);
            }

            x += nodeW + gap;
        }
    } else if (isCircularQueue) {
        // ================= 循环队列（修正版）=================
        int w = width(), h = height();
        int nodeW = 60, nodeH = 40;
        CircularQueue* queue = dynamic_cast<CircularQueue*>(ds);
        if (!queue) return;

        // 核心修改：节点数 = 容量 + 1
        int capacity = queue->capacity();
        int n = capacity + 1;  // 节点数量 = 容量 + 1
        int frontIdx = queue->frontIndex();
        int rearIdx = queue->rearIndex();
        bool isFull = queue->isFull();
        bool isEmpty = queue->isEmpty();

        // 获取实际节点数据（可能少于容量+1个有效元素）
        QList<NodeVisual> nodes = ds->visualNodes();
        // 确保节点列表有足够元素（容量+1）
        while (nodes.size() < n) {
            nodes.append(NodeVisual(-1, -1));
        }

        // 计算圆心和半径（圆形布局）
        QPoint center(w/2, h/2);
        int radius = qMin(w, h) / 3;

        // 存储所有节点位置
        QVector<QPoint> nodePositions;
        QVector<QRect> nodeRects;

        // 绘制所有节点（0到capacity，共capacity+1个）
        for (int i = 0; i < n; ++i) {
            // 极坐标计算节点位置（圆形布局）
            double angle = 2 * M_PI * i / n - M_PI/2;
            int x = center.x() + radius * cos(angle) - nodeW/2;
            int y = center.y() + radius * sin(angle) - nodeH/2;
            QRect r(x, y, nodeW, nodeH);
            nodePositions.append(r.center());
            nodeRects.append(r);

            // 设置节点颜色
            QColor fillColor;
            if (isFull) {
                fillColor = QColor(255, 165, 0); // 队满橙色
            } else if (isEmpty) {
                fillColor = QColor(240, 240, 240); // 队空灰色
            } else if (i == frontIdx) {
                fillColor = QColor(255, 200, 200); // 队头红色
            } else if (i == rearIdx) {
                fillColor = QColor(200, 255, 200); // 队尾绿色
            } else if (nodes[i].first != -1) {
                fillColor = QColor(240, 240, 255); // 有效节点蓝色
            } else {
                fillColor = QColor(240, 240, 240); // 空闲节点灰色
            }

            p.fillRect(r, fillColor);
            p.drawRoundedRect(r, 8, 8);
            if (nodes[i].first != -1) {
                p.drawText(r, Qt::AlignCenter, QString::number(nodes[i].first));
            }

            // 保留原有数字索引显示
            p.drawText(r.x() + 5, r.y() + 15, QString::number(i));

            // 在节点下方添加front/rear标签
            if (i == frontIdx) {
                // 绘制front标签（节点下方10像素，居中）
                QRect frontRect(r.x(), r.y() + nodeH + 10, nodeW, 20);
                p.drawText(frontRect, Qt::AlignCenter, "front");
            }
            if (i == rearIdx) {
                // 绘制rear标签（节点下方30像素，居中）
                QRect rearRect(r.x(), r.y() + nodeH + 30, nodeW, 20);
                p.drawText(rearRect, Qt::AlignCenter, "rear");
            }
        }

        // 绘制环形箭头连接
        for (int i = 0; i < n; ++i) {
            int nextIdx = (i + 1) % n; // 循环队列特性：下一个节点 = (当前+1) % 容量
            QPoint start = nodePositions[i];
            QPoint end = nodePositions[nextIdx];

            // 计算箭头方向
            double angle = 2 * M_PI * i / n;
            QPoint adjustedStart = start + QPoint(
                nodeW/2 * cos(angle),
                nodeH/2 * sin(angle)
            );
            QPoint adjustedEnd = end - QPoint(
                nodeW/2 * cos(angle),
                nodeH/2 * sin(angle)
            );

            // 反转箭头方向：交换起点和终点
            p.drawLine(adjustedEnd, adjustedStart);
            drawArrowHead(p, adjustedEnd, adjustedStart);
        }

        // 绘制队头队尾文本标记
        drawCircularMarker(p, center, radius, frontIdx, n, "队头");
        drawCircularMarker(p, center, radius, rearIdx, n, "队尾");

        // 队满/队空提示
        if (isFull) {
            // 移除红色圆圈绘制
            // QPen flashPen(Qt::red, 3);
            // p.setPen(flashPen);
            // p.drawEllipse(center, radius + 20, radius + 20);
            // p.setPen(Qt::black);

            // 添加队满文字提示
            QFont font = p.font();
            font.setPointSize(24);
            font.setBold(true);
            p.setFont(font);
            p.drawText(center.x() - 30, center.y() + 10, "队满");
            p.setFont(QFont()); // 恢复默认字体
        } else if (isEmpty) {
            // 移除蓝色虚线绘制
            // QPen flashPen(Qt::blue, 2, Qt::DashLine);
            // p.setPen(flashPen);
            // p.drawEllipse(center, radius + 10, radius + 10);
            // p.setPen(Qt::black);

            // 添加队空文字提示
            QFont font = p.font();
            font.setPointSize(24);
            font.setBold(true);
            p.setFont(font);
            p.drawText(center.x() - 30, center.y() + 10, "队空");
            p.setFont(QFont()); // 恢复默认字体
        }

        // 更新容量信息显示
        QString capacityText = QString("容量: %1/%2 (节点数: %3)").arg(queue->size()).arg(capacity).arg(n);
        p.drawText(10, 20, capacityText);
    }
}

// 修改标记绘制函数，移除红色虚线
void CanvasWidget::drawCircularMarker(QPainter &p, const QPoint &center, int radius, int idx, int n, const QString &label) {
    double angle = 2 * M_PI * idx / n - M_PI/2;
    QPoint markerPos(
        center.x() + (radius + 40) * cos(angle),
        center.y() + (radius + 40) * sin(angle)
    );
    p.drawText(markerPos, label);
    // 移除红色虚线绘制代码
}

// 添加箭头头部绘制辅助函数
void CanvasWidget::drawArrowHead(QPainter &p, const QPoint &start, const QPoint &end) {
    QLineF line(end, start);
    double angle = line.angle();

    QPointF arrowP1 = end + QPointF(sin(angle * M_PI / 180) * 10, cos(angle * M_PI / 180) * 10);
    QPointF arrowP2 = end + QPointF(sin((angle + 180 - 30) * M_PI / 180) * 10, cos((angle + 180 - 30) * M_PI / 180) * 10);

    p.drawLine(end, arrowP1);
    p.drawLine(end, arrowP2);
}

void CanvasWidget::setDataStructure(DataStructure *ds_)
{
    if (ds) disconnect(ds, &DataStructure::changed, this, &CanvasWidget::onDataChanged);
    ds = ds_;
    if (ds) connect(ds, &DataStructure::changed, this, &CanvasWidget::onDataChanged);
    update();
}

// 添加辅助函数绘制队头队尾标记
void CanvasWidget::drawPositionMarker(QPainter &p, int idx, int cols, int nodeW, int nodeH, int gap, int xOffset, int yOffset, const QString &label) {
    int row = idx / cols;
    int col = idx % cols;
    int x = xOffset + col * (nodeW + gap);
    int y = yOffset + row * (nodeH + gap);

    p.setPen(QPen(Qt::red, 2));
    p.drawRect(x - 5, y - 5, nodeW + 10, nodeH + 10);
    p.drawText(x, y - 15, label);
    p.setPen(QPen(Qt::black)); // 恢复默认画笔
}

// 在cpp文件中实现
void CanvasWidget::startLinkedListTraversal() {
    if (dynamic_cast<LinkedList*>(ds)) {
        currentHighlightIndex = 0;
        if (!traversalTimer) {
            traversalTimer = new QTimer(this);
            connect(traversalTimer, &QTimer::timeout, this, [this]() {
                int nodeCount = ds->visualNodes().size();
                if (currentHighlightIndex >= nodeCount - 1) {
                    stopLinkedListTraversal();
                } else {
                    currentHighlightIndex++;
                    update();
                }
            });
        }
        traversalTimer->start(1000); // 1秒切换一个节点
        update();
    }
}

void CanvasWidget::stopLinkedListTraversal() {
    if (traversalTimer) {
        traversalTimer->stop();
    }
    currentHighlightIndex = -1;
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    if (!ds || !dynamic_cast<LinkedList*>(ds)) {
        QWidget::mousePressEvent(event);
        return;
    }

    LinkedList* list = dynamic_cast<LinkedList*>(ds);
    QList<NodeVisual> nodes = list->visualNodes();
    int n = nodes.size();
    if (n == 0) return;

    // 计算节点位置（与paintEvent保持一致）
    int w = width(), h = height();
    int nodeW = 60, nodeH = 40;
    int gap = qMax(20, (w - n*nodeW) / (n+2));
    int x = gap;
    int y = h/2 - nodeH/2;

    // 检查点击位置是否在节点范围内
    for (int i = 0; i < n; ++i) {
        QRect nodeRect(x, y, nodeW, nodeH);
        if (nodeRect.contains(event->pos())) {
            if (event->button() == Qt::LeftButton) {
                // 左键点击选中节点（标红）
                selectedNodeIndex = i;
                update();
            } else if (event->button() == Qt::RightButton) {
                // 右键点击删除节点
                list->removeAt(i);  // 假设LinkedList有removeAt方法
                selectedNodeIndex = -1;  // 重置选择状态
                update();
            }
            return;
        }
        x += nodeW + gap;
    }

    // 点击空白处取消选择
    selectedNodeIndex = -1;
    update();
    QWidget::mousePressEvent(event);
}


