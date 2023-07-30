//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CTABLEEXPRESSION_H
#define SEMESTRAL_CTABLEEXPRESSION_H
#include "CExpression.h"

/*!  Leaf node of every table. Holds information about one table. */
class CTableExpression: public CExpression {
public:
    /*!
     * Constructor accepting table from data source
     * @param tablee - one table
     */
    CTableExpression(const std::shared_ptr < CTable > tableToAdd);
    /*!
     * Overrides evaluate() method of a parent.
     */
    std::shared_ptr < CTable > evaluate() const override;
    /*!
     * Overrides toSQL() method of a parent.
     */
    std::string toSQL() const override;
    bool isNested() const override;
    int relNum() const override;
private:
    std::shared_ptr < CTable > table; /// table belonging to the node
};

#endif //SEMESTRAL_CTABLEEXPRESSION_H