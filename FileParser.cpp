#include "FileParser.h"

#include <stdexcept>

using namespace std;

const unsigned int c_uMaxRowCnt = 100;

std::string get_path_to_file()
{
    return "C:\\Users\\MSI\\Desktop\\project.op.qt\\src\\PPolic.txt";
}

FileParser::FileParser(const string& crStrPathToFile)
    : m_uColimnCnt{0}
{
    std::string strPathToFile{ crStrPathToFile };

    if(strPathToFile.empty())
        strPathToFile = get_path_to_file();

    loadPoliciesFromFile(strPathToFile);
}

unsigned int FileParser::getRowsCnt() const
{
    return m_vAllPolicies.size();
}

unsigned int FileParser::getColumnsCnt() const
{
    return m_uColimnCnt;
}

std::vector<std::vector<string> > FileParser::getAllPolicies() const
{
    return m_vAllPolicies;
}

void FileParser::saveDataToFile(const std::vector<std::vector<std::string> > &crVecData)
{
    std::ofstream outFile;
    outFile.open(get_path_to_file());

    if(outFile.is_open())
    {
        for(const auto& vRowData : crVecData)
        {
            std::string strOut;
            bool bFirst{true};
            for(const auto& strData : vRowData)
            {
                if(bFirst)
                {
                    strOut += strData;
                    bFirst = false;
                    continue;
                }
                strOut += "," + strData;
            }
            outFile << strOut  << std::endl;
        }
    }
    outFile.close();
}

void FileParser::loadPoliciesFromFile(const string& crStrPathToFile)
{
    ifstream file(crStrPathToFile);

    string line;
    unsigned int iCntPolicies = 0;

    while (getline(file, line) && iCntPolicies < c_uMaxRowCnt)
    {
        std::vector<std::string> vDataPolicy;

        stringstream ss(line);
        string strData;

        while(getline(ss, strData, ','))
        {
            vDataPolicy.push_back(strData);
        }

        if(m_uColimnCnt < static_cast<unsigned int>(vDataPolicy.size()))
            m_uColimnCnt = static_cast<unsigned int>(vDataPolicy.size());

        m_vAllPolicies.push_back(vDataPolicy);
        ++iCntPolicies;
    }
}
