#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QTimer>  // Add QTimer header
#include "datastructure.h"

class CanvasWidget : public QWidget {
    Q_OBJECT
public:
    explicit CanvasWidget(DataStructure *ds_, QWidget *parent = nullptr);
    void startLinkedListTraversal();
    void stopLinkedListTraversal();
    DataStructure* dataStructure() const { return ds; }
    void setDataStructure(DataStructure *ds_);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override; // 添加鼠标事件处理

private slots:
    void onDataChanged();

private:
    DataStructure *ds;
    int currentHighlightIndex = -1;  // 遍历高亮索引
    QTimer *traversalTimer = nullptr;
    int selectedNodeIndex = -1;      // 鼠标选择的节点索引
    void drawPositionMarker(QPainter &p, int idx, int cols, int nodeW, int nodeH, int gap, int xOffset, int yOffset, const QString &label);
    void drawArrowHead(QPainter &p, const QPoint &start, const QPoint &end);
    void drawCircularMarker(QPainter &p, const QPoint &center, int radius, int idx, int n, const QString &label);
    // 动画相关变量
    int animationFrame = 0;
    QTimer* animationTimer = nullptr;
    enum AnimationType { None, Enqueue, Dequeue, Full, Empty } currentAnimation;
    int animationStartIndex = -1;
    int animationEndIndex = -1;
    double animationProgress = 0.0;

    // 动画控制方法
    void startAnimation(AnimationType type, int startIdx, int endIdx);
    void updateAnimation();
    void drawAnimation(QPainter& p);
};

#endif // CANVAS_H
