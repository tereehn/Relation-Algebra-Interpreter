//
// Created by terez on 27/05/2021.
//

#include "CJoinOnExpression.h"
#include <algorithm>
#include <iostream>

CJoinOnExpression::CJoinOnExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right,
                                     const std::string & leftString,
                                     const std::string & rightString) : CJoin(left, right), leftString(leftString), rightString(rightString) {}

void CJoinOnExpression::makeHeader(std::shared_ptr < CTable > & newTable, std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const {
    for (unsigned i = 0; i < leftTable -> getHeader().size(); i++) {
        newTable -> getHeader().push_back(leftTable -> getHeader()[i]);
    }
    for (unsigned i = 0; i < rightTable -> getHeader().size(); i++) {
        if (i == rightCol && (rightTable -> getHeader()[rightCol] == leftTable -> getHeader()[leftCol])) continue;
        newTable -> getHeader().push_back(rightTable -> getHeader()[i]);
    }
}

bool CJoinOnExpression::findCommon(std::shared_ptr < CTable > left, std::shared_ptr < CTable > right) const {
    bool leftFound = false, rightFound = false;
    for (unsigned i = 0; i < left -> getHeader().size(); i++) { /// find joining column on left side
        if (left -> getHeader()[i] == leftString) {
            leftCol = i;
            leftFound = true;
            break;
        }
    }
    for (unsigned i = 0; i < right -> getHeader().size(); i++) { /// find joining column on right side
        if (right -> getHeader()[i] == rightString) {
            rightCol = i;
            rightFound = true;
            break;
        }
    }
    return (rightFound && leftFound);
}

std::shared_ptr < CTable > CJoinOnExpression::evaluate() const {
    std::shared_ptr < CTable > rightTable = rightNode -> evaluate();
    std::shared_ptr < CTable > leftTable = leftNode -> evaluate();
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();

    if (!findCommon(leftTable, rightTable)) {
        throw ErrorTreeNodeException("Common attribute not found!");
    }
    makeHeader(newTable, leftTable, rightTable);
    joinTables(newTable, leftTable, rightTable);

    return newTable;
}

std::string CJoinOnExpression::toSQL() const {
    std::string toReturn, leftSide, rightSide;
    if (leftNode->isNested()){
        toReturn += "( SELECT DISTINCT *\n";
        toReturn += "FROM "+leftNode -> toSQL();
        toReturn += ") R"+std::to_string(leftNode->relNum());
        leftSide = "R"+std::to_string(leftNode->relNum());
    }else {
        toReturn += leftNode -> toSQL();
        leftSide = leftNode -> toSQL();
    }
    toReturn += "\nJOIN\n";
    if (rightNode->isNested()){
        toReturn += "(SELECT DISTINCT *\n";
        toReturn += "FROM "+rightNode -> toSQL();
        //toReturn += ") R\n";
        if (leftNode->relNum() == rightNode->relNum()){
            toReturn += ") R"+std::to_string(rightNode->relNum()+1);
            rightSide = "R"+std::to_string(rightNode->relNum()+1);
        }else {
            toReturn += ") R"+std::to_string(rightNode->relNum());
            rightSide = "R"+std::to_string(rightNode->relNum());
        }
    }else {
        toReturn += rightNode -> toSQL();
        rightSide = rightNode -> toSQL();
    }
    toReturn += " ON " + leftSide+"."+leftString+"="+rightSide+"."+rightString;
    return toReturn;
}

bool  CJoinOnExpression::isNested() const {
    return true;
}

int CJoinOnExpression::relNum() const {
    return (std::max(leftNode->relNum(), rightNode->relNum()+1));
}