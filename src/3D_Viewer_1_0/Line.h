#ifndef LINE_H
#define LINE_H

class Line{
private:
    int startIndex;
    int endIndex;
    int edge;
public:
     Line(int start, int end) {
        this->startIndex = start;
        this->endIndex = end;
    }
     explicit Line() {}
public:
  int isEqualLine(Line first, Line second);
  int checkLine(Line **lines, int length, Line *line);
  int getEdgeCounter();
};

#endif // LINE_H
