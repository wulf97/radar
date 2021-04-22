#ifndef POLAR_POINT_H
#define POLAR_POINT_H

class QPointF;

class PolarPoint {
public:
    PolarPoint(qreal dist = 0, qreal peleng = 0);
    PolarPoint(const PolarPoint &point);
    ~PolarPoint();

    void operator = (const PolarPoint &point);

    void setXY(const QPointF &center, qreal xPos, qreal yPos);
    QPointF getQPointF(const QPointF &center) const;
    qreal getDist() const;
    qreal getPeleng() const;
    qreal getX() const;
    qreal getY() const;

private:
    qreal m_dist;
    qreal m_peleng;
};

#endif // POLAR_POINT_H
