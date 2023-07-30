//
// Created by terez on 27/05/2021.
//
#include <iostream>
#include <sstream>
#include <algorithm>
#include "CQueryHandler.h"
#include "CTableExpression.h"
#include "CProjectExpression.h"
#include "CJoinExpression.h"
#include "CJoinOnExpression.h"
#include "CUnionExpression.h"
#include "CIntersectExpression.h"
#include "CCartesianExpression.h"
#include "CDiffExpression.h"
#include "CSelectExpression.h"

CQueryHandler::CQueryHandler(const std::string & inputLine, std::map < std::string, std::shared_ptr < CTable >> data): tokens(CTokenizer(inputLine)), tables(data) {

}

bool CQueryHandler::checkParenthesis(const std::string & inputLine) const {
    std::stack < char > s;
    char ch;
    for (unsigned int i = 0; i < inputLine.length(); i++) {
        if (inputLine[i] == '(' || inputLine[i] == '{') {
            s.push(inputLine[i]);
            continue;
        }
        switch (inputLine[i]) {
            case ')':
                if (s.empty()) return false;
                ch = s.top();
                s.pop();
                if (ch == '{' || ch == '[')
                    return false;
                break;
            case '}':
                if (s.empty()) return false;
                ch = s.top();
                s.pop();
                if (ch == '(' || ch == '[')
                    return false;
                break;
            case ']':
                if (s.empty()) return false;
                ch = s.top();
                s.pop();
                if (ch == '(' || ch == '{')
                    return false;
                break;
            case '[':
                s.push(inputLine[i]);
                break;
        }
    }
    return (s.empty());
}

bool CQueryHandler::startParsing() {

    while (true) {
        CSyntaxToken tmp = tokens.nextToken();
        if (tmp.getKind() == CSyntaxKind::INPUT_EOF) {
            break;
        }
        if (tmp.getKind() != CSyntaxKind::BAD_INPUT) { /// if bad token detected, return false
            CSyntaxToken newToken(tmp.getKind(), tmp.getPosition(), tmp.getText());
            if (newToken.getKind() == CSyntaxKind::WHITE_SPACE_TOKEN) continue;
            tokenList.push_back(newToken);
        } else {
            return false;
        }
    }
    return true;
}

bool CQueryHandler::checkTableValidity(const std::string & tableName) const {
    auto findTable = tables.find(tableName);  /// check is table like this exists
    if (findTable == tables.end()) {
        return false;
    }
    return true;
}

std::shared_ptr < CExpression > CQueryHandler::mergeFactory(std::shared_ptr < CExpression > tableLeft, std::shared_ptr < CExpression > tableRight, CSyntaxKind op, bool nested) const {

    std::shared_ptr < CExpression > merge;
    if (op == CSyntaxKind::JOIN) {
        std::shared_ptr < CExpression > join(new CJoinExpression(tableLeft, tableRight,nested));
        merge = join;
    } else if (op == CSyntaxKind::UNION) {
        std::shared_ptr < CExpression > uni(new CUnionExpression(tableLeft, tableRight));
        merge = uni;
    } else if (op == CSyntaxKind::INTERSECT) {
        std::shared_ptr < CExpression > intersect(new CIntersectExpression(tableLeft, tableRight));
        merge = intersect;
    } else if (op == CSyntaxKind::DIFF) {
        std::shared_ptr < CExpression > diff(new CDiffExpression(tableLeft, tableRight));
        merge = diff;
    } else if (op == CSyntaxKind::CROSS_JOIN) {
        std::shared_ptr < CExpression > crossJoin(new CCartesianExpression(tableLeft, tableRight));
        merge = crossJoin;
    }
    return merge;
}

std::shared_ptr < CExpression > CQueryHandler::projectFactory(std::shared_ptr < CExpression > table,
                                                              const std::string & toProject) const {
    std::vector < std::pair < std::string, std::string >> newNames;
    std::stringstream ss(toProject);
    std::string tmp;
    while (getline(ss >> std::ws, tmp, ',')) {
        size_t found = tmp.find("->");
        if (found == std::string::npos) {
            newNames.push_back(make_pair(tmp, tmp));
        } else {
            std::string getNew = tmp.substr(found + 2, std::string::npos);
            std::string getOld = tmp.substr(0, found);
            newNames.push_back(make_pair(getOld, getNew));
        }
    }
    std::shared_ptr < CExpression > projection(new CProjectExpression(table, newNames));
    return projection;
}

