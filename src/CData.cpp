//
// Created by terez on 27/05/2021.
//

#include "CData.h"
#include <fstream>

void CData::writeToCsv(const std::string & filename, std::shared_ptr < CTable > tableToExport) const {

    std::ofstream myFile(filename + ".csv");
    if (!myFile.is_open()) {
        throw ErrorLoadingDataException("Error writing into the file!");
    }

    /// write header
    for (auto it = tableToExport -> getHeader().begin(); it != tableToExport -> getHeader().end(); ++it) {
        if ((it + 1) == tableToExport -> getHeader().end()) {
            myFile << * it;
        } else {
            myFile << * it << delimiter;
        }
    }

    myFile << "\n";

    /// write data
    for (unsigned int i = 0; i < tableToExport -> getData().size(); ++i) {
        CRow tmpRow = * tableToExport -> getData()[i];
        std::vector < std::string > tmpValues = tmpRow.getValues();
        for (auto it = tmpValues.begin(); it != tmpValues.end(); ++it) {
            if ((it + 1) == tmpValues.end()) {
                myFile << * it;
            } else {
                myFile << * it << delimiter;
            }
        }
        myFile << "\n";
    }
    myFile.close(); /// close just created file
}

void CData::appendData(const std::string & tableName, std::shared_ptr < CTable > newTable) {
    newTable -> setName(tableName);
    savedData[tableName] = newTable;
}
void CData::removeData(const std::string & tableName) { /// table to be removed
    savedData.erase(tableName);
}

const std::map < std::string, std::shared_ptr < CTable >> & CData::getData() const {
    return savedData;
}