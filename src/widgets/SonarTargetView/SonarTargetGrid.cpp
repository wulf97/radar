#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>

#include "SonarTargetGrid.h"
#include "SonarTargetScene.h"

SonarTargetGrid::SonarTargetGrid(QGraphicsItem *parent) : QGraphicsItem(parent) {
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

SonarTargetGrid::~SonarTargetGrid() {

}

QRectF SonarTargetGrid::boundingRect() const {
    return m_boundingRect;
}

QPainterPath SonarTargetGrid::shape() const {
    QPainterPath path;

    path.addEllipse(boundingRect());

    return path;
}

void SonarTargetGrid::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
//    qDebug() << "SonarTargetGrid::paint()";

    painter->save();

    int mainRadius = qobject_cast<SonarTargetScene*>(scene())->getCenter().x() - painter->pen().width();

    QImage backgroundImg(QSize(2*mainRadius, 2*mainRadius), QImage::Format_RGB888);
    for (auto i = 0; i < backgroundImg.height(); i++) {
        for (auto j = 0; j < backgroundImg.width(); j++) {
            int color = std::rand()%80;
            backgroundImg.setPixelColor(i, j, QColor(color, color, color));
        }
    }

    QPixmap background = QPixmap::fromImage(backgroundImg);

    painter->setBrush(background);
    painter->setPen(QPen(Qt::blue));
    painter->drawEllipse(QRect(QPoint(painter->pen().width(), painter->pen().width()),
                               QSize(2*mainRadius, 2*mainRadius)));

    painter->setBrush(QBrush());

    painter->setPen(QPen(Qt::green));
    for (int i = 0; i <= mainRadius/100; i++) {
        painter->drawEllipse(QPoint(mainRadius + painter->pen().width(), mainRadius + painter->pen().width()), 100*i, 100*i);

        if (i == mainRadius/100)     m_ringRadius1 = 100*i;
        if (i == mainRadius/100 - 1) m_ringRadius2 = 100*i;
    }

    painter->setPen(QPen(Qt::green, 1, Qt::DashLine));

    for (float ang = 0; ang < 180; ang += 45) {
        painter->drawLine(QPoint(qSin(qDegreesToRadians(ang))*mainRadius + mainRadius, qCos(qDegreesToRadians(ang))*mainRadius + mainRadius),
                          QPoint(mainRadius - qSin(qDegreesToRadians(ang))*mainRadius, mainRadius - qCos(qDegreesToRadians(ang))*mainRadius));
    }

    m_boundingRect = QRectF(QPointF(0, 0), QSize(2*mainRadius + 2*painter->pen().width(), 2*mainRadius + 2*painter->pen().width()));

    painter->restore();
}

QPointF SonarTargetGrid::getCenter() const {
    return QPointF(boundingRect().width()/2,
                   boundingRect().height()/2);
}

int SonarTargetGrid::getRingRadius1() const {
    return m_ringRadius1;
}

int SonarTargetGrid::getRingRadius2() const {
    return m_ringRadius2;
}

void SonarTargetGrid::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    if (shape().contains(e->scenePos())) {
        int x = e->scenePos().x() - m_boundingRect.width()/2;
        int y = m_boundingRect.height()/2 - e->scenePos().y();
        int peleng;
        int dist = qSqrt(x*x + y*y);

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

        emit setXPos(x);
        emit setYPos(y);
        emit setPeleng(peleng);
        emit setDist(dist);
    }
}
