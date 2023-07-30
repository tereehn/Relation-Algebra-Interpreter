//
// Created by terez on 27/05/2021.
//
#ifndef SEMESTRAL_CQUERYHANDLER_H
#define SEMESTRAL_CQUERYHANDLER_H
#include <string>
#include <map>
#include <stack>
#include <memory>
#include "CTokenizer.h"
#include "CTable.h"
#include "CExpression.h"
#include <vector>

/*!  Class handles user's input, builds polymorphic tree representing the query and returns the result. */
class CQueryHandler {
public:
    /*!
     * Constructor with name
     * @param inputLine - line entered by user
     */
    CQueryHandler(const std::string & inputLine, std::map < std::string, std::shared_ptr < CTable >> data);
    /*!
     * Check if parenthesis are set correctly
     * @return bool - true if set correctly, false otherwise
     */
    bool checkParenthesis(const std::string & inputLine) const;
    /*!
     * Split line into tokens
     * @return bool - true if no error has occurred
     */
    bool startParsing();
    /*!
     * Check if table of given name exist
     * @return bool - true if exist
     */
    bool checkTableValidity(const std::string & tableName) const;
    /*!
     * Builds polymorphic tree that represent one query
     * @return true - if successful
     */
    bool buildTree();
    /*!
     * Evaluates the tree
     * @return CTable - result of query
     */
    std::shared_ptr < CTable > getResult() const;
    /*!
     * Evaluates the tree
     * @return string - sql translation
     */
    std::string getSQL() const;
    /*!
     * Create node of a tree according to the operator
     * @param tableLeft - left node of new parent node
     * @param tableRight - right node of new parent node
     * @param op - CSyntaxKind decides operation
     * @return std::shared_ptr<CExpression> for further processing
     */
    std::shared_ptr < CExpression > mergeFactory(std::shared_ptr < CExpression > tableLeft, std::shared_ptr < CExpression > tableRight, CSyntaxKind op, bool nested) const;
    /*!
     * Creates projecting node of a tree
     * @param table - only child of a node
     * @param toProject - columns that shall be projected
     * @return std::shared_ptr<CExpression> for further processing
     */
    std::shared_ptr < CExpression > projectFactory(std::shared_ptr < CExpression > table,
                                                   const std::string & toProject) const;
    /*!
     * Creates projecting list node
     * @param tableName - name of the table
     * @return std::shared_ptr<CExpression> for further processing
     */
    std::shared_ptr < CExpression > tableFactory(const std::string & tableName) const;
    /*!
     * Creates projecting list node
     * @param tableLeft - left node of new parent node
     * @param tableRight - right node of new parent node
     * @param joinOn - atributes for join on
     * @return std::shared_ptr<CExpression> for further processing
     */
    std::shared_ptr < CExpression > joinOnFactory(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right,
                                                  const std::string & joinOn) const;

private:
    CTokenizer tokens; /*!< Class that tokenizes the input */
    std::vector < CSyntaxToken > tokenList; /*!< Input line split to tokens */
    std::map < std::string, std::shared_ptr < CTable >> tables;
    std::shared_ptr < CExpression > result; /*!< Top node of the tree */
};

#endif //SEMESTRAL_CQUERYHANDLER_H