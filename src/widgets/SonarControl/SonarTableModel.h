#ifndef SONARTABLEMODEL_H
#define SONARTABLEMODEL_H

#include <QStandardItemModel>

class SonarTableModel : public QStandardItemModel {
    Q_OBJECT
public:
    SonarTableModel(QObject *parent = nullptr);
    virtual ~SonarTableModel();

    void setFirsTarget(int nTarget);
public slots:
    void setItem(int nTarget, const QStringList &data);
    void slotSelectTarget(const QModelIndex &current);

signals:
    void selectTarget(int nTarget);

private:
    int getTargetRow(int nTarget);
};

#endif // SONARTABLEMODEL_H
