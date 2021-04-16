#include <QStatusBar>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>

#include "MainWindow.h"
#include "MainCompouse.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_mainCompouse = new MainCompouse;
    m_timeLabel = new QLabel(QTime::currentTime().toString("hh:mm:ss"));
    m_timer = new QTimer(this);

    m_timer->start(1000);

    setMinimumSize(1024, 768);
    resize(1152, 864);

    setWindowFlags(Qt::Window |  Qt::FramelessWindowHint);
    statusBar()->setSizeGripEnabled(true);
    statusBar()->addWidget(m_timeLabel);


    setCentralWidget(m_mainCompouse);

    connect(m_timer, &QTimer::timeout,
            this,    &MainWindow::setTime);
}

MainWindow::~MainWindow() {

}

void MainWindow::setTime() {
    m_timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}
