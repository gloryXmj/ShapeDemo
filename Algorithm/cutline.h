#ifndef CUTLINE_H
#define CUTLINE_H


#include "Line.h"
#include "Rect.h"
#include <vector>

class CutLine
{
    using Line = Mcoder::Line;
    using Rect = Mcoder::Rect;
    using Point = Mcoder::Point;
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
    virtual bool exeCutLine(int lineId = -1) = 0 ;
protected:

    std::vector<Line*> lines;
    Rect rect ;
};


namespace Cohen_Suther_land {
class Cohen_Suther_CutLine : public CutLine
{
    using Line = Mcoder::Line;
    using Rect = Mcoder::Rect;
    using Point = Mcoder::Point;
public:
    Cohen_Suther_CutLine(){};
    /*!
     * \brief exeCutLine  执行裁剪动作
     * \param lineId  为-1 表示裁剪所有直线
     * \return
     */
    virtual bool exeCutLine(int lineId = -1) override;

private:
    /*!
     * \brief CS_CutLine Cohen-Sutherland裁剪算法
     * \param line
     * \return
     */
    int CS_CutLine(const Line *line);
    void encode(double x, double y, int &code);
};
}

namespace Liang_Barsky {
class Liang_Barsky_CutLine:public CutLine
{
    using Line = Mcoder::Line;
    using Rect = Mcoder::Rect;
    using Point = Mcoder::Point;
public:
    Liang_Barsky_CutLine(){};
    /*!
     * \brief exeCutLine  执行裁剪动作
     * \param lineId  为-1 表示裁剪所有直线
     * \return
     */
    virtual bool exeCutLine(int lineId = -1) override;
private:
    bool ClipT(double q,double d,double &t0,double &t1);
    void LiangBarskyLineClip(const Line *line);
};
}
#endif // CUTLINE_H
