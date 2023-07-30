//
// Created by terez on 28/05/2021.
//

#include "CSelectExpression.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <sstream>

CSelectExpression::CSelectExpression(std::shared_ptr < CExpression > tablee,
                                     const std::string & det): node(tablee), line(det) {}



int CSelectExpression::findColumn(std::shared_ptr < CTable > tmpTable,
                                  const std::string & attribute) const {
    std::string tmp = attribute;
    /// function to remove trailing whitespaces
    tmp.erase( tmp.begin(), find_if( tmp.begin(), tmp.end(), not1( std::ptr_fun<int, int>( isspace ) ) ) );
    tmp.erase( find_if( tmp.rbegin(), tmp.rend(), not1( std::ptr_fun<int, int>( isspace ) ) ).base(), tmp.end() );

    for (unsigned i = 0; i < tmpTable -> getHeader().size(); i++) {
        if (tmpTable -> getHeader()[i] == tmp) {
            return i;
        }
    }
    return -1;
}

std::shared_ptr < CTable > CSelectExpression::evaluate() const {
    std::shared_ptr < CTable > tmpTable = node -> evaluate();

    std::stack < std::string > ops;
    std::stack < std::shared_ptr < CTable >> values;

    for (unsigned int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') continue;

        else if (line[i] == '(') {
            std::string tmp = "(";
            ops.push(tmp);
        } else if (isalpha(line[i])) {
            std::string val = {};
            int count = 0;
            while (i < line.length() && line[i] != ')') {
                if (line[i] == '\'') {
                    count++;
                }
                if (count == 2) break;
                val += line[i];
                i++;
            }
            values.push(createTable(val, tmpTable));
            i--;
        } else if (line[i] == ')') {
            while (!ops.empty() && ops.top() != "(") {
                if (values.empty()) {
                    throw ErrorTreeNodeException("Incorrect selection expression!");
                }
                std::shared_ptr < CTable > val2 = values.top();
                values.pop();

                if (values.empty()) {
                    throw ErrorTreeNodeException("Incorrect selection expression!");
                }
                std::shared_ptr < CTable > val1 = values.top();
                values.pop();

                std::string op = ops.top();
                ops.pop();

                values.push(applyOp(op, val1, val2));
            }

            if (!ops.empty())
                ops.pop();
        } else {
            if (line[i] == '|') {
                i++;
                if (line[i] == '|') {
                    ops.push("||");
                } else {
                    throw ErrorTreeNodeException("Incorrect selection operator!");
                }
            } else if (line[i] == '&') {
                i++;
                if (line[i] == '&') {
                    ops.push("&&");
                } else {
                    throw ErrorTreeNodeException("Incorrect selection operator!");
                }
            }
        }
    }

    while (!ops.empty()) {
        if (values.empty()) {
            throw ErrorTreeNodeException("Incorrect selection expression!");
        }
        std::shared_ptr < CTable > val2 = values.top();
        values.pop();

        if (values.empty()) {
            throw ErrorTreeNodeException("Incorrect selection expression!");
        }
        std::shared_ptr < CTable > val1 = values.top();
        values.pop();

        std::string op = ops.top();
        ops.pop();

        values.push(applyOp(op, val1, val2));
    }
    return values.top();
}

bool CSelectExpression::isDouble(const std::string & input) const {
    std::istringstream iss(input);
    double d;
    return iss >> d >> std::ws && iss.eof(); /// check if wrong character was read
}

bool CSelectExpression::compare(std::string rightSide, std::string leftSide, int option) const {

    bool add = false, isNumeric = false;
    double customNum1;
    double customNum2;

    if (isDouble(rightSide) && isDouble(leftSide)) {
        customNum1 = atof(rightSide.c_str());
        customNum2 = atof(leftSide.c_str());
        isNumeric = true;
    }

    if (option == 0) {
        if (isNumeric) {
            return (customNum1 == customNum2);
        } else {
            return (rightSide == leftSide);
        }
    } else if (option == 1) {
        if (isNumeric) {
            return (customNum1 != customNum2);
        } else {
            return (rightSide != leftSide);
        }
    } else if (option == 2) {
        if (isNumeric) {
            return (customNum1 > customNum2);
        } else {
            return (rightSide > leftSide);
        }
    } else if (option == 3) {
        if (isNumeric) {
            return (customNum1 >= customNum2);
        } else {
            return (rightSide >= leftSide);
        }
    } else if (option == 4) {
        if (isNumeric) {
            return (customNum1 < customNum2);
        } else {
            return (rightSide < leftSide);
        }
    } else if (option == 5) {
        if (isNumeric) {
            return (customNum1 <= customNum2);
        } else {
            return (rightSide <= leftSide);
        }
    }
    return add;
}

