#include "Model.h"

Model::Model(QObject* pParent)
    : QAbstractTableModel{pParent},
      m_Parser{new FileParser()}
{
    loadData();
}

int Model::rowCount(const QModelIndex&) const
{
    return m_ValuesAllRows.count();
}

int Model::columnCount(const QModelIndex&) const
{
    return m_Parser->getColumnsCnt();
}

QVariant Model::data(const QModelIndex& crIndex, int iRole) const
{
    QVariant returnValue;

    if(crIndex.isValid())
    {
        Keys key = static_cast<Keys>(crIndex.column());

        switch (iRole)
        {
        case Qt::DisplayRole:
        {
            returnValue = getDisplayNameForType(key, data(crIndex,  Qt::EditRole).toInt()).first;

            if(returnValue.toString().isEmpty())
                returnValue = QString::fromStdString(m_ValuesAllRows.at(crIndex.row())->getDataFromKey(key));

            break;
        }
        case Qt::EditRole:
        {
            returnValue = QString::fromStdString(m_ValuesAllRows.at(crIndex.row())->getDataFromKey(key));
            break;
        }
        case Qt::UserRole:
        {
            std::string strData = m_ValuesAllRows.at(crIndex.row())->getDataFromKey(key);

            try
            {
                returnValue = std::stoi(strData);
            }
            catch(std::invalid_argument&)
            {
                returnValue = QString::fromStdString(strData);
            }
            catch(std::out_of_range&)
            {
                returnValue = QString::fromStdString(strData);
            }
            break;
        }
        default:
            break;
        }
    }


    return returnValue;
}

void Model::insertRow(const std::vector<std::string>& crVecNewData, int, const QModelIndex &)
{
    beginResetModel();

    Policy* policy{new Policy()};
    policy->setData(crVecNewData);
    m_ValuesAllRows.append(policy);

    endResetModel();
}

void Model::saveData()
{
    std::vector<std::vector<std::string> > vOutData;

    for(const auto& crPolicy : m_ValuesAllRows)
    {
        vOutData.push_back(crPolicy->getRowData());
    }

    m_Parser->saveDataToFile(vOutData);
}

std::vector<std::pair<QString, unsigned int> > Model::getPieValues()
{
    std::vector<std::pair<QString, unsigned int> > vecValues;

    for(int iRow{0}; iRow < rowCount(); ++iRow)
    {
        QString qstrType = getTypeProgramm(this->index(iRow, static_cast<int>(Keys::key_insuranceProgram)).data(Qt::EditRole).toInt());
        std::vector<std::pair<QString, unsigned int> >::iterator it = std::find_if(vecValues.begin(), vecValues.end(), [&](const std::pair<QString, unsigned int>& crPair){
            return crPair.first == qstrType;
        });

        if(it == vecValues.end())
        {
            vecValues.push_back({qstrType, 0});
        }
        else
        {
            it->second++;
        }
    }

    return vecValues;
}

QString Model::getTypeProgramm(unsigned int uType)
{
    switch(uType)
    {
    case 1:
    {
        return QString(QString::fromLocal8Bit("Эконом"));
    }
    case 2:
    {
        return QString(QString::fromLocal8Bit("Стандарт"));
    }
    case 3:
    {
        return QString(QString::fromLocal8Bit("Премиум"));
    }
    default:
        return QString("");
    }
}

bool Model::setData(const QModelIndex& index, const QVariant& rValue, int iRole)
{
    if(index.isValid() && iRole == Qt::EditRole)
    {
        if(!rValue.toString().isEmpty())
        {
            m_ValuesAllRows.at(index.row())->setDataToColumn(rValue.toString().toStdString(), index.column());
            emit dataChanged(index, index);
            return true;
        }
    }

    return false;
}

bool Model::removeRow(int iRow, const QModelIndex &)
{
    beginResetModel();
    m_ValuesAllRows.removeAt(iRow);
    endResetModel();
    return true;
}

