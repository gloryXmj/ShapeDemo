#ifndef CUTLINE_H
#define CUTLINE_H


#include "Line.h"
#include "Rect.h"
#include <vector>
namespace Cohen_Suther_land {


//using Mcoder::Line;

class CutLine
{
    using Line = Mcoder::Line;
public:
    CutLine();
    typedef std::vector<Line*>::iterator iterator;
    typedef std::vector<Line*>::const_iterator const_iterator;

    void setLines(std::vector<Line*> lines);
    Line* getLine(int id);
    iterator getHeadLine();
    iterator getTailLine();
    iterator getEndLine();
    void addLine(Line *line);
    std::vector<Line*> lines;
};
}

#endif // CUTLINE_H
