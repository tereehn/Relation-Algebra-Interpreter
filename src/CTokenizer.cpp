//
// Created by terez on 27/05/2021.
//

#include <algorithm>
#include "CTokenizer.h"

CTokenizer::CTokenizer(const std::string & line): str(line), position(0) {}

bool CTokenizer::checkGaps() const { /// set operation must be separated by gap on each side
    if (position != 0) {
        char prev = str[position - 1];
        char next = str[position + 1];
        return (isspace(prev) && isspace(next));
    }
    return false;
}

CSyntaxToken CTokenizer::nextToken() {

    if (position == str.size()) {
        return CSyntaxToken(CSyntaxKind::INPUT_EOF, position, "");
    }
    if (currentToken() == 'U') {
        if (checkGaps()) {
            return CSyntaxToken(CSyntaxKind::UNION, position++, "U");
        }
    }
    if (currentToken() == 'I') {
        if (checkGaps()) {
            return CSyntaxToken(CSyntaxKind::INTERSECT, position++, "I");
        }
    }
    if (currentToken() == 'X') {
        if (checkGaps()) {
            return CSyntaxToken(CSyntaxKind::CROSS_JOIN, position++, "X");
        }
    }
    if (isalnum(currentToken())) {
        unsigned int start = position;
        while (isalnum(currentToken()) || currentToken() == '_') next();
        return CSyntaxToken(CSyntaxKind::STRING_TOKEN, start, str.substr(start, (position - start)));
    }

    if (isspace(currentToken())) { /// skip gaps
        unsigned int start = position;
        while (isspace(currentToken())) next();
        return CSyntaxToken(CSyntaxKind::WHITE_SPACE_TOKEN, start, "");
    }

    if (currentToken() == '[') {
        unsigned int start = position++;
        while (currentToken() != ']') next();

        std::string getText = str.substr(start + 1, (position - start) - 1);

        if (currentToken() == ']') {
            position++;
            if (getText.find('=') != std::string::npos) {
                return CSyntaxToken(CSyntaxKind::JOIN_ON, start, getText);
            } else {
                return CSyntaxToken(CSyntaxKind::PROJECTION_EXPRESS, start, getText);
            }
        }
        return CSyntaxToken(CSyntaxKind::BAD_INPUT, position++, "");
    }
    if (currentToken() == '{') {
        return CSyntaxToken(CSyntaxKind::CURLY_LEFT_BRACKET, position++, "{");
    }
    if (currentToken() == '}') {
        return CSyntaxToken(CSyntaxKind::CURLY_RIGHT_BRACKET, position++, "}");
    }
    if (currentToken() == '(') {
        unsigned int start = position++;
        int count = 1;
        while (count) {
            if (currentToken() == '(') count++;
            if (currentToken() == ')') count--;
            next(); /// nested brackets
        }
        return CSyntaxToken(CSyntaxKind::BASIC_BRACKET_EXPRESS, start, str.substr(start + 1, (position - start) - 2));
    }
    if (currentToken() == '*') {
        return CSyntaxToken(CSyntaxKind::JOIN, position++, "*");
    }
    if (currentToken() == '\\') {
        return CSyntaxToken(CSyntaxKind::DIFF, position++, "\\");
    }
    return CSyntaxToken(CSyntaxKind::BAD_INPUT, position++, "");
}

void CTokenizer::next() {
    position++;
}

char CTokenizer::currentToken() {

    if (position >= str.size()) {
        return '\0';
    }
    return str[position];
}