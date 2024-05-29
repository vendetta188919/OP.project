#pragma once

#include <string>
#include <vector>
#include <map>

enum class Keys
{
    key_Id,                     // ID ������, ��������������� �����.
    key_fullName,               // ������ ��� ��������� ������.
    key_telNumber,              // ����� �������� ���������.
    key_typeOfHouse,            // ��� ����� (��������, ��������=1, ���=2), ��������������� �����.
    key_address,                // ����� ������������������ ������������.

    key_typeOfProperty,         // ��� �������� (���������=1, ����������=2), ��������������� �����.
    key_yearOfConstruction,     // ��� ��������� ������� ������������, ��������������� �����.
    key_housingArea,            // ������� �����, ���������������� �����.
    key_insuranceProgram,       // ��� ��������� ��������� (��������, ������=1, ��������=2, �������=3), ��������������� �����.
    key_insuranceAmount,        // ����� �����������, ���������������� �����.
    key_insurancePremium,       // ��������� ������, ���������������� �����.
    key_insurancePeriod,        // ���� �����������.
    end
};

enum class typeHouse
{
    apartment = 1,
    house,
    end
};

enum class typeProperty
{
    wood = 1,
    stone,
    end
};

enum class typeProgramm
{
    econom = 1,
    standart,
    premium,
    end
};

class Policy
{

public:
    static std::map<Keys, std::string> getTypes();

    Policy();
    bool isValid() const;

    void setDataToColumn(const std::string &crStrData, unsigned int iColumn);
    void setData(const std::vector<std::string>& vData);
    std::string getHeaderFromKey(Keys key) const;
    std::string getDataFromKey(Keys key) const;

    std::vector<std::string> getRowData() const;
private:
    std::vector<std::string> m_vDataRow;
};

