#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QDebug>

#include "SonarCursorPos.h"

SonarCursorPos::SonarCursorPos(QWidget *parent) : QWidget(parent) {
    m_xPosLabel = new QLabel(QString(tr("Положение по оси X от центра круга: %1 px")).arg(0));
    m_yPosLabel = new QLabel(QString(tr("Положение по оси Y от центра круга: %1 px")).arg(0));
    m_pelengLabel = new QLabel(QString(tr("Пеленг относительно центра круга: %1 градусов")).arg(0));
    m_distLabel = new QLabel(QString(tr("Удаление от центра круга: %1 px")).arg(0));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    mainLayout->addWidget(m_xPosLabel);
    mainLayout->addWidget(m_yPosLabel);
    mainLayout->addWidget(m_pelengLabel);
    mainLayout->addWidget(m_distLabel);
    mainLayout->addSpacerItem(spacer);

    setFixedHeight(120);

    setLayout(mainLayout);
}

SonarCursorPos::~SonarCursorPos() {

}

void SonarCursorPos::setXPos(int xPos) {
    m_xPosLabel->setText(QString(tr("Положение по оси X от центра круга: %1 px")).arg(xPos));
}

void SonarCursorPos::setYPos(int yPos) {
    m_yPosLabel->setText(QString(tr("Положение по оси Y от центра круга: %1 px")).arg(yPos));
}

void SonarCursorPos::setPeleng(int peleng) {
    m_pelengLabel->setText(QString(tr("Пеленг относительно центра круга: %1 градусов")).arg(peleng));
}

void SonarCursorPos::setDist(int dist) {
    m_distLabel->setText(QString(tr("Удаление от центра круга: %1 px")).arg(dist));
}
