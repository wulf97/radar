#ifndef SONAR_TARGET_VIEW_H
#define SONAR_TARGET_VIEW_H

#include <QGraphicsView>

#include "SonarTargetScene.h"
#include "PolarPoint.h"

class SonarTargetView : public QGraphicsView {
    Q_OBJECT
public:
    SonarTargetView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~SonarTargetView();

protected:
    virtual void resizeEvent(QResizeEvent *e) override;

signals:
    void setCenter(QPointF center);
    void setXPos(int xPos);
    void setYPos(int yPos);
    void setPeleng(int peleng);
    void setDist(int dist);
    void pause();
    void targetPos(int nTarget, PolarPoint point);
    void selectTarget(int nTarget);
    void targetClick(int nTarget);
};

#endif // SONAR_TARGET_VIEW_H
