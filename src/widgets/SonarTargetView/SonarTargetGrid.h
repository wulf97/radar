#ifndef SONAR_TARGET_GRID_H
#define SONAR_TARGET_GRID_H

#include <QGraphicsItem>
#include <QObject>

class SonarTargetGrid : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    SonarTargetGrid(QGraphicsItem *parent = nullptr);
    virtual ~SonarTargetGrid();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    QPointF getCenter() const; // Получение центра мишени

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;

signals:
    void setXPos(int xPos);
    void setYPos(int yPos);
    void setPeleng(int peleng);
    void setDist(int dist);
private:
    QRectF m_boundingRect;
};

#endif // SONAR_TARGET_GRID_H
