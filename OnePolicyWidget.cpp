#include "OnePolicyWidget.h"

const unsigned int c_uWidgth = 40;
const unsigned int c_uHeight = 40;
const unsigned int c_uFont = 20;
const unsigned int c_uWidthWidget = 500;
const unsigned int c_uHeightWidget = 500;

OnePolicyWidget::OnePolicyWidget(QWidget* pParent)
    : QDialog{pParent}
{
    QVBoxLayout* pMainLayout{new QVBoxLayout()};

    AdjustHelpMenu();

    setLayout(pMainLayout);
}

void OnePolicyWidget::AdjustHelpMenu()
{
    QFont font = this->font();

    this->setFont(font);

    setWindowTitle(tr("Формирование полиса"));
}

QHBoxLayout* OnePolicyWidget::makePairWidgets(QWidget* pLeftWidget, QWidget* pRightWidget) const
{
    QHBoxLayout* pNewHLayout{new QHBoxLayout()};

    pNewHLayout->addWidget(pLeftWidget);
    pNewHLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    pNewHLayout->addWidget(pRightWidget);

    return pNewHLayout;
}

QLabel* OnePolicyWidget::makeInfoLabel(const QVariant& crVar)
{
    QLabel* pLbl{new QLabel()};
    pLbl->setText(crVar.toString());
    pLbl->setAlignment(Qt::AlignLeft);
    return pLbl;
}

QLabel* OnePolicyWidget::makeDescriptionLbl(const QString& crQstrTxt) const
{
    QLabel* pLbl = new QLabel(crQstrTxt);
    pLbl->setAlignment(Qt::AlignLeft);
    return pLbl;
}

void OnePolicyWidget::makeDescription(const QVariant& crVar, const QString& crQstrTxt)
{
    static_cast<QVBoxLayout*>(this->layout())->addLayout(makePairWidgets(makeInfoLabel(crVar), makeDescriptionLbl(crQstrTxt)));
}
