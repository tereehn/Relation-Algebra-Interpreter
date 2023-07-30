//
// Created by terez on 27/05/2021.
//

#include "CTableExpression.h"

CTableExpression::CTableExpression(const std::shared_ptr < CTable > tableToAdd): table(tableToAdd) {}

std::shared_ptr < CTable > CTableExpression::evaluate() const {
    return table;
}

std::string CTableExpression::toSQL() const {
    std::string toReturn;
    toReturn += table -> getName();
    return toReturn;
}

bool CTableExpression::isNested() const {
    return false;
}

int CTableExpression::relNum() const {
    return 0;
}