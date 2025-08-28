#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "datastructure.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(DataStructure *ds_, QWidget *parent=nullptr);
    DataStructure* dataStructure() const { return ds; }
    void setDataStructure(DataStructure *ds_);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onDataChanged();

private:
    DataStructure *ds = nullptr;
    void drawPositionMarker(QPainter &p, int idx, int cols, int nodeW, int nodeH, int gap, int xOffset, int yOffset, const QString &label);
    void drawArrowHead(QPainter &p, const QPoint &start, const QPoint &end);
    void drawCircularMarker(QPainter &p, const QPoint &center, int radius, int idx, int n, const QString &label);
};

#endif // CANVAS_H