bool Model::removeFromPolicyId(int iId)
{
    beginResetModel();

    auto it = std::find_if(m_ValuesAllRows.begin(), m_ValuesAllRows.end(), [&](Policy* poloicyRow){
            return poloicyRow->getDataFromKey(Keys::key_Id) == std::to_string(iId);
});

    if(it != m_ValuesAllRows.end())
        m_ValuesAllRows.erase(it);
    else
        return false;

    endResetModel();
    return true;
}

QModelIndex Model::findFromKey(const QString& crQstrData, Keys key)
{
    for(int iRow{0}; iRow < rowCount(); ++iRow)
    {
        QModelIndex idx = this->index(iRow, static_cast<int>(key));
        QString qstrData = idx.data(Qt::DisplayRole).toString();

        qstrData.replace('\r',"");

        if(qstrData == crQstrData)
            return idx;
    }

    return QModelIndex();
}

void Model::findMin()
{
    std::vector<int> vPremiumValues;

    for(const auto& policy : m_ValuesAllRows)
    {
        vPremiumValues.push_back(std::atoi(policy->getDataFromKey(Keys::key_insurancePremium).c_str()));
    }

    auto it = std::min_element(vPremiumValues.begin(), vPremiumValues.end());

    if(it != vPremiumValues.end())
        emit minValue(*it);
}

void Model::findMax()
{
    std::vector<int> vPremiumValues;
    for(const auto& policy : m_ValuesAllRows)
    {
        vPremiumValues.push_back(std::atoi(policy->getDataFromKey(Keys::key_insurancePremium).c_str()));
    }

    auto it = std::max_element(vPremiumValues.begin(), vPremiumValues.end());

    if(it != vPremiumValues.end())
        emit maxValue(*it);
}

QVariant Model::headerData(int iSection, Qt::Orientation orientation, int iRole) const
{
    QVariant returnValue;

    switch (iRole)
    {
    case Qt::DisplayRole:
    {
        if(orientation == Qt::Horizontal)
        {
            returnValue = QString::fromStdString(m_ValuesAllRows.front()->getHeaderFromKey(static_cast<Keys>(iSection)));
        }
        else
            return QVariant();
        break;
    }
    default:
    {
        return QVariant();
    }
    }

    return returnValue;
}

Qt::ItemFlags Model::flags(const QModelIndex& crIndex) const
{
    if(!crIndex.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(crIndex);
}

void Model::loadData()
{
    std::vector<std::vector<std::string> > vData = m_Parser->getAllPolicies();

    for(const auto& vPolicy : vData)
    {
        Policy* policy{new Policy()};
        policy->setData(vPolicy);
        m_ValuesAllRows.append(policy);
    }
}

Policy* Model::getPolciyFromIndex(const QModelIndex& crIdx)
{
    if(crIdx.isValid())
        return m_ValuesAllRows.at(crIdx.row());
    return new Policy();
}


std::pair<QString,int> Model::getDisplayNameForType(Keys key, unsigned int iValueType) const
{
    switch(key)
    {
    case Keys::key_typeOfHouse:
    {
        switch(static_cast<typeHouse>(iValueType))
        {
        case typeHouse::house:
        {
            return {QString(QString::fromLocal8Bit("Квартира")), 1};
        }
        case typeHouse::apartment:
        {
            return {QString(QString::fromLocal8Bit("Дом")), 2};
        }
        default:
            break;
        }
        break;
    }
    case Keys::key_typeOfProperty:
    {
        switch(static_cast<typeProperty>(iValueType))
        {
        case typeProperty::wood:
        {
            return {QString(QString::fromLocal8Bit("Деревянный")), 1};
        }
        case typeProperty::stone:
        {
            return {QString(QString::fromLocal8Bit("Каменный")), 2};
        }
        default:
            break;
        }
        break;
    }
    case Keys::key_insuranceProgram:
    {
        switch(static_cast<typeProgramm>(iValueType))
        {
        case typeProgramm::econom:
        {
            return {QString(QString::fromLocal8Bit("Эконом")), 1};
        }
        case typeProgramm::standart:
        {
            return {QString(QString::fromLocal8Bit("Стандарт")), 2};
        }
        case typeProgramm::premium:
        {
            return {QString(QString::fromLocal8Bit("Премиум")), 3};
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    return {QString(),-1};
}
















