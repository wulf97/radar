#ifndef MAIN_COMPOUSE_H
#define MAIN_COMPOUSE_H

#include <QWidget>

class SonarTargetView;
class SonarControl;

class MainCompouse : public QWidget {
    Q_OBJECT
public:
    MainCompouse(QWidget *parent = nullptr);
    virtual ~MainCompouse();

private:
    SonarTargetView *m_sonarTargetView;
    SonarControl *m_sonarControl;
};

#endif // MAIN_COMPOUSE_H
