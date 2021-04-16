#include <QModelIndex>
#include <QDebug>

#include "SonarTableModel.h"

SonarTableModel::SonarTableModel(QObject *parent) : QStandardItemModel(parent) {
    setRowCount(9);

    setHorizontalHeaderLabels(QStringList()
                              << tr("№ цели")
                              << tr("Положение по оси\n X от центра круга\n (px)")
                              << tr("Положение по оси\n Y от центра круга\n (px)")
                              << tr("Пеленг\n относительно\n центра\n круга\n (градусы)")
                              << tr("Удаление\n от центра\n круга\n (px)"));

//    setData(index(0, 0), QString("3"));
//    setData(index(1, 0), QString("2"));
}

SonarTableModel::~SonarTableModel() {

}

void SonarTableModel::setFirsTarget(int nTarget) {
    int nRow = getTargetRow(nTarget);

    if (nRow == 0) return;

    // Скопировать содержимое выбранной строки во временный список строк
    QStringList dataList;
    for (int i = 0; i < columnCount(); i++) {
        dataList.push_back(data(index(nRow, i)).toString());
    }

    // Переместить строки, выше выбранной, вниз на один
    for (int i = nRow - 1; i >= 0; i--) {
        for (int j = 0; j < columnCount(); j++) {
            setData(index(i + 1, j), data(index(i, j)));
        }
    }

    // Скопировать содержимое выбранной строки в первую строку
    for (int i = 0; i < columnCount(); i++) {
        setData(index(0, i), dataList.at(i));
    }
}

void SonarTableModel::setItem(int nTarget, const QStringList &data) {
    setData(index(getTargetRow(nTarget), 0), nTarget);

    int i = 1;
    for (auto it = data.begin(); it != data.end(); i++, it++) {
        setData(index(getTargetRow(nTarget), i), *it);
    }
}

void SonarTableModel::slotSelectTarget(const QModelIndex &current) {
    if (data(index(current.row(), 0)).toString() != QString("")) {
        emit selectTarget(data(index(current.row(), 0)).toInt());
    }
}

int SonarTableModel::getTargetRow(int nTarget) {
    // Проверить строки с номерами целей на соответствие с nTarget
    for (int i = 0; i < rowCount(); i++) {
        if (data(index(i, 0)) == nTarget || data(index(i, 0)).toString() == QString("")) return i;
    }

    return nTarget - 1;
}
