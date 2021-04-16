#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include "SonarTargetView.h"
#include "SonarTargetGrid.h"
#include "SonarTargetScene.h"

SonarTargetView::SonarTargetView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
    scene->setParent(this);
    scene->setSceneRect(0, 0, width() - 10, height() - 10);

    setRenderHint(QPainter::Antialiasing, true);
    setMouseTracking(true);

    connect(qobject_cast<SonarTargetScene*>(scene)->getTargetGrid(), &SonarTargetGrid::setXPos,
            this,                                                    &SonarTargetView::setXPos);
    connect(qobject_cast<SonarTargetScene*>(scene)->getTargetGrid(), &SonarTargetGrid::setYPos,
            this,                                                    &SonarTargetView::setYPos);
    connect(qobject_cast<SonarTargetScene*>(scene)->getTargetGrid(), &SonarTargetGrid::setPeleng,
            this,                                                    &SonarTargetView::setPeleng);
    connect(qobject_cast<SonarTargetScene*>(scene)->getTargetGrid(), &SonarTargetGrid::setDist,
            this,                                                    &SonarTargetView::setDist);

    connect(this,                                   &SonarTargetView::pause,
            qobject_cast<SonarTargetScene*>(scene), &SonarTargetScene::slotPause);

    connect(this,                                   &SonarTargetView::selectTarget,
            qobject_cast<SonarTargetScene*>(scene), &SonarTargetScene::selectTarget);

    connect(qobject_cast<SonarTargetScene*>(scene), &SonarTargetScene::targetPos,
            this,                                   &SonarTargetView::targetPos);

    connect(qobject_cast<SonarTargetScene*>(scene), &SonarTargetScene::targetClick,
            this,                                   &SonarTargetView::targetClick);
}

SonarTargetView::~SonarTargetView() {

}

void SonarTargetView::resizeEvent(QResizeEvent *e) {
    scene()->setSceneRect(0, 0, width() - 10, height() - 10);

    emit setCenter(qobject_cast<SonarTargetScene*>(scene())->getCenter());
}
