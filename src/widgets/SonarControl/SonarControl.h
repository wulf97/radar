#ifndef SONAR_CONTROL_H
#define SONAR_CONTROL_H

#include <QWidget>

#include "PolarPoint.h"

class SonarCursorPos;
class QPushButton;
class QTableView;
class SonarTableModel;

class SonarControl : public QWidget {
    Q_OBJECT
public:
    SonarControl(QWidget *parent = nullptr);
    virtual ~SonarControl();

public slots:
    void setCenter(QPointF center);
    void setXPos(int xPos);
    void setYPos(int yPos);
    void setPeleng(int peleng);
    void setDist(int dist);
    void targetPos(int nTarget, PolarPoint point);
    void targetClick(int nTarget);

signals:
    void pause();
    void selectTarget(int nTarget);

private:
    QPushButton     *m_pauseButton;
    QPushButton     *m_exitButton;
    SonarCursorPos  *m_cursorPos;
    QTableView      *m_tableView;
    SonarTableModel *m_tableModel;
    QPointF         m_center;
};

#endif // SONAR_CONTROL_H
