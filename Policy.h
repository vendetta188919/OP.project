#pragma once

#include <string>
#include <vector>
#include <map>

enum class Keys
{
    key_Id,                     // ID полиса, инициализирован нулем.
    key_fullName,               // Полное имя владельца полиса.
    key_telNumber,              // Номер телефона владельца.
    key_typeOfHouse,            // Тип жилья (например, квартира=1, дом=2), инициализирован нулем.
    key_address,                // Адрес зарегистрированной недвижимости.

    key_typeOfProperty,         // Тип свойства (кирпичное=1, деревянное=2), инициализирован нулем.
    key_yearOfConstruction,     // Год постройки объекта недвижимости, инициализирован нулем.
    key_housingArea,            // Площадь жилья, инициализирована нулем.
    key_insuranceProgram,       // Тип страховой программы (например, Эконом=1, Стандарт=2, Премиум=3), инициализирован нулем.
    key_insuranceAmount,        // Сумма страхования, инициализирована нулем.
    key_insurancePremium,       // Страховая премия, инициализирована нулем.
    key_insurancePeriod,        // Срок страхования.
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

