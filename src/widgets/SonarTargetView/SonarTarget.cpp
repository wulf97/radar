#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

#include "SonarTarget.h"
#include "SonarTargetScene.h"

#define BLINK_TIMER_MS 200

int SonarTarget::s_colorGen = Qt::GlobalColor::red;
int SonarTarget::s_idGen = 1;

SonarTarget::SonarTarget(const QPointF &center, qreal dist, qreal peleng, QGraphicsItem *parent) : QGraphicsItem(parent) {
    m_blinkTimer = new QTimer();
    m_center = center;
    m_pos    = PolarPoint(dist, peleng);
    m_id     = s_idGen;
    m_color  = s_colorGen;

    m_directionAngle = 90*(std::rand()%4);

    m_polygon.append(QPoint(0, -30*qCos(qDegreesToRadians(75.))));
    m_polygon.append(QPoint(0, 30*qCos(qDegreesToRadians(75.))));
    m_polygon.append(QPoint(30*qSin(qDegreesToRadians(75.)), 0));

    setPos(m_pos.getQPointF(center));
    setRotation(m_directionAngle);

    m_track.push_back(m_pos);

    s_idGen++;
    s_colorGen++;

    connect(m_blinkTimer, &QTimer::timeout,
            this,         &SonarTarget::slotBlink);
}

SonarTarget::~SonarTarget() {
    if (m_blinkTimer->isActive()) {
        m_blinkTimer->stop();
    }

    delete m_blinkTimer;
}

QRectF SonarTarget::boundingRect() const {
    return shape().boundingRect();
}

QPainterPath SonarTarget::shape() const  {
    QPainterPath path;

    path.addPolygon(m_polygon);

    return path;
}

void SonarTarget::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    painter->setPen(QPen(Qt::GlobalColor(m_color)));

    if (m_isDisplay) {
        painter->drawPolygon(m_polygon);
    }

    if (m_track.size() > 1) {
        auto it = m_track.begin();
        QPointF prePoint = mapFromParent((*it).getQPointF(m_center));
        for (auto it = m_track.begin() + 1; it != m_track.end(); it++) {
            painter->drawLine(prePoint, mapFromParent((*it).getQPointF(m_center)));
            prePoint = mapFromParent((*it).getQPointF(m_center));
        }
    }

    painter->restore();

    m_center = qobject_cast<SonarTargetScene*>(scene())->getCenter();
    resetCenter(m_center);
}

void SonarTarget::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    Q_UNUSED(e)

    emit targetClick(m_id);
}

void SonarTarget::updatePos() {
    m_directionAngle = 90*(std::rand()%4);

    setPos(pos().x() + 20*qCos(qDegreesToRadians(static_cast<float>(m_directionAngle))),
           pos().y() + 20*qSin(qDegreesToRadians(static_cast<float>(m_directionAngle))));
    setRotation(m_directionAngle);

    m_pos.setXY(m_center, pos().x(), pos().y());

    m_track.push_back(m_pos);
    if (m_track.size() > 4) {
        m_track.pop_front();
    }
}

void SonarTarget::selectTarget(bool fl) {
    if (fl) {
        m_blinkTimer->start(BLINK_TIMER_MS);
    } else {
        if (m_blinkTimer->isActive()) {
            m_blinkTimer->stop();
            m_isDisplay = true;
        }
    }
}

const PolarPoint &SonarTarget::getPolarPoint() const {
    return m_pos;
}

qreal SonarTarget::getDist() const {
    return m_pos.getDist();
}

int SonarTarget::getPeleng() const {
    return m_pos.getPeleng();
}

int SonarTarget::getId() const {
    return m_id;
}

void SonarTarget::slotBlink() {
    if (m_isDisplay) {
        m_isDisplay = false;
    } else {
        m_isDisplay = true;
    }
    update();
}

void SonarTarget::resetCenter(const QPointF &center) {
    m_center = center;
    setPos(m_pos.getQPointF(center));
}
