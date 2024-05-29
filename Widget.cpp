#include "Widget.h"

#include <QFileDialog>

#include <QMessageBox>

#include <QRegularExpressionValidator>
#include <QValidator>

#include "PolicyMaker.h"
#include "OnePolicyWidget.h"
#include "PieChart.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_pView{new TableView()},
      m_pRemoveBtn{new QPushButton(QString::fromLocal8Bit("Удалить"))},
      m_pCreateNewBtn{new QPushButton(QString::fromLocal8Bit("Создать"))},
      m_pSaveBtn{new QPushButton(QString::fromLocal8Bit("Сохранить"))},
      m_pShowOnePolicyBtn{new QPushButton(QString::fromLocal8Bit("Показать текущий"))},
      m_pFindMinBtn{new QPushButton(QString::fromLocal8Bit("Найти мин премию"))},
      m_pFindMaxBtn{new QPushButton(QString::fromLocal8Bit("Найти макс премию"))},
      m_pFindTermBtn{new QPushButton(QString::fromLocal8Bit("Поиск срока"))},
      m_pFindAreaBtn{new QPushButton(QString::fromLocal8Bit("Поиск площади"))},
      m_pPieBtn{new QPushButton(QString::fromLocal8Bit("Диаграмма"))},
      m_pRemoveEdit{new QLineEdit()},
      m_pAreaEdit{new QLineEdit()},
      m_pTermEdit{new QLineEdit()}

{
    initGui();
    createConnections();
}

void Widget::onMakeNewPolicy()
{

    std::vector<int> vId;
    for(int iRow{0}; iRow < m_pView->model()->rowCount(); ++iRow)
    {
        vId.push_back(m_pView->model()->index(iRow, static_cast<int>(Keys::key_Id)).data(Qt::DisplayRole).toInt());
    }

    PolicyMaker* pMaker{new PolicyMaker(vId)};

    connect(pMaker, &PolicyMaker::sendData, m_pView, &TableView::onSetData);

    pMaker->exec();
}

QHBoxLayout* Widget::makePairWidgets(QWidget* pLeftWidget, QWidget* pRightWidget)
{
    QHBoxLayout* pLayout{new QHBoxLayout()};

    if(pLeftWidget != nullptr)
        pLayout->addWidget(pLeftWidget);

    if(pLeftWidget != nullptr)
        pLayout->addWidget(pRightWidget);

    return pLayout;
}

void Widget::initGui()
{
    QVBoxLayout* pMainLayout{new QVBoxLayout()};

    QHBoxLayout* pToolBarlayout{new QHBoxLayout()};

    QVBoxLayout* pLeftToolBarLayout{new QVBoxLayout()};
    QVBoxLayout* pRightToolBarLayout{new QVBoxLayout()};


    pLeftToolBarLayout->addLayout(makePairWidgets(m_pRemoveBtn, m_pRemoveEdit));
    pLeftToolBarLayout->addLayout(makePairWidgets(m_pFindAreaBtn, m_pAreaEdit));
    pLeftToolBarLayout->addLayout(makePairWidgets(m_pFindTermBtn, m_pTermEdit));

    pRightToolBarLayout->addLayout(makePairWidgets(m_pFindMinBtn, m_pFindMaxBtn));
    pRightToolBarLayout->addLayout(makePairWidgets(m_pCreateNewBtn, m_pShowOnePolicyBtn));
    pRightToolBarLayout->addLayout(makePairWidgets(m_pSaveBtn, m_pPieBtn));


    QRegularExpression rx("\\d*");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    m_pRemoveEdit->setValidator(validator);
    m_pAreaEdit->setValidator(validator);

    m_pRemoveEdit->setPlaceholderText(QString::fromLocal8Bit("Номер полиса"));
    m_pAreaEdit->setPlaceholderText(QString::fromLocal8Bit("Площадь дома"));
    m_pTermEdit->setPlaceholderText(QString::fromLocal8Bit("Срок страхования"));

    m_pRemoveEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_pAreaEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_pTermEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);


    pToolBarlayout->addLayout(pLeftToolBarLayout);
    pToolBarlayout->addLayout(pRightToolBarLayout);
    pToolBarlayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    pToolBarlayout->setAlignment(Qt::AlignLeft);

    pMainLayout->addLayout(pToolBarlayout);
    pMainLayout->addWidget(m_pView);


    setLayout(pMainLayout);
}

