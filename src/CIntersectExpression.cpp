//
// Created by terez on 27/05/2021.
//

#include "CIntersectExpression.h"

CIntersectExpression::CIntersectExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CSetExpression(left, right) {}

/*!< First evaluates children nodes and then calculates the intersection of two relations */
std::shared_ptr < CTable > CIntersectExpression::evaluate() const {

    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();

    if (!checkTables(rightTable, leftTable)) {
        throw ErrorTreeNodeException("Column do not match!");
    }

    newTable -> getHeader() = rightTable -> getHeader(); /// copy header

    for (unsigned i = 0; i < ( * (leftTable)).rowCount(); i++) {
        CRow tmpLeft = ( * (leftTable))[i];
        std::shared_ptr < CRow > newRow = std::make_shared < CRow > ();

        if (rightTable -> isRowThere(tmpLeft)) { /// add only if row is present in the right table as well
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
            newTable -> pushData(newRow);
        }
    }

    return newTable;
}

std::string CIntersectExpression::toSQL() const {
    std::string toReturn;
    toReturn += leftNode -> toSQL();
    toReturn += "\nINTERSECT\n";
    toReturn += rightNode -> toSQL();
    return toReturn;
}