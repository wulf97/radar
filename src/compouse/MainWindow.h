#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>


class MainCompouse;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setTime();
private:
    MainCompouse *m_mainCompouse;
    QLabel *m_timeLabel;
    QTimer *m_timer;
};

#endif // MAIN_WINDOW_H
