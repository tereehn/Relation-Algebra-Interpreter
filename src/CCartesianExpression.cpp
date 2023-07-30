//
// Created by terez on 27/05/2021.
//

#include "CCartesianExpression.h"

#include <iostream>

CCartesianExpression::CCartesianExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CBinaryExpression(left, right) {}

/*!< First evaluates children nodes and then calculates the cartesian product */

std::shared_ptr < CTable > CCartesianExpression::evaluate() const {

    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();
    makeHeader(leftTable, rightTable, newTable);

    for (unsigned i = 0; i < leftTable -> rowCount(); i++) {
        CRow tmpLeft = ( * (leftTable))[i]; /// copy row of left table
        for (unsigned j = 0; j < rightTable -> rowCount(); j++) {
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
            CRow tmpRight = ( * (rightTable))[j];
            newRow -> appendData(tmpRight.getValues()); /// append row of the right table to the left one
            newTable -> pushData(newRow);
        }
    }

    return newTable;
}

void CCartesianExpression::makeHeader(std::shared_ptr < CTable > left, std::shared_ptr < CTable > right, std::shared_ptr < CTable > & newTable) const {

    for (unsigned i = 0; i < left -> getHeader().size(); i++) {
        newTable -> getHeader().push_back(left -> getHeader()[i]);
    }

    bool dup = false;
    for (unsigned i = 0; i < right -> getHeader().size(); i++) {
        std::string tmpRight = right -> getHeader()[i];
        for (unsigned j = 0; j < newTable -> getHeader().size(); j++) {
            std::string tmp = newTable -> getHeader()[j];
            /// in case of duplicates, combine name of table to column name
            if (tmp == tmpRight) {
                newTable -> getHeader()[j] = left -> getName() + +"." + newTable -> getHeader()[j];
                newTable -> getHeader().push_back(right -> getName() + "." + tmpRight);
                dup = true;
                break;
            }
        }
        if (!dup) {
            newTable -> getHeader().push_back(tmpRight);
        }
        dup = false;
    }
}

std::string CCartesianExpression::toSQL() const {
    std::string toReturn;
    toReturn += leftNode -> toSQL();
    toReturn += "\nCROSS JOIN\n";
    toReturn += rightNode -> toSQL();
    return toReturn;
}

bool CCartesianExpression::isNested() const {
    return false;
}

int CCartesianExpression::relNum() const {
    return 0;
}