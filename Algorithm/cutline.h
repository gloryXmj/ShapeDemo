#ifndef CUTLINE_H
#define CUTLINE_H


#include "Line.h"
#include "Rect.h"
#include <vector>
namespace Cohen_Suther_land {
class CutLine
{
    using Line = Mcoder::Line;
    using Rect = Mcoder::Rect;
public:
    CutLine();

    typedef std::vector<Line*>::iterator iterator;
    typedef std::vector<Line*>::const_iterator const_iterator;

    /*!
     * \brief setRect  设置裁剪框的大小
     * \param rect
     */
    void setRect(Rect rect);

    /*!
     * \brief setLines  设置需要裁剪的线段
     * \param lines
     */
    void setLines(std::vector<Line*> lines);
    /*!
     * \brief getLine  获取器对应的线
     * \param id
     * \return
     */\
    Line* getLine(int id);

    /*!
     * \brief getHeadLine 获取第一条线
     * \return
     */
    iterator getHeadLine();
    /*!
     * \brief getTailLine 获取最后一条线
     * \return
     */
    iterator getTailLine();
    /*!
     * \brief getEndLine  迭代器的结束标志
     * \return
     */
    iterator getEndLine();
    /*!
     * \brief addLine 添加线
     * \param line
     */
    void addLine(Line *line);

    /*!
     * \brief LinesNum  含有的线的数量
     * \return
     */
    int LinesNum() const;

    /*!
     * \brief exeCutLine  执行裁剪动作
     * \param lineId  为-1 表示裁剪所有直线
     * \return
     */
    bool exeCutLine(int lineId = -1);

private:
    /*!
     * \brief CS_CutLine Cohen-Sutherland裁剪算法
     * \param line
     * \return
     */
    int CS_CutLine(const Line *line);
    void encode(double x, double y, int &code);
private:
    std::vector<Line*> lines;
    Rect rect ;
};
}
#endif // CUTLINE_H
