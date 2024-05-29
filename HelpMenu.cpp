#include "HelpMenu.h"

const unsigned int c_uWidgth = 20;
const unsigned int c_uHeight = 20;
const unsigned int c_uFont = 10;
const unsigned int c_uWidthWidget = 300;
const unsigned int c_uHeightWidget = 300;




//void MenuOfProgram() {
//    cout << "\t\t\t------------<<<<<<<<< << МЕНЮ ПРОГРАММЫ >> >>>>>>>>>------------" << endl;
//    cout << "\t\t\t+--------------------------------------------------------------+" << endl;
//    cout << "\t\t\t|                                                              |" << endl;
//    cout << "\t\t\t|        1  - Вывод страховых полисов в виде таблицы           |" << endl;
//    cout << "\t\t\t|        2  - Добавление новой записи                          |" << endl;
//    cout << "\t\t\t|        3  - Поиск по запросу                                 |" << endl;
//    cout << "\t\t\t|        4  - Удаление записи                                  |" << endl;
//    cout << "\t\t\t|        5  - Сортировка                                       |" << endl;
//    cout << "\t\t\t|        6  - Процентная соотношение страховых программ        |" << endl;
//    cout << "\t\t\t|        7  - Формирование страховых полисов                   |" << endl;
//    cout << "\t\t\t|        0  - Выход                                            |" << endl;
//    cout << "\t\t\t|                                                              |" << endl;
//    cout << "\t\t\t+--------------------------------------------------------------+" << endl;
//    cout << endl;
//    cout << "Введите необходимый пункт меню >> ";
//}


HelpMenu::HelpMenu(QWidget* pParent)
    : QDialog{pParent}
{
//    hide();
    QVBoxLayout* pMainLayout{new QVBoxLayout()};

    pMainLayout->addLayout(makeDescription("1", "Вывод страховых полисов в виде таблицы"));
    pMainLayout->addLayout(makeDescription("2", "Добавление новой записи "));
    pMainLayout->addLayout(makeDescription("3", "Поиск по запросу"));
    pMainLayout->addLayout(makeDescription("4", "Удаление записи"));
    pMainLayout->addLayout(makeDescription("5", "Сортировка "));
    pMainLayout->addLayout(makeDescription("6", "Процентная соотношение страховых программ "));
    pMainLayout->addLayout(makeDescription("7", "Формирование страховых полисов"));
    pMainLayout->addLayout(makeDescription("0", "Выход"));

    AdjustHelpMenu();

    setLayout(pMainLayout);
}

void HelpMenu::AdjustHelpMenu()
{
    QFont font = this->font();

    font.setPointSize(c_uFont);

    this->setFont(font);

    setWindowTitle(tr("Help"));

    setFixedSize(c_uWidthWidget, c_uHeightWidget);
}

QHBoxLayout* HelpMenu::makePairWidgets(QWidget* pLeftWidget, QWidget* pRightWidget) const
{
    QHBoxLayout* pNewHLayout{new QHBoxLayout()};

    pNewHLayout->addWidget(pLeftWidget);
    pNewHLayout->addWidget(pRightWidget);

    return pNewHLayout;
}

QLabel* HelpMenu::makeInfoLabel(const QVariant& crVar)
{
    QLabel* pLbl{new QLabel()};

    QColor color = crVar.value<QColor>();

    if(color.isValid())
    {
        QPalette palette = pLbl->palette();
        palette.setColor(pLbl->backgroundRole(), color);
        pLbl->setAutoFillBackground(true);
        pLbl->setPalette(palette);
    }
    else
    {
        pLbl->setText(crVar.toString());
    }

    pLbl->setFixedSize(c_uWidgth, c_uHeight);

    pLbl->setAlignment(Qt::AlignCenter);
    pLbl->setFrameStyle(1);

    return pLbl;
}

QLabel* HelpMenu::makeDescriptionLbl(const QString& crQstrTxt) const
{
    QLabel* pLbl = new QLabel(crQstrTxt);
    return pLbl;
}

QHBoxLayout* HelpMenu::makeDescription(const QVariant& crVar, const QString& crQstrTxt)
{
    return makePairWidgets(makeInfoLabel(crVar), makeDescriptionLbl(crQstrTxt));
}
