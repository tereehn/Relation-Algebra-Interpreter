//
// Created by terez on 27/05/2021.
//

#include "CTable.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>

CTable::CTable()  {
    srand((unsigned) time(0));
    tableName = std::to_string(rand()); /// sets random name in case no name given
}
CTable::CTable(const std::string & name): tableName(name) {}

CTable::~CTable() {
    for (auto & it: rows) {
        it = nullptr;
    }
}

unsigned int CTable::rowCount(void) const {
    return rows.size();
}

const std::string CTable::getName() const {
    return tableName;
}

void CTable::setName(const std::string & newName) {
    tableName = newName;
}

bool CTable::isRowThere(const CRow & other) const {
    for (auto & it: rows) {
        if ( * it == other) {
            return true;
        }
    }
    return false;
}

CRow & CTable::operator[](unsigned int row) const {
    if (row < rows.size())
        return *(rows[row]);
    throw std::out_of_range("Can't return this row (doesn't exist)!");
}

void CTable::setWidth() {
    for (auto & it: tableHeader) {
        widths.push_back(it.length());
    }

    for (unsigned int i = 0; i < tableHeader.size(); ++i) {
        for (auto & it: rows) {
            std::string tmp = ( * it)[i];
            widths[i] = std::max(tmp.length(), widths[i]); /// change col width, in case of larger string
        }

    }
}

std::ostream & operator << (std::ostream & out, const CTable & input) {

    out << input.getLine(input.style.top);
    out << input.getHeaders(input.tableHeader);
    out << input.getLine(input.style.middle);
    out << input.getRows(input.rows);
    out << input.getLine(input.style.bottom);
    return out;
}

std::vector < std::string > & CTable::getHeader() {
    return tableHeader;
}

const std::vector < std::shared_ptr < CRow >> CTable::getData() const {
    return rows;
}

bool CTable::isEmpty() const {
    return (rowCount() == 0);
}

void CTable::pushData(std::shared_ptr < CRow > newRow) {
    for (auto & it: rows) {
        if ( * it == * newRow) {
            return;
        }
    }
    rows.push_back(newRow);
}

std::string CTable::getLine(rowType row) const {
    std::stringstream line;
    line << row.left;
    for (unsigned int i = 0; i < widths.size(); ++i) {
        for (unsigned int j = 0; j < (widths[i] + padding + padding); ++j) {
            line << style.horizontal;
        }
        line << (i == widths.size() - 1 ? row.right : row.intersect);
    }
    return line.str() + "\n";
}

std::string CTable::getHeaders(std::vector < std::string > tableHeader) const {
    std::stringstream line;
    line << style.vertical;
    for (unsigned int i = 0; i < tableHeader.size(); ++i) {
        std::string text = tableHeader[i];
        line << SPACE_CHARACTER * padding + text + SPACE_CHARACTER * (widths[i] - text.length()) + SPACE_CHARACTER * padding;
        line << style.vertical;
    }
    line << "\n";
    return line.str();
}

std::string CTable::getRows(std::vector < std::shared_ptr < CRow >> rows) const {
    std::stringstream line;
    for (auto & row: rows) {
        line << style.vertical;
        for (unsigned int j = 0; j < row -> dataCount(); ++j) {
            std::string text = ( * row)[j];
            line << SPACE_CHARACTER * padding + text + SPACE_CHARACTER * (widths[j] - text.length()) + SPACE_CHARACTER * padding;
            line << style.vertical;
        }
        line << "\n";
    }
    return line.str();
}

std::string operator * (const std::string & other, int repeats) {
    std::string ret;
    ret.reserve(other.size() * repeats);
    for (; repeats; --repeats)
        ret.append(other);
    return ret;
}

