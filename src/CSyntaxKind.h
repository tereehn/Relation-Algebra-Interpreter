//
// Created by terez on 27/05/2021.
//

#ifndef SEMESTRAL_CSYNTAXKIND_H
#define SEMESTRAL_CSYNTAXKIND_H

/*!  Enumerates tokens, query will be split into. */

enum class CSyntaxKind {
    STRING_TOKEN,
    WHITE_SPACE_TOKEN,
    CURLY_RIGHT_BRACKET,
    CURLY_LEFT_BRACKET,
    JOIN,
    JOIN_ON,
    CROSS_JOIN,
    UNION,
    INTERSECT,
    DIFF,
    BAD_INPUT,
    INPUT_EOF,
    BASIC_BRACKET_EXPRESS,
    PROJECTION_EXPRESS
};

#endif //SEMESTRAL_CSYNTAXKIND_H