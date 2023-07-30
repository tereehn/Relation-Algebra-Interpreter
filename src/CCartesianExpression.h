//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CCARTESIANEXPRESSION_H
#define SEMESTRAL_CCARTESIANEXPRESSION_H
#include "CBinaryExpression.h"

/*!  Class that stores the relation of two nodes and calculates cartesian product. It is a child class of CBinaryExpression. */

class CCartesianExpression : public CBinaryExpression{
public:
    /*!
    * Constructor with children nodes
    * @param left - left child
    * @param right - right child
    */
    CCartesianExpression(std::shared_ptr<CExpression> left,std::shared_ptr<CExpression> right);
    /*!
    * Overrides evaluate() method of a parent
    */
    std::shared_ptr<CTable> evaluate() const override;
    /*!
    * Overrides toSQL() method of a parent
    */
    std::string toSQL() const override;
    /*!
    * Overrides isNested() method of a parent
    */
    bool isNested() const override;
    /*!
    * Overrides relNum() method of a parent
    */
    int relNum() const override;

private:
    void makeHeader(std::shared_ptr<CTable> left, std::shared_ptr<CTable> right, std::shared_ptr<CTable> & newTable)const; /// creates header, checks for duplicates
};


#endif //SEMESTRAL_CCARTESIANEXPRESSION_H
