//
// Created by terez on 27/05/2021.
//

#include "CDiffExpression.h"

CDiffExpression::CDiffExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CSetExpression(left, right) {}

/*!< First evaluates children nodes and then calculates the difference of two relations */

std::shared_ptr < CTable > CDiffExpression::evaluate() const {
    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();

    if (!checkTables(rightTable, leftTable)) {
        throw ErrorTreeNodeException("Column do not match!");
    }

    newTable -> getHeader() = rightTable -> getHeader(); /// copy header

    for (unsigned i = 0; i < leftTable -> rowCount(); i++) {

        CRow tmpLeft = ( * (leftTable))[i];
        if (!rightTable -> isRowThere(tmpLeft)) { /// add row only if it is not present in right table
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
            newTable -> pushData(newRow);
        }
    }

    return newTable;
}

std::string CDiffExpression::toSQL() const {
    std::string toReturn;
    toReturn += leftNode -> toSQL();
    toReturn += "\nMINUS\n";
    toReturn += rightNode -> toSQL();
    return toReturn;
}