#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QtMath>

#include "SonarTargetScene.h"
#include "SonarTargetGrid.h"
#include "SonarTarget.h"
#include "SonarTargetView.h"


#define UPDATE_TIMER_MS 500
#define ADD_TARGET_TIMER_MS 10000
#define N_TARGETS 9

SonarTargetScene::SonarTargetScene(QObject *parent) : QGraphicsScene(parent) {
    m_targetGrid     = new SonarTargetGrid;
    m_updateTimer    = new QTimer();
    m_addTargetTimer = new QTimer();

    addItem(m_targetGrid);

    connect(m_updateTimer, &QTimer::timeout,
            this,          &SonarTargetScene::slotUpdate);

    connect(m_addTargetTimer, &QTimer::timeout,
            this,             &SonarTargetScene::addTarget);
}

SonarTargetScene::~SonarTargetScene() {
    delete m_targetGrid;

    if (m_updateTimer->isActive()) {
        m_updateTimer->stop();
    }

    if (m_addTargetTimer->isActive()) {
        m_addTargetTimer->stop();
    }

    delete m_updateTimer;
    delete m_addTargetTimer;
}

SonarTargetGrid *SonarTargetScene::getTargetGrid() const {
    return m_targetGrid;
}

SonarTarget *SonarTargetScene::getTarget(int nTarget) const {
    if (nTarget <= m_targets.size() && nTarget > 0) {
        return m_targets.at(nTarget - 1);
    }
}

QPointF SonarTargetScene::getCenter() const {
    if (width() < height()) {
        return QPointF(width()/2, width()/2);
    } else {
        return QPointF(height()/2, height()/2);
    }
}

void SonarTargetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    m_targetGrid->mouseMoveEvent(e);
}

void SonarTargetScene::slotPause() {
    if (m_updateTimer->isActive()) {
        m_updateTimer->stop();
        m_addTargetTimer->stop();
    } else {
        m_updateTimer->start(UPDATE_TIMER_MS);
        m_addTargetTimer->start(ADD_TARGET_TIMER_MS);
    }
}

void SonarTargetScene::selectTarget(int nTarget) {
    qDebug() << nTarget;
    for (auto it = m_targets.begin(); it != m_targets.end(); it++) {
        if (nTarget == (*it)->getId()) {
            (*it)->selectTarget(true);
        } else {
            (*it)->selectTarget(false);
        }
    }
}

void SonarTargetScene::slotUpdate() {
    update(m_targetGrid->boundingRect());

    for (auto target : m_targets) {
        target->updatePos();

        emit targetPos(target->getId(), target->getPolarPoint());
    }
}


void SonarTargetScene::addTarget() {
    // Добавление целей на мишень
    if (m_targets.size() < N_TARGETS) {
        QPointF center = m_targetGrid->getCenter();
        SonarTarget *target = new SonarTarget(center, std::rand()%(m_targetGrid->getRingRadius1() - m_targetGrid->getRingRadius2()) + m_targetGrid->getRingRadius2(),
                                              std::rand()%360, m_targetGrid);

        emit targetPos(target->getId(), target->getPolarPoint());

        connect(target,  &SonarTarget::targetClick,
                this,    &SonarTargetScene::targetClick);

        m_targets.push_back(target);
    } else {
        disconnect(m_addTargetTimer, &QTimer::timeout,
                   this,             &SonarTargetScene::addTarget);
    }
}
