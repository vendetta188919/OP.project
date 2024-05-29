#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class FileParser
{
public:
    explicit FileParser(const std::string& crStrPathToFile = "");

    unsigned int getRowsCnt() const;
    unsigned int getColumnsCnt() const;
    std::vector<std::vector<std::string> > getAllPolicies() const;

    void saveDataToFile(const std::vector<std::vector<std::string> > &crVecData);

private:
    void loadPoliciesFromFile(const std::string& crStrPathToFile);

private:
    std::vector<std::vector<std::string> > m_vAllPolicies;
    unsigned int m_uColimnCnt;

};
