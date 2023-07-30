//
// Created by terez on 27/05/2021.
//

#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression(std::shared_ptr<CExpression> left,std::shared_ptr<CExpression> right) :  leftNode(left),rightNode(right) {}