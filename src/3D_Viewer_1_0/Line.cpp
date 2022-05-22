#include "Line.h"
#include <iostream>

int Line::isEqualLine(Line first, Line second) {
    int equal = 0;
    if ((first.startIndex == second.startIndex && first.endIndex == second.endIndex) ||
        (first.startIndex == second.endIndex && first.endIndex == second.startIndex))
        equal = 1;
    return equal;
}

int Line::checkLine(Line **lines, int length, Line *line) {
    int added = 0;
    int unique = 1;
    for (int i = 0; i < length; i++) {
        if (isEqualLine((*lines)[i], *line)) {
             unique = 0;
             break;
        }
    }
    if (unique) {
        *lines  = (Line *)realloc(*lines, sizeof(Line) * ++length);
        (*lines)[length - 1] = *line;
        added = 1;
    }
    this->edge = added;
    return added;
}

int Line::getEdgeCounter(){
    return this->edge;
}