std::shared_ptr < CTable > CSelectExpression::createTable(std::string tmp, std::shared_ptr < CTable > tmpTable) const {

    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();
    newTable -> getHeader() = tmpTable -> getHeader();

    int option = -1;
    std::string delimiter = {};
    size_t findEqualSign = tmp.find("=");
    if (findEqualSign != std::string::npos) option = 0, delimiter = "=";
    size_t findNotEqualSign = tmp.find("!=");
    if (findNotEqualSign != std::string::npos) option = 1, delimiter = "!=";
    size_t findGreater = tmp.find(">");
    if (findGreater != std::string::npos) option = 2, delimiter = ">";
    size_t findGreaterOrEqual = tmp.find(">=");
    if (findGreaterOrEqual != std::string::npos) option = 3, delimiter = ">=";
    size_t findLess = tmp.find("<");
    if (findLess != std::string::npos) option = 4, delimiter = "<";
    size_t findLessOrEqual = tmp.find("<=");
    if (findLessOrEqual != std::string::npos) option = 5, delimiter = "<=";

    if (option == -1) {
        throw ErrorTreeNodeException("Incorrect compare operator!");
    }

    std::string what, attribute;
    attribute = tmp.substr(0, tmp.find(delimiter));
    what = tmp.substr(tmp.find(delimiter) + delimiter.size(), std::string::npos);
    what.erase(std::remove(what.begin(), what.end(), '\''), what.end()); /// remove quotes from string

    int col = findColumn(tmpTable, attribute);
    if (col == -1) throw ErrorTreeNodeException("Attribute does not exist!");

    for (unsigned i = 0; i < ( * (tmpTable)).rowCount(); i++) {
        CRow tmpRight = ( * (tmpTable))[i];
        std::string att = ( * (tmpTable))[i][col];
        if (compare(att, what, option)) {
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpRight);
            newTable -> pushData(newRow);
        }
    }
    return newTable;
}

std::shared_ptr < CTable > CSelectExpression::applyOp(const std::string line, std::shared_ptr < CTable > rightTable, std::shared_ptr < CTable > leftTable) const {

    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();
    newTable -> getHeader() = rightTable -> getHeader();

    if (line == "&&") {
        for (unsigned i = 0; i < rightTable -> rowCount(); i++) {
            CRow tmpLeft = ( * (rightTable))[i];
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > ();

            if (leftTable -> isRowThere(tmpLeft)) {
                std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
                newTable -> pushData(newRow);
            }
        }
    } else {
        for (unsigned i = 0; i < rightTable -> rowCount(); i++) {
            CRow tmpLeft = ( * (rightTable))[i];
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpLeft);
            newTable -> pushData(newRow);
        }

        for (unsigned i = 0; i < leftTable -> rowCount(); i++) {
            CRow tmpRight = ( * (leftTable))[i];
            std::shared_ptr < CRow > newRow = std::make_shared < CRow > (tmpRight);
            newTable -> pushData(newRow);
        }
    }

    return newTable;
}
/// source https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void CSelectExpression::replaceOp(std::string & str,
                                  const std::string & from,
                                  const std::string & to) const {
    if (str.find(from) == std::string::npos) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string CSelectExpression::toSQL() const {
    std::string newLine = line;
    replaceOp((newLine), "&&", "AND");
    replaceOp((newLine), "||", "OR");
    std::string toReturn = node -> toSQL() + '\n';
    toReturn += "(WHERE " + newLine+")";

    return toReturn;
}

bool CSelectExpression::isNested() const { /// contains information about table
    return true;
}

int CSelectExpression::relNum() const { /// contains information about table
    return 1;
}