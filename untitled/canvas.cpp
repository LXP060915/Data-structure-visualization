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
        p.drawText(rect(), Qt::AlignCenter, "空");
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
            
            // 栈满时所有节点变橙色，否则栈顶红色、其他节点灰色
            QColor fillColor;
            if (stack->isFull()) {
                fillColor = QColor(255, 165, 0); // 橙色
            } else {
                fillColor = (i == 0) ? QColor(255, 0, 0) : QColor(240, 240, 240);
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
            p.drawRoundedRect(r,8,8);
            QString txt = QString::number(nodes[i].first);
            p.drawText(r, Qt::AlignCenter, txt);

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
        // ================= 循环队列（优化版）=================
        int w = width(), h = height();
        int nodeW = 60, nodeH = 40;
        QList<NodeVisual> nodes = ds->visualNodes();
        int n = nodes.size();
        if (n == 0) return;

        // 计算圆心和半径（仅用于布局计算，不绘制圆周）
        QPoint center(w/2, h/2);
        int radius = qMin(w, h) / 3;

        // 存储所有节点位置
        QVector<QPoint> nodePositions;
        QVector<QRect> nodeRects;

        // 获取队头队尾索引
        CircularQueue* queue = dynamic_cast<CircularQueue*>(ds);
        int frontIdx = -1, rearIdx = -1;
        if (queue) {
            frontIdx = queue->frontIndex();
            rearIdx = queue->rearIndex();
        }

        // 绘制所有节点
        for (int i = 0; i < n; ++i) {
            // 计算角度和位置
            double angle = 2 * M_PI * i / n - M_PI/2;
            int x = center.x() + radius * cos(angle) - nodeW/2;
            int y = center.y() + radius * sin(angle) - nodeH/2;
            QRect r(x, y, nodeW, nodeH);
            nodePositions.append(r.center());
            nodeRects.append(r);

            // 设置节点颜色（队头红色，队尾绿色，其他正常）
            if (i == frontIdx) {
                p.setBrush(QColor(255, 200, 200)); // 队头红色
            } else if (i == rearIdx) {
                p.setBrush(QColor(200, 255, 200)); // 队尾绿色
            } else if (nodes[i].first != -1) {
                p.setBrush(QColor(240, 240, 255)); // 有效节点蓝色
            } else {
                p.setBrush(QColor(240, 240, 240)); // 空闲节点灰色
            }

            // 绘制节点
            p.drawRoundedRect(r, 8, 8);
            if (nodes[i].first != -1) {
                p.drawText(r, Qt::AlignCenter, QString::number(nodes[i].first));
            }
        }

        // 绘制环形箭头（移除红色虚线）
        for (int i = 0; i < n; ++i) {
            int nextIdx = nodes[i].second;
            if (nextIdx < 0 || nextIdx >= n) continue;

            QPoint start = nodePositions[i];
            QPoint end = nodePositions[nextIdx];

            // 计算箭头方向并调整起点终点
            double angle = 2 * M_PI * i / n;
            QPoint adjustedStart = start + QPoint(
                nodeW/2 * cos(angle), 
                nodeH/2 * sin(angle)
            );
            QPoint adjustedEnd = end - QPoint(
                nodeW/2 * cos(angle), 
                nodeH/2 * sin(angle)
            );

            // 绘制箭头（无红色虚线）
            p.drawLine(adjustedStart, adjustedEnd);
            drawArrowHead(p, adjustedStart, adjustedEnd);
        }

        // 绘制队头队尾文本标记（无连接线）
        if (queue) {
            drawCircularMarker(p, center, radius, frontIdx, n, "队头");
            drawCircularMarker(p, center, radius, rearIdx, n, "队尾");
        }
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
