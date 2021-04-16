#ifndef SONAR_TARGET_SCENE_H
#define SONAR_TARGET_SCENE_H

#include <QGraphicsScene>

#include "PolarPoint.h"

class SonarTargetGrid;
class SonarTarget;
class QTimer;

class SonarTargetScene : public QGraphicsScene {
     Q_OBJECT
public:
    SonarTargetScene(QObject *parent = nullptr);
    virtual ~SonarTargetScene();

    SonarTargetGrid *getTargetGrid() const;
    SonarTarget     *getTarget(int nTarget) const;
    QPointF         getCenter() const;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e);

public slots:
    void slotPause();
    void selectTarget(int nTarget);

signals:
    void targetPos(int nTarget, PolarPoint point);
    void targetClick(int nTarget);

private slots:
    void slotUpdate();
    void addTarget();

private:
    SonarTargetGrid       *m_targetGrid;     // Графическое представление мишени
    QVector<SonarTarget*> m_targets;         // Список графических представлений целей
    QTimer                *m_updateTimer;    // Таймер обновления информации
    QTimer                *m_addTargetTimer; // Таймер добавления новых целей
};

#endif // SONAR_TARGET_SCENE_H
