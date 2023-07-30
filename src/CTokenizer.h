//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CTOKENIZER_H
#define SEMESTRAL_CTOKENIZER_H
#include "CSyntaxToken.h"

/*!  Class responsible for tokenizing input into tokens, according to set and relational operations. */
class CTokenizer {
public:
    /*!
     * Constructor accepting user's input
     * @param line - line to be proccessed
     */
    CTokenizer(const std::string & line);
    /*!
     * Procces next token
     * @return SyntaxToken
     */
    CSyntaxToken nextToken();
    /*!
     * Char getter
     * @return char - current symbol on input
     */
    char currentToken();
    /*!
     * check if set operators are separated from the rest of query
     * @return true is are, false otherwise
     */
    bool checkGaps() const;
private:
    std::string str;
    void next(); /*!< Moves to next position */
    unsigned int position;
};

#endif //SEMESTRAL_CTOKENIZER_H