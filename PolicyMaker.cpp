#include "PolicyMaker.h"

#include <iostream>

#include <QLabel>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QValidator>

#include "Policy.h"

PolicyMaker::PolicyMaker(const std::vector<int> &crVecId, QWidget* pParent)
    : QDialog{pParent},
      m_pCreateBtn{new QPushButton(QString::fromLocal8Bit("�������"))},
      m_pCancelBtn{new QPushButton(QString::fromLocal8Bit("������"))},
      m_vIdPolicy{crVecId}
{
    initGui();
    createConnections();
}

void PolicyMaker::initGui()
{
    QVBoxLayout* pMainLayout{new QVBoxLayout()};

    std::map<Keys, std::string> vTypes = Policy::getTypes();


    QHBoxLayout* pBtnsLayout{new QHBoxLayout()};

    pBtnsLayout->addWidget(m_pCancelBtn);
    pBtnsLayout->addWidget(m_pCreateBtn);


    pMainLayout->addLayout(pBtnsLayout);
    
    for(const auto& crStr : vTypes)
    {
        pMainLayout->addLayout(makePairWidgets(QString::fromStdString(crStr.second), crStr.first));
    }

    setWindowFilePath(QString::fromLocal8Bit("�������� ������ ������"));

    setLayout(pMainLayout);
}

void PolicyMaker::createConnections()
{
    connect(m_pCreateBtn, SIGNAL(clicked(bool)), this, SLOT(onCreate()));
    connect(m_pCancelBtn, SIGNAL(clicked(bool)), this, SLOT(onClose()));
}



QHBoxLayout* PolicyMaker::makePairWidgets(const QString& crQstrDescription, Keys key)
{

    QHBoxLayout* pLayout{new QHBoxLayout()};

    QWidget* pNewWidget = makeRedactorWidget(key);

    m_vWidgets.push_back({pNewWidget, key});

    pLayout->addWidget(new QLabel(crQstrDescription));
    pLayout->addWidget(pNewWidget);

    return pLayout;
}

void PolicyMaker::onClose()
{
    close();
}

void PolicyMaker::onCreate()
{
    bool bUnique{true};
    int iUniqueId{0};

    std::vector<std::string> vRes;
    for(const auto& pair : m_vWidgets)
    {
        if(pair.second == Keys::key_Id)
        {
            QLineEdit* pLineEdit = static_cast<QLineEdit*>(pair.first);
            for(const auto& iId : m_vIdPolicy)
            {
                if(iId == pLineEdit->text().toInt())
                {
                    iUniqueId = iId;
                    bUnique = false;
                }
            }
            vRes.push_back(pLineEdit->text().toStdString());
        }
        else if(pair.second == Keys::key_insuranceProgram ||
                pair.second == Keys::key_typeOfProperty ||
                pair.second == Keys::key_typeOfHouse)
        {
            QComboBox* pEditBox = static_cast<QComboBox*>(pair.first);
            vRes.push_back(pEditBox->currentData().toString().toStdString());
        }
        else
        {
            QLineEdit* pLineEdit = static_cast<QLineEdit*>(pair.first);
            vRes.push_back(pLineEdit->text().toStdString());
        }
    }

    if(bUnique)
    {
        bool bEmptyValue{false};
        for(const auto& strData : vRes)
        {
            if(strData.empty())
            {
                bEmptyValue = true;
                QMessageBox::warning(this, QString::fromLocal8Bit("��������!"), QString::fromLocal8Bit("�������� �� ����� ���� �������!"));
                break;
            }
        }

        if(!bEmptyValue)
        {
            emit sendData(vRes);
            close();
        }
    }
    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("��������!"), QString::fromLocal8Bit("���������� �������.\n"
                                                 "����� ������ ") + QString("%1").arg(iUniqueId) + QString::fromLocal8Bit(" �� ����������."));
    }
}

std::string PolicyMaker::getRegExp(Keys key) const
{
    std::string strRegExp;
    switch(key)
    {
    case Keys::key_Id:
    {
        strRegExp = "[0-9]+";
        break;
    }
    case Keys::key_fullName:
    {
        strRegExp = "^[A-Z\u0410-\u042F\u0401][a-z\u0430-\u044F\u0451]+\\s[A-Z\u0410-\u042F]\\.[A-Z\u0410-\u042F]\\.&";
        break;
    }
    case Keys::key_telNumber:
    {
        strRegExp = "[0-9]+";
        break;
    }
    case Keys::key_typeOfHouse:
    {
        strRegExp = "[1-2]";
        break;
    }
    case Keys::key_address:
    {
        strRegExp = "";
        break;
    }
    case Keys::key_typeOfProperty:
    {
        strRegExp = "[1-2]";
        break;
    }
    case Keys::key_yearOfConstruction:
    {
        strRegExp = "[\\d]{4}";
        break;
    }
    case Keys::key_housingArea:
    {
        strRegExp = "[0-9]+";
        break;
    }
    case Keys::key_insuranceProgram:
    {
        strRegExp = "[0-9]+";
        break;
    }
    case Keys::key_insurancePeriod:
    {
        strRegExp = "[0-9]+\\s[\\D]+";
        break;
    }
    case Keys::key_insurancePremium:
    {
        strRegExp = "[0-9]+";
        break;
    }
    case Keys::key_insuranceAmount:
    {
        strRegExp = "[0-9]+";
        break;
    }
    default:
        break;
    }

    return strRegExp;
}

QWidget* PolicyMaker::makeRedactorWidget(Keys key)
{
    switch(key)
    {
    case Keys::key_typeOfHouse:
    {
        return makeComboBox(key);
    }
    case Keys::key_typeOfProperty:
    {
        return makeComboBox(key);
    }
    case Keys::key_insuranceProgram:
    {
        return makeComboBox(key);
    }
    default:
        return makeLineEdit(key);
    }
}

QWidget* PolicyMaker::makeLineEdit(Keys key)
{
    QLineEdit* pEdit{new QLineEdit()};

    std::string strRegExp = getRegExp(key);

    if(!strRegExp.empty())
    {
        QRegularExpression rx(QString::fromStdString(strRegExp));
        QValidator* validator = new QRegularExpressionValidator(rx, this);
        pEdit->setValidator(validator);
    }

    return pEdit;
}

QWidget* PolicyMaker::makeComboBox(Keys key)
{
    QComboBox* pEdit{new QComboBox()};

    std::vector<QString> vTypes = getDescriptionsBox(key);

    if(!vTypes.empty())
    {
        int iCnt{1};
        for(const auto& type : vTypes)
        {
            pEdit->addItem(type, iCnt);
            ++iCnt;
        }
    }

    return pEdit;
}

std::vector<QString> PolicyMaker::getDescriptionsBox(Keys key) const
{
    std::vector<QString> vRes;

    switch(key)
    {
    case Keys::key_typeOfHouse:
    {
        vRes.push_back(QString::fromLocal8Bit("��������")); /// 1
        vRes.push_back(QString::fromLocal8Bit("���")); /// 2
        break;
    }
    case Keys::key_typeOfProperty:
    {
        vRes.push_back(QString::fromLocal8Bit("����������")); /// 1
        vRes.push_back(QString::fromLocal8Bit("��������")); /// 2
        break;
    }
    case Keys::key_insuranceProgram:
    {
        vRes.push_back(QString::fromLocal8Bit("������"));    /// 1
        vRes.push_back(QString::fromLocal8Bit("��������"));  /// 2
        vRes.push_back(QString::fromLocal8Bit("�������"));   /// 3
    }
    default:
        break;
    }

    return vRes;
}