std::shared_ptr < CExpression > CQueryHandler::tableFactory(const std::string & tableName) const {

    if (!checkTableValidity(tableName)) {
        throw ErrorTreeNodeException("Table does not exist!");
    }
    std::shared_ptr < CExpression > table(new CTableExpression(tables.at(tableName)));
    return table;
}

std::shared_ptr < CExpression > CQueryHandler::joinOnFactory(std::shared_ptr < CExpression > left, std::shared_ptr < CExpression > right,
                                                             const std::string & joinOn) const {
    size_t findEqualSign = joinOn.find("=");
    if (findEqualSign == std::string::npos) throw ErrorTreeNodeException("Incorrect join on expression!");
    std::string leftSide = joinOn.substr(0, joinOn.find("="));
    std::string rightSide = joinOn.substr(findEqualSign + 1, std::string::npos);
    std::string leftA = leftSide.substr(leftSide.find('.') + 1, std::string::npos);
    std::string rightA = rightSide.substr(rightSide.find('.') + 1, std::string::npos);

    std::shared_ptr < CExpression > join(new CJoinOnExpression(left, right, leftA, rightA));
    return join;
}

bool CQueryHandler::buildTree() {

    std::stack < std::shared_ptr < CExpression >> values;
    std::stack < CSyntaxToken > ops;

    for (unsigned int i = 0; i < tokenList.size(); i++) {

        if ((tokenList)[i].getKind() == CSyntaxKind::CURLY_LEFT_BRACKET) {
            ops.push((tokenList)[i]);
        } else if ((tokenList)[i].getKind() == CSyntaxKind::STRING_TOKEN) {
            try {
                std::shared_ptr < CExpression > table1 = tableFactory((tokenList)[i].getText());
                values.push(table1);
            } catch (ErrorTreeNodeException
                     const & ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
        } else if ((tokenList)[i].getKind() == CSyntaxKind::BASIC_BRACKET_EXPRESS) {
            if (values.empty()) return false;
            std::shared_ptr < CExpression > val2 = values.top();
            values.pop();
            std::shared_ptr < CExpression > selection(new CSelectExpression(val2, (tokenList)[i].getText()));
            values.push(selection);
        } else if ((tokenList)[i].getKind() == CSyntaxKind::PROJECTION_EXPRESS) {
            if (values.empty()) return false; /// nothing projected could be built on presnet
            std::shared_ptr < CExpression > val2 = values.top();
            values.pop();
            values.push(projectFactory(val2, (tokenList)[i].getText()));
        } else if ((tokenList)[i].getKind() == CSyntaxKind::CURLY_RIGHT_BRACKET) {
            while (!ops.empty() && ops.top().getKind() != CSyntaxKind::CURLY_LEFT_BRACKET) {
                if (values.empty()) return false; /// no tables were given, incorrect

                std::shared_ptr < CExpression > val2 = values.top();
                values.pop();

                if (values.empty()) return false;

                std::shared_ptr < CExpression > val1 = values.top();
                values.pop();

                CSyntaxToken op = ops.top();
                ops.pop();

                if (op.getKind() == CSyntaxKind::JOIN_ON) {
                    values.push(joinOnFactory(val1, val2, op.getText()));
                } else {
                    values.push(mergeFactory(val1, val2, op.getKind(),true));
                }
            }

            if (!ops.empty())
                ops.pop();
        } else {
            ops.push(tokenList[i]);
        }
    }
    while (!ops.empty() && values.size() != 1) { /// in case no brackets were present
        if (values.empty()) return false;

        std::shared_ptr < CExpression > val2 = values.top();
        values.pop();

        if (values.empty()) return false;

        std::shared_ptr < CExpression > val1 = values.top();
        values.pop();

        CSyntaxToken op = ops.top();
        ops.pop();

        if (op.getKind() == CSyntaxKind::JOIN_ON) {
            values.push(joinOnFactory(val1, val2, op.getText()));
        } else {
            values.push(mergeFactory(val1, val2, op.getKind(),false));
        }
    }
    if (values.size() != 1 || ops.size() != 0) { /// only top node should remain in stack and no operator
        return false;
    }

    result = values.top();
    return true;
}

std::shared_ptr < CTable > CQueryHandler::getResult() const {
    std::shared_ptr < CTable > newTable = std::make_shared < CTable > ();
    try { /// try and see if error has occurred while building tree
        newTable = result -> evaluate();
    } catch (ErrorTreeNodeException const & ex) {
        std::cout << ex.what() << std::endl;
    }
    return newTable;
}

std::string CQueryHandler::getSQL() const {
    std::string sql = {};
    sql = result -> toSQL();
    return sql;
}