//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CSYNTAXTOKEN_H
#define SEMESTRAL_CSYNTAXTOKEN_H
#include <string>

#include "CSyntaxKind.h"

class CSyntaxToken {
public:
    /*!
     * Constructor with name
     * @param kind - token category
     * @param position - position on which was found on input
     * @param name - value
     */
    CSyntaxToken(CSyntaxKind kind, unsigned int position, std::string text);
    /*!
     * Kind Getter
     * @return SyntaxKind token
     */
    CSyntaxKind getKind();
    /*!
     * Value Getter
     * @return string name
     */
    std::string getText();
    /*!
     * Position Getter
     * @return int position
     */
    unsigned int getPosition();
private:
    CSyntaxKind kind;
    unsigned int position;
    std::string text;
};

#endif //SEMESTRAL_CSYNTAXTOKEN_H