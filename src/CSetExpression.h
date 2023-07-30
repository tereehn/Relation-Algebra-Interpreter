//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CSETEXPRESSION_H
#define SEMESTRAL_CSETEXPRESSION_H
#include "CBinaryExpression.h"

/*!  Abstract class of set operations. */
class CSetExpression: public CBinaryExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CSetExpression(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    /*!
     * Compare headers and check if the columns match
     * @param left - left  node
     * @param right - right node
     * @return bool - if headers are the same, false otherwise
     */
    virtual bool checkTables(std::shared_ptr < CTable > left, std::shared_ptr < CTable > right) const;
    /*!
    * Overrides isNested() method of a parent
    */
    bool isNested() const override;
    /*!
    * Overrides relNum() method of a parent
    */
    int relNum() const override;
};

#endif //SEMESTRAL_CSETEXPRESSION_H