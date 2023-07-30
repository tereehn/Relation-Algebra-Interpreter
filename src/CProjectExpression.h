//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CPROJECTEXPRESSION_H
#define SEMESTRAL_CPROJECTEXPRESSION_H
#include "CExpression.h"

/*!  Class represents the projection node of relation algebra. Chooses only requested columns. Is a child class of CExpression. */
class CProjectExpression :public CExpression {
public:
    /*!
    * Constructor with name of data location
    * @param node - appends child node
    * @param toPrint - vector of columns and their new names, shall they be renamen
    */
    CProjectExpression(std::shared_ptr<CExpression> node, const std::vector<std::pair<std::string,std::string>> & toPrint);
    /*!
    * Overrides toSQL() method of a parent.
    */
    std::shared_ptr<CTable> evaluate() const override;
    /*!
    * Overrides evaluate() method of a parent.
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
    std::shared_ptr<CExpression> expression; /// child node
    std::vector<std::pair<std::string,std::string>> toProject; /// rename specifications
};


#endif //SEMESTRAL_CPROJECTEXPRESSION_H
