#ifndef SONAR_CURSOR_POS_H
#define SONAR_CURSOR_POS_H

#include <QWidget>

class QLabel;

class SonarCursorPos : public QWidget {
    Q_OBJECT
public:
    SonarCursorPos(QWidget *parent = nullptr);
    virtual ~SonarCursorPos();

public slots:
    void setXPos(int xPos);
    void setYPos(int yPos);
    void setPeleng(int peleng);
    void setDist(int dist);

private:
    QLabel *m_xPosLabel;
    QLabel *m_yPosLabel;
    QLabel *m_pelengLabel;
    QLabel *m_distLabel;
};

#endif // SONAR_CURSOR_POS_H
