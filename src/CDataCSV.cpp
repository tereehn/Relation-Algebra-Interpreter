//
// Created by terez on 27/05/2021.
//

#include "CDataCSV.h"

#include <filesystem>

#include <fstream>

#include <iostream>

CDataCSV::CDataCSV(const std::string & load): CData(load) {}

bool CDataCSV::tryLoading() {
    if (!(std::filesystem::is_directory(src)) || std::filesystem::is_empty(src)) { /// check is directory is valid and reachable
        return false;
    }
    for (const auto & entry: std::filesystem::directory_iterator(src)) {
        filesToOpen.push_back(std::make_pair(entry.path().filename().string(), entry.path().string()));
    }
    return true;
}

void CDataCSV::LoadTables() {

    for (auto & it: filesToOpen) {
        std::string tableName = it.first;
        std::string toErase = ".csv";

        size_t pos = tableName.find(toErase); /// remove the csv suffix
        if (pos != std::string::npos) {
            tableName.erase(pos, toErase.length());
        } else {
            throw ErrorLoadingDataException("Contains files different from .csv!"); /// directory must contain only csv files
        }
        std::shared_ptr < CTable > tmpTable = std::make_shared < CTable > (tableName);
        SaveOne(it.second, tmpTable); /// save path to a file to the vector
        savedData.insert(std::make_pair(tableName, tmpTable));
    }
    if (savedData.empty()) { /// no data were found
        throw ErrorLoadingDataException("No data found!");
    }
}

/*! Writes csv files to table, controls string with double quotes and splits them correctly . */
void CDataCSV::SaveOne(const std::string & fileName, std::shared_ptr < CTable > & tmpTable) {
    std::string headerLine, item, dataLine;
    std::ifstream openFile(fileName);
    if (!openFile) { /// checks if file exist
        throw ErrorLoadingDataException("File does not exist!");
    }

    if (!getline(openFile, headerLine)) { /// file contains no data
        throw ErrorLoadingDataException("Header is not present!");
    }
    std::stringstream ss(headerLine);

    while (std::getline(ss, item, delimiter)) {
        tmpTable -> getHeader().push_back(item);
    }

    unsigned int neededCount = tmpTable -> getHeader().size();
    while (std::getline(openFile, dataLine)) {

        std::vector < std::string > tmp {""};
        CSVState state = CSVState::UnquotedField;
        unsigned int i = 0;

        for (char c: dataLine) {
            switch (state) {
                case CSVState::UnquotedField:
                    switch (c) {
                        case ',':
                            tmp.push_back("");
                            i++;
                            break;
                        case '"':
                            state = CSVState::QuotedField;
                            break;
                        default:
                            tmp[i].push_back(c);
                            break;
                    }
                    break;
                case CSVState::QuotedField:
                    switch (c) {
                        case '"':
                            state = CSVState::QuotedQuote;
                            break;
                        default:
                            tmp[i].push_back(c);
                            break;
                    }
                    break;
                case CSVState::QuotedQuote:
                    switch (c) {
                        case ',':
                            tmp.push_back("");
                            i++;
                            state = CSVState::UnquotedField;
                            break;
                        case '"':
                            tmp[i].push_back('"');
                            state = CSVState::QuotedField;
                            break;
                        default:
                            state = CSVState::UnquotedField;
                            break;
                    }
                    break;
            }
        }
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmp);
        tmpTable -> pushData(newRow);

        if (newRow -> dataCount() != neededCount) { /// number of columns must be the same
            throw ErrorLoadingDataException("Invalid csv file!");
        }
    }

    openFile.close();
}