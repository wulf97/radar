#include <QHBoxLayout>
#include <QPushButton>

#include "MainCompouse.h"
#include "SonarTargetView.h"
#include "SonarControl.h"

MainCompouse::MainCompouse(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *mainLayout = new QHBoxLayout;

    m_sonarTargetView  = new SonarTargetView(new SonarTargetScene(), this);
    m_sonarControl = new SonarControl(this);

    mainLayout->addWidget(m_sonarTargetView);
    mainLayout->addWidget(m_sonarControl);

    setLayout(mainLayout);

    connect(m_sonarTargetView, &SonarTargetView::setCenter,
            m_sonarControl,    &SonarControl::setCenter);
    connect(m_sonarTargetView, &SonarTargetView::setXPos,
            m_sonarControl,    &SonarControl::setXPos);
    connect(m_sonarTargetView, &SonarTargetView::setYPos,
            m_sonarControl,    &SonarControl::setYPos);
    connect(m_sonarTargetView, &SonarTargetView::setPeleng,
            m_sonarControl,    &SonarControl::setPeleng);
    connect(m_sonarTargetView, &SonarTargetView::setDist,
            m_sonarControl,    &SonarControl::setDist);
    connect(m_sonarTargetView, &SonarTargetView::targetPos,
             m_sonarControl,   &SonarControl::targetPos);
    connect(m_sonarTargetView, &SonarTargetView::targetClick,
            m_sonarControl,    &SonarControl::targetClick);

    connect(m_sonarControl,    &SonarControl::pause,
            m_sonarTargetView, &SonarTargetView::pause);
    connect(m_sonarControl,    &SonarControl::selectTarget,
            m_sonarTargetView, &SonarTargetView::selectTarget);
}

MainCompouse::~MainCompouse() {

}
