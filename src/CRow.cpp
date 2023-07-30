//
// Created by terez on 27/05/2021.
//

#include <stdexcept>
#include "CRow.h"
#include "iostream"

CRow::CRow(std::vector < std::string > & oneRow): values(oneRow) {}

CRow::~CRow() {

}

void CRow::appendData(const std::vector < std::string > & newValues) {
    values.insert(values.end(), newValues.begin(), newValues.end());
}

void CRow::pushData(const std::string & data) {
    values.push_back(data);
}

unsigned int CRow::dataCount(void) const {
    return values.size();
}

bool CRow::operator == (const CRow & another) const {
    if (values == another.getValues()) {
        return true;
    }
    return false;
}

const std::string CRow::operator[](unsigned int index) const {
    if (index < this -> dataCount()) {
        return values[index];
    }
    throw std::out_of_range("Column does not exist!");
}

const std::vector < std::string > CRow::getValues() const {
    return values;
}
