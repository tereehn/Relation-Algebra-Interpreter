//
// Created by terez on 27/05/2021.
//

#include <iostream>
#include <algorithm>
#include "CProjectExpression.h"

CProjectExpression::CProjectExpression(std::shared_ptr < CExpression > node,
                                       const std::vector < std::pair < std::string, std::string >> & toPrint): expression(node), toProject(toPrint) {}

std::shared_ptr < CTable > CProjectExpression::evaluate() const {
    std::shared_ptr < CTable > tmpTable = expression -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();
    std::vector < int > columnNums;
    bool isThere = false;

    for (unsigned i = 0; i < toProject.size(); i++) { /// creates header
        newTable -> getHeader().push_back(toProject[i].second);
    }

    for (unsigned i = 0; i < toProject.size(); i++) {
        for (unsigned j = 0; j < tmpTable -> getHeader().size(); j++) {
            if (toProject[i].first == tmpTable -> getHeader()[j]) {
                columnNums.push_back(j); /// push number of columns which will be projected
                isThere = true;
                break; /// print only first that matches column
            }
        }
        if (!isThere) { /// if column is not present throw error
            throw ErrorTreeNodeException("Column does not exist!");
        }
        isThere = false;
    }

    for (unsigned i = 0; i < tmpTable -> rowCount(); i++) {
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > ();
        for (unsigned j = 0; j < columnNums.size(); j++) {
            int tmpNum = columnNums[j];
            std::string word = ( * (tmpTable))[i][tmpNum]; /// only add items from requested columns
            newRow -> pushData(word);
        }
        newTable -> pushData(newRow);
    }

    return newTable;
}

std::string CProjectExpression::toSQL() const {
    std::string toReturn = "SELECT DISTINCT ";

    for (unsigned int i = 0; i < toProject.size(); i++) {
        std::string name = {};
        if (toProject[i].first != toProject[i].second) { /// in case new name was assigned
            name = toProject[i].first + " AS " + toProject[i].second;
        } else {
            name = toProject[i].first;
        }
        if (i == toProject.size() - 1) {
            toReturn += name;
        } else {
            toReturn += name + ",";
        }
    }
    toReturn += "\nFROM ";
    toReturn += expression -> toSQL();
    return toReturn;
}

bool  CProjectExpression::isNested() const {
    return false;
}

int CProjectExpression::relNum() const {
    return 0;
}