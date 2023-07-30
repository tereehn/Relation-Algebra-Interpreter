//
// Created by terez on 28/05/2021.
//

#ifndef SEMESTRAL_CSELECTEXPRESSION_H
#define SEMESTRAL_CSELECTEXPRESSION_H
#include "CExpression.h"

/*!  Class represents the selection node of relation algebra. Chooses only tables that satisfy requested criteria. It is a child class of CExpression. */
class CSelectExpression: public CExpression {
public:
    /*!
     * Constructor with name of data location
     * @param tablee - appends child node
     * @param det - details of criteria
     */
    CSelectExpression(std::shared_ptr < CExpression > tablee,
                      const std::string & det);
    /*!
     * Overrides toSQL() method of a parent.
     */
    std::string toSQL() const override;
    /*!
     * Merges two tables
     * @param line - the operator
     * @param rightTable - left table
     * @param leftTable - right table
     */
    std::shared_ptr < CTable > applyOp(const std::string line, std::shared_ptr < CTable > rightTable, std::shared_ptr < CTable > leftTable) const;
    /*!
     * Creates table by attribute specified
     * @param tmp - string specifying wanted data
     * @param tmpTable - table that is being processed
     * @return std::shared_ptr<CTable> - return table that contains matching attributes
     */
    std::shared_ptr < CTable > createTable(std::string tmp, std::shared_ptr < CTable > tmpTable) const;
    /*!
     * Check if item of table matches specification
     * @param rightSide
     * @param leftSide
     * @param option - op
     * @return bool if true and should be added to table
     */
    bool compare(std::string rightSide, std::string leftSide, int option) const;
    /*!
     * Overrides evaluate() method of a parent.
     */
    std::shared_ptr < CTable > evaluate() const override;
    /*!
   * Overrides isNested() method of a parent
   */
    bool isNested() const override;
    /*!
    * Overrides relNum() method of a parent
    */
    int relNum() const override;
    int findColumn(std::shared_ptr < CTable > tmpTable,
                   const std::string & attribute) const;
    /*!
     * Merges two tables
     * @param s - string that is to be processed
     * @return bool - if string is a number, false otherwise
     */
    bool isDouble(const std::string & input) const;
    /*!
     * Merges two tables
     * @param str - result string
     * @param from - substring to be replaced
     * @param to - substring to be replaced with
     */
    void replaceOp(std::string & str,
                   const std::string & from,
                   const std::string & to) const;
private:
    std::shared_ptr < CExpression > node; /// child node
    std::string line; /// line that will be parsed into tokens and executed
};

#endif //SEMESTRAL_CSELECTEXPRESSION_H