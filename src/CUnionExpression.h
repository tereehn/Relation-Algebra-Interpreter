//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CUNIONEXPRESSION_H
#define SEMESTRAL_CUNIONEXPRESSION_H
#include "CSetExpression.h"

/*!  Class represents union operation between two nodes. Is child class of CSetExpression. */

class CUnionExpression: public CSetExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CUnionExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    /*!
     * Overrides evaluate() method of a parent.
     */
    std::shared_ptr < CTable > evaluate() const override;
    /*!
     * Overrides toSQL() method of a parent.
     */
    std::string toSQL() const override;
};

#endif //SEMESTRAL_CUNIONEXPRESSION_H