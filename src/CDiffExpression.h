//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CDIFFEXPRESSION_H
#define SEMESTRAL_CDIFFEXPRESSION_H
#include "CSetExpression.h"

/*!  Class represents the difference between two relations. It is a child class of CSetExpression. */
class CDiffExpression: public CSetExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CDiffExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    /*!
     * Overrides evaluate() method of its parent.
     */
    std::shared_ptr < CTable > evaluate() const override;
    /*!
     * Overrides toSQL() method of its parent.
     */
    std::string toSQL() const override;
};

#endif //SEMESTRAL_CDIFFEXPRESSION_H