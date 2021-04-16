#include <QDebug>
#include <QBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QApplication>
#include <QTableView>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "SonarControl.h"
#include "SonarCursorPos.h"
#include "SonarTableModel.h"

SonarControl::SonarControl(QWidget *parent) : QWidget(parent) {
    m_pauseButton = new QPushButton(tr("Пауза"));
    m_exitButton  = new QPushButton(tr("Выйти"));
    m_cursorPos   = new SonarCursorPos;
    m_tableView   = new QTableView;
    m_tableModel  = new SonarTableModel;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *btnLayout  = new QHBoxLayout;

    QSpacerItem *btnSpacer  = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    setFixedWidth(400);

    m_pauseButton->setStyleSheet("QPushButton{font-size: 18px; font-weight: bold; padding: 10px;}");
    m_pauseButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    m_exitButton->setStyleSheet("QPushButton{font-size: 18px; font-weight: bold; padding: 10px;}");
    m_exitButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setModel(m_tableModel);
    m_tableView->resizeColumnsToContents();
    m_tableView->resizeRowsToContents();
    for (int i = 0; i < m_tableModel->rowCount(); i++) {
        m_tableView->setRowHeight(i, 40);
    }

    btnLayout->addSpacerItem(btnSpacer);
    btnLayout->addWidget(m_pauseButton);
    btnLayout->addWidget(m_exitButton);

    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_cursorPos);
    mainLayout->addWidget(m_tableView);
    setLayout(mainLayout);

    connect(m_tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            m_tableModel,                  &SonarTableModel::slotSelectTarget);

    connect(m_tableModel, &SonarTableModel::selectTarget,
            this,         &SonarControl::selectTarget);

    connect(m_pauseButton, &QPushButton::clicked,
            this,          &SonarControl::pause);
    connect(m_exitButton, &QPushButton::clicked,
            qApp,         &QApplication::quit);
}

SonarControl::~SonarControl() {

}

void SonarControl::setCenter(QPointF center) {
    m_center = center;
}

void SonarControl::setXPos(int xPos) {
    m_cursorPos->setXPos(xPos);
}

void SonarControl::setYPos(int yPos) {
    m_cursorPos->setYPos(yPos);
}

void SonarControl::setPeleng(int peleng) {
    m_cursorPos->setPeleng(peleng);
}

void SonarControl::setDist(int dist) {
    m_cursorPos->setDist(dist);
}

void SonarControl::targetPos(int nTarget, PolarPoint point) {
    QStringList data = QStringList()
                       << QString("%1").arg(point.getX(m_center))
                       << QString("%1").arg(point.getY(m_center))
                       << QString("%1").arg(point.getPeleng())
                       << QString("%1").arg(point.getDist());

    m_tableModel->setItem(nTarget, data);
}

void SonarControl::targetClick(int nTarget) {
    m_tableModel->setFirsTarget(nTarget);
}
