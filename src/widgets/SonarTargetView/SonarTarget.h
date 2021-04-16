#ifndef SONARTARGET_H
#define SONARTARGET_H

#include <QGraphicsItem>
#include <QObject>

#include "PolarPoint.h"

class SonarTarget : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    SonarTarget(const QPointF &center,
                qreal dist,
                qreal peleng,
                QGraphicsItem *parent = nullptr);
    virtual ~SonarTarget();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e) override;

    void updatePos();
    void selectTarget(bool fl);

    const PolarPoint &getPolarPoint() const;
    qreal getDist() const;  // Получение расстояния до центра мишени
    int getPeleng() const;  // Получение пеленга цели
    int getId() const;

signals:
    void targetClick(int nTarget);

private slots:
    void slotBlink();

private:
    void resetCenter(const QPointF &center); // Изменение координат центра мишени


private:
    QTimer            *m_blinkTimer;
    QPointF           m_center;   // Центр мишени
    QPolygon          m_polygon;  // Рисунок цели
    QList<PolarPoint> m_track;    // Список точек трека передвижения цели
    PolarPoint        m_pos;      // Координаты цели в полярной системе координат
    int               m_directionAngle {0};
    static int        s_idGen;
    static int        s_colorGen;
    int               m_color;
    int               m_id;
    bool              m_isDisplay {true};
};


#endif // SONARTARGET_H
