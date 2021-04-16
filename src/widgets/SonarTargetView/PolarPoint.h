#ifndef POLAR_POINT_H
#define POLAR_POINT_H

#include <QObject>

class QPointF;

class PolarPoint : public QObject {
    Q_OBJECT
public:
    PolarPoint(qreal dist = 0, qreal peleng = 0, QObject *parent = nullptr);
    PolarPoint(const PolarPoint &point);
    ~PolarPoint();

    void operator = (const PolarPoint &point);

    void setXY(const QPointF &center, qreal xPos, qreal yPos);
    QPointF getQPointF(const QPointF &center) const;
    qreal getDist() const;
    qreal getPeleng() const;
    qreal getX(const QPointF &center) const;
    qreal getY(const QPointF &center) const;

private:
    qreal m_dist;
    qreal m_peleng;
};

#endif // POLAR_POINT_H