void Widget::createConnections()
{
    connect(m_pRemoveBtn, SIGNAL(clicked(bool)), this, SLOT(onRemove()));
    connect(m_pCreateNewBtn, SIGNAL(clicked(bool)), this, SLOT(onMakeNewPolicy()));
    connect(m_pSaveBtn, SIGNAL(clicked(bool)), m_pView, SLOT(onSave()));
    connect(m_pShowOnePolicyBtn, SIGNAL(clicked(bool)), this, SLOT(onShowCurrentPolicy()));

    connect(m_pFindMinBtn, SIGNAL(clicked(bool)), this, SLOT(onFindMin()));
    connect(m_pFindMaxBtn, SIGNAL(clicked(bool)), this, SLOT(onFindMax()));

    connect(m_pFindAreaBtn, SIGNAL(clicked(bool)), this, SLOT(onFindArea()));
    connect(m_pFindTermBtn, SIGNAL(clicked(bool)), this, SLOT(onFindTerm()));

    connect(m_pPieBtn, SIGNAL(clicked(bool)), this, SLOT(onShowPie()));

    connect(m_pView, SIGNAL(minValue(int)), this, SLOT(onShowMinValue(int)));
    connect(m_pView, SIGNAL(maxValue(int)), this, SLOT(onShowMaxValue(int)));
}

void Widget::onShowPie()
{
    PieChart* pChart{new PieChart(m_pView->getPieValues())};
    pChart->exec();
}

void Widget::onFindMin()
{
    m_pView->findMin();
}

void Widget::onFindMax()
{
    m_pView->findMax();
}

void Widget::onShowMinValue(int iMinValue)
{
    QString qstrMsg = QString::fromLocal8Bit("Минимальная премия: ") + QString("%1").arg(iMinValue);
    QMessageBox::information(this, QString::fromLocal8Bit("Минимальное значение"), qstrMsg);
}

void Widget::onShowMaxValue(int iMaxValue)
{
    QString qstrMsg = QString::fromLocal8Bit("Максимальная премия: ") + QString("%1").arg(iMaxValue);
    QMessageBox::information(this, QString::fromLocal8Bit("Максимальное значение"), qstrMsg);
}

void Widget::onShowCurrentPolicy()
{
    QModelIndex idx = m_pView->currentIndex();
    if(idx.isValid())
    {
        OnePolicyWidget* pMenu{new OnePolicyWidget()};

        auto pPolicy = m_pView->getPolciyFromIndex(idx);
        int iColumn = 0;

        for(const auto& data : pPolicy->getRowData())
        {
            pMenu->makeDescription(m_pView->getHeaderFromColumn(iColumn), m_pView->getModelData(idx.row(), iColumn));
            ++iColumn;
        }

        m_pView->setCurrentIndex(QModelIndex());
        pMenu->exec();
    }
}

bool Widget::callQuestionRemove(int iId)
{
    QString qstrMsg = QString::fromLocal8Bit("Вы уверены, что хотите удалить ") + QString::number(iId) + QString::fromLocal8Bit(" полис?");

    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("Внимание!"));
    msgBox.setText(qstrMsg);
    QPushButton *yesButton = msgBox.addButton(QString::fromLocal8Bit("Да"), QMessageBox::YesRole);
    QPushButton *noButton = msgBox.addButton(QString::fromLocal8Bit("Нет"), QMessageBox::NoRole);

    msgBox.setDefaultButton(yesButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
        return true;

    return false;
}

void Widget::onRemove()
{
    if(!m_pRemoveEdit->text().isEmpty())
    {
        if(callQuestionRemove(m_pRemoveEdit->text().toInt()))
            m_pView->removeRowById(m_pRemoveEdit->text().toInt());
    }
}

void Widget::findFromValue(QLineEdit* pEdit, Keys key)
{
    if(!pEdit->text().isEmpty())
    {
        if(!m_pView->findFromKey(pEdit->text(), key))
        {
            QString qstrMsg = QString::fromLocal8Bit("Невозможно найти: ") + pEdit->text();
            showMsg(qstrMsg);
        }
    }
}

void Widget::showMsg(const QString& qstrMsg)
{
    QMessageBox::warning(this, QString::fromLocal8Bit("Внимание!"), qstrMsg);
}

void Widget::onFindArea()
{
    QSortFilterProxyModel* proxyModel = static_cast<QSortFilterProxyModel*>(m_pView->model());
    proxyModel->setFilterKeyColumn(static_cast<int>(Keys::key_housingArea));
    proxyModel->setFilterRegularExpression(m_pAreaEdit->text());
    m_pView->setCurrentIndex(QModelIndex());
}

void Widget::onFindTerm()
{
    QSortFilterProxyModel* proxyModel = static_cast<QSortFilterProxyModel*>(m_pView->model());
    proxyModel->setFilterKeyColumn(static_cast<int>(Keys::key_insurancePeriod));
    proxyModel->setFilterRegularExpression(m_pTermEdit->text());
    m_pView->setCurrentIndex(QModelIndex());
}









