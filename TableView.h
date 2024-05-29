#pragma once

#include <QTableView>

#include "Model.h"
#include <QSortFilterProxyModel>

class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView();

    QString getHeaderFromColumn(int iColumn);
    void removeRowById(int iId);
    void findMin();
    void findMax();
    bool findFromKey(const QString& crQstrData, Keys key);

    QString getModelData (int iRow, int rColumn) const;

    std::vector<std::pair<QString, unsigned int> > getPieValues() const;

signals:
    void minValue(int);
    void maxValue(int);

public slots:
    void onSetData(std::vector<std::string> vNewData);
    void onSave();
    void makeConnections();
    Policy* getPolciyFromIndex(const QModelIndex& crIdx);

private slots:
    void onClickHeader(int iColumn);

private:
    Model* m_pModel;
    QSortFilterProxyModel* m_pProxyModel;
};
