//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CBINARYEXPRESSION_H
#define SEMESTRAL_CBINARYEXPRESSION_H
#include "CExpression.h"

/*!  Abstract Class defining relation between two nodes. It is a child class of CExpression. */
class CBinaryExpression: public CExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CBinaryExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    protected:
    std::shared_ptr < CExpression > leftNode; /// left child
    std::shared_ptr < CExpression > rightNode; /// right child
};

#endif //SEMESTRAL_CBINARYEXPRESSION_H