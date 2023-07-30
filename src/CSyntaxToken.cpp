//
// Created by terez on 27/05/2021.
//

#include "CSyntaxToken.h"

CSyntaxToken::CSyntaxToken(CSyntaxKind kind, unsigned int position, std::string text): kind(kind), position(position), text(text) {}

unsigned int CSyntaxToken::getPosition() {
    return position;
}

CSyntaxKind CSyntaxToken::getKind() {
    return kind;
}

std::string CSyntaxToken::getText() {
    return text;
}