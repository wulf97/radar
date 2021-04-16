#include <QtMath>
#include <QPointF>

#include "PolarPoint.h"

PolarPoint::PolarPoint(qreal dist, qreal peleng, QObject *parent) : QObject(parent) {
    m_dist = dist;
    m_peleng = peleng;
}

PolarPoint::PolarPoint(const PolarPoint &point) {
    m_dist   = point.m_dist;
    m_peleng = point.m_peleng;
}

PolarPoint::~PolarPoint() {

}

void PolarPoint::operator = (const PolarPoint &point) {
    m_dist   = point.m_dist;
    m_peleng = point.m_peleng;
}

void PolarPoint::setXY(const QPointF &center, qreal xPos, qreal yPos) {
    qreal x = xPos - center.x();
    qreal y = center.y() - yPos;
    qreal peleng;
    qreal dist = qSqrt(x*x + y*y);


    if (x) {
        peleng = qRadiansToDegrees(qAtan(static_cast<double>(y)/x));

        if (y > 0) {
            if (x < 0) peleng += 180;
        } else {
            if (x < 0) {
                peleng += 180;
            } else {
                peleng += 360;
            }
        }
    } else {
        if (y > 0)
            peleng = 90;
        else
            peleng = 270;
    }

    m_dist = dist;
    m_peleng = peleng;
}

QPointF PolarPoint::getQPointF(const QPointF &center) const {
    qreal x {0};
    qreal y {0};

    x = m_dist*qCos(qDegreesToRadians(m_peleng));
    y = -m_dist*qSin(qDegreesToRadians(m_peleng));

    x += center.x();
    y += center.y();

    return QPointF(x, y);
}

qreal PolarPoint::getDist() const {
    return m_dist;
}

qreal PolarPoint::getPeleng() const {
    return m_peleng;
}

qreal PolarPoint::getX(const QPointF &center) const {
    qreal x {0};

    x = m_dist*qCos(qDegreesToRadians(m_peleng));

    return x;
}

qreal PolarPoint::getY(const QPointF &center) const {
    qreal y {0};

    y = m_dist*qSin(qDegreesToRadians(m_peleng));

    return y;
}
