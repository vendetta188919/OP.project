#pragma once

#include <QAbstractTableModel>

#include <QString>
#include <QList>

#include "Policy.h"
#include "FileParser.h"

class Model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit Model(QObject* pParent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    int rowCount(const QModelIndex& = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QVariant data(const QModelIndex& crIndex, int iRole) const;
    bool setData(const QModelIndex& index, const QVariant& rValue, int iRole);
    bool removeRow(int iRow, const QModelIndex& = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex& crIndex) const;

    void insertRow(const std::vector<std::string>& crVecNewData, int, const QModelIndex& = QModelIndex());
    void saveData();

    std::vector<std::pair<QString, unsigned int> > getPieValues();

    Policy* getPolciyFromIndex(const QModelIndex& crIdx);
    bool removeFromPolicyId(int iId);

    QModelIndex findFromKey(const QString& crQstrData, Keys key);

    //void findMin();
    //void findMax();

signals:
    void minValue(int);
    void maxValue(int);

private:
    void loadData();
    QString getTypeProgramm(unsigned int uType);

private:
    QList<Policy*> m_ValuesAllRows;
    FileParser* m_Parser;
    std::pair<QString, int> getDisplayNameForType(Keys key, unsigned int iValueType) const;
};
