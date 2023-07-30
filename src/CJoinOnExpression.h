//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CJOINONEXPRESSION_H
#define SEMESTRAL_CJOINONEXPRESSION_H
#include "CJoin.h"

/*!  Class represents join by attribute of two tables. It is a child class of CJoin. */
class CJoinOnExpression : public CJoin {
public:
    /*!
    * Constructor with children nodes
    * @param left - left child
    * @param right - right child
    */
    CJoinOnExpression(std::shared_ptr<CExpression> left,std::shared_ptr<CExpression> right,const std::string & leftString,const std::string & rightString);
    /*!
    * Overrides makeHeader() method of a parent.
    */
    void makeHeader(std::shared_ptr<CTable> &newTable, std::shared_ptr<CTable> leftTable, std::shared_ptr<CTable> rightTable) const override;
    /*!
    * Overrides findCommon() method of a parent.
    */
    bool findCommon(std::shared_ptr<CTable> leftTable, std::shared_ptr<CTable> rightTable) const override;
    /*!
    * Overrides evaluate() method of a parent.
    */
    std::shared_ptr<CTable> evaluate() const override;
    /*!
    * Overrides toSQL() method of a parent.
    */
    std::string toSQL() const override;
    bool isNested() const override;
    int relNum() const override;
private:
    std::string leftString;
    std::string rightString;
};


#endif //SEMESTRAL_CJOINONEXPRESSION_H
