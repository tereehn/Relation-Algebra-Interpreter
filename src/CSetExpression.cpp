//
// Created by terez on 27/05/2021.
//

#include "CSetExpression.h"

CSetExpression::CSetExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right): CBinaryExpression(left, right) {}

/// column must be matching to perform set operation
bool CSetExpression::checkTables(std::shared_ptr < CTable > left, std::shared_ptr < CTable > right) const {
    return (left -> getHeader() == right -> getHeader());
}

bool CSetExpression::isNested() const {
    return false;
}

int CSetExpression::relNum() const {
    return 0;
}