//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CEXPRESSION_H
#define SEMESTRAL_CEXPRESSION_H
#include "CTable.h"
#include "CExceptions/ErrorTreeNodeException.h"

/*!  Abstract class for all of the nodes of the relational algebra tree. Returns the result or translates query to SQL expression.*/
class CExpression {
public:
    /*!
    * Default constructor
    */
    CExpression( void ) = default;
    /*!
    * Default destructor
    */
    virtual ~CExpression ( void ) noexcept = default;
    /*!
    * Recursively evaluates the tree nodes and returns result
    * @return std::shared_ptr<CTable> - represents the result of a query stored in a table
    */
    virtual std::shared_ptr<CTable> evaluate() const = 0;
    /*!
    * Translates query to SQL
    * @return std::string - sql interpretation of query
    */
    virtual std::string toSQL() const = 0;
    /*!
    * Checks if node contains nested expression
    * @return bool - if nested, false otherwise
    */
    virtual bool isNested() const =0;
    /*!
    * Checks how many nested relations are preceding
    * @return int - number of relation
    */
    virtual int relNum() const = 0;
};


#endif //SEMESTRAL_CEXPRESSION_H
