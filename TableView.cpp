#include "TableView.h"

#include <QMessageBox>
#include <QHeaderView>

#include "ItemDelegate.h"

TableView::TableView()
    : m_pModel{new Model(this)},
      m_pProxyModel{new QSortFilterProxyModel(this)}
{
    m_pProxyModel->setSourceModel(m_pModel);

    m_pProxyModel->setSortRole(Qt::UserRole);

    QFont font = horizontalHeader()->font();

    font.setBold(true);

    horizontalHeader()->setFont(font);

    setModel(m_pProxyModel);

    setItemDelegate(new ItemDelegate);
    connect(horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onClickHeader(int)));
    resizeColumnsToContents();

    makeConnections();
}

void TableView::removeRowById(int iId)
{
    if(!m_pModel->removeFromPolicyId(iId))
        QMessageBox::warning(this, QString::fromLocal8Bit("Внимание!"), QString::fromLocal8Bit("Полис ") + QString("%1").arg(iId) + QString::fromLocal8Bit(" не найден"));
}

void TableView::findMin()
{
    m_pModel->findMin();
}

void TableView::findMax()
{
    m_pModel->findMax();
}

bool TableView::findFromKey(const QString& crQstrData, Keys key)
{
    QModelIndex idx = m_pModel->findFromKey(crQstrData, key);

    if(idx.isValid())
    {
        setCurrentIndex(idx);
        return true;
    }
    else
        return false;
}

void TableView::onSetData(std::vector<std::string> vNewData)
{
    m_pModel->insertRow(vNewData, model()->rowCount());
}

void TableView::onSave()
{
    m_pModel->saveData();
}

void TableView::makeConnections()
{
    connect(m_pModel, SIGNAL(minValue(int)), SIGNAL(minValue(int)));
    connect(m_pModel, SIGNAL(maxValue(int)), SIGNAL(maxValue(int)));
}

Policy* TableView::getPolciyFromIndex(const QModelIndex& crIdx)
{
    return m_pModel->getPolciyFromIndex(crIdx);
}

QString TableView::getHeaderFromColumn(int iColumn)
{
    return m_pModel->headerData(iColumn, Qt::Horizontal, Qt::DisplayRole).toString();
}

void TableView::onClickHeader(int iColumn)
{
    if(iColumn == 3 || iColumn == 9 || iColumn == 10)
    {
        if(m_pProxyModel->sortOrder() == Qt::AscendingOrder)
            m_pProxyModel->sort(iColumn, Qt::DescendingOrder);
        else
            m_pProxyModel->sort(iColumn, Qt::AscendingOrder);
    }
}

std::vector<std::pair<QString, unsigned int> > TableView::getPieValues() const
{
    return m_pModel->getPieValues();
}

QString TableView::getModelData(int iRow, int iColumn) const
{
    return m_pModel->index(iRow, iColumn).data(Qt::DisplayRole).toString();
}
