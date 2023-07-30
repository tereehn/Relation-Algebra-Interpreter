//
// Created by terez on 27/05/2021.
//

#include <iostream>

#include "CJoinExpression.h"

CJoinExpression::CJoinExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right, bool isNested): CJoin(left, right),nested(isNested) {}

void CJoinExpression::makeHeader(std::shared_ptr < CTable > & newTable, std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const {
    for (unsigned i = 0; i < leftTable -> getHeader().size(); i++) {
        newTable -> getHeader().push_back(leftTable -> getHeader()[i]);
    }
    for (unsigned i = 0; i < rightTable -> getHeader().size(); i++) {
        if (i == rightCol) continue; /// don't add the same column twice
        newTable -> getHeader().push_back(rightTable -> getHeader()[i]);
    }

}

bool CJoinExpression::findCommon(std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const {

    for (unsigned i = 0; i < leftTable -> getHeader().size(); i++) {
        for (unsigned j = 0; j < rightTable -> getHeader().size(); j++) {
            if (leftTable -> getHeader()[i] == rightTable -> getHeader()[j]) { /// find common attribute
                leftCol = i;
                rightCol = j;
                return true;
            }
        }
    }
    return false; /// common attribute not found
}

std::shared_ptr < CTable > CJoinExpression::evaluate() const {
    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();

    if (!findCommon(leftTable, rightTable)) {
        throw ErrorTreeNodeException("No common attribute!");
    }
    makeHeader(newTable, leftTable, rightTable);
    joinTables(newTable, leftTable, rightTable);

    return newTable;
}

std::string CJoinExpression::toSQL() const {
    std::string toReturn;
    if (leftNode->isNested()){
        toReturn += "( SELECT DISTINCT *\n";
        toReturn += "FROM "+leftNode -> toSQL();
        toReturn += ") R"+std::to_string(leftNode->relNum());
    }else {
        toReturn += leftNode -> toSQL();
    }
    toReturn += "\nNATURAL JOIN\n";
    if (rightNode->isNested()){
        toReturn += "(SELECT DISTINCT *\n";
        toReturn += "FROM "+rightNode -> toSQL();
        //toReturn += ") R\n";
        if (leftNode->relNum() == rightNode->relNum()){
            toReturn += ") R"+std::to_string(rightNode->relNum()+1);
        }else {
            toReturn += ") R"+std::to_string(rightNode->relNum());
        }
    }else {
        toReturn += rightNode -> toSQL();
    }

    return toReturn;
}

bool CJoinExpression::isNested() const {
    return (leftNode->isNested() && rightNode->isNested());
}

int CJoinExpression::relNum() const {
    return (std::max(leftNode->relNum(), rightNode->relNum()+1));
}