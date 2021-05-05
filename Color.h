#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    Color();
    Color(int r,int g,int b);
    Color(const Color &color);
    void operator=(Color color);
    int red() const ;
    int green() const ;
    int blue() const ;
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void getRGB(int *r, int *g, int *b);
    void setRgb(int r, int g, int b);
    double redF() const;
    double greenF() const;
    double blueF() const;
private:
    int m_red;
    int m_green;
    int m_blue;
};
#endif // COLOR_H
