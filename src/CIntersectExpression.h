//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CINTERSECTEXPRESSION_H
#define SEMESTRAL_CINTERSECTEXPRESSION_H
#include "CSetExpression.h"

/*!  Class represents the intersection of two relations. It is a child class of CSetExpression. */
class CIntersectExpression: public CSetExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CIntersectExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    /*!
     * Overrides evaluate() method of a parent.
     */
    std::shared_ptr < CTable > evaluate() const override;
    /*!
     * Overrides toSQL() method of a parent.
     */
    std::string toSQL() const override;
};

#endif //SEMESTRAL_CINTERSECTEXPRESSION_H