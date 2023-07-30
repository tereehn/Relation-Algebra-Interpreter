//
// Created by terez on 27/05/2021.
//

#include "CUnionExpression.h"

CUnionExpression::CUnionExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CSetExpression(left, right) {}

std::shared_ptr < CTable > CUnionExpression::evaluate() const {
    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();

    if (!checkTables(rightTable, leftTable)) {
        throw ErrorTreeNodeException("Column do not match!");
    }

    newTable -> getHeader() = rightTable -> getHeader();

    for (unsigned i = 0; i < ( * (leftTable)).rowCount(); i++) {
        CRow tmpLeft = ( * (leftTable))[i];
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
        newTable -> pushData(newRow);
    }

    for (unsigned i = 0; i < ( * (rightTable)).rowCount(); i++) {
        CRow tmpRight = ( * (rightTable))[i];
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpRight);
        newTable -> pushData(newRow);
    }

    return newTable;
}

std::string CUnionExpression::toSQL() const {
    std::string toReturn;
    toReturn += rightNode -> toSQL();
    toReturn += "\nUNION\n";
    toReturn += leftNode -> toSQL();
    return toReturn;
}