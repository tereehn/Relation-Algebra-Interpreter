//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CJOIN_H
#define SEMESTRAL_CJOIN_H
#include "CBinaryExpression.h"

/*!  Class represents the join operation of two tables. It is a child class of CExpression and abstract class for CJoinExpression and CJoinOnExpression */

class CJoin: public CBinaryExpression {
public:
    /*!
     * Constructor with children nodes
     * @param left - left child
     * @param right - right child
     */
    CJoin(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right);
    /*!
     * Sets leftCol and rightCol values, according to the column in which the common attribute is
     * @param left - left child
     * @param right - right child
     */
    virtual bool findCommon(std::shared_ptr < CTable > left, std::shared_ptr < CTable > right) const = 0;
    /*!
     * Makes new header by joining the tables
     * @param left - left child
     * @param right - right child
     * @param newTable - table to be created
     */
    virtual void makeHeader(std::shared_ptr < CTable > & newTable, std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const = 0;
    /*!
     * Join tables by common attribute
     * @param left - left child
     * @param right - right child
     * @param newTable - table to be created
     */
    virtual void joinTables(std::shared_ptr < CTable > & newTable, std::shared_ptr < CTable > leftTable, std::shared_ptr < CTable > rightTable) const;
protected:
    /*! number of column in which common attribute is */
    mutable unsigned int leftCol;
    mutable unsigned int rightCol;
};

#endif //SEMESTRAL_CJOIN_H