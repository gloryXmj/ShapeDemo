#include "Color.h"

#define COLOR_MAX_VALUE 255.0

Color::Color()
    :m_red(0),
      m_green(0),
      m_blue(0)
{

}

Color::Color(int r, int g, int b)
{
    m_red = r;
    m_green = g;
    m_blue = b;
}

Color::Color(const Color &color)
{
    m_red = color.m_red;
    m_green = color.m_green;
    m_blue = color.m_blue;
}

void Color::operator=(Color color)
{
    this->m_red = color.m_red;
    this->m_green = color.m_green;
    this->m_blue = color.m_blue;
}

int Color::red() const
{
    return m_red;
}

int Color::green() const
{
    return m_green;
}

int Color::blue() const
{
    return m_blue;
}

void Color::setRed(int red)
{
    m_red = red ;
}

void Color::setGreen(int green)
{
    m_green = green;
}

void Color::setBlue(int blue)
{
    m_blue = blue;
}

void Color::getRGB(int *r, int *g, int *b)
{
    r = &m_red;g = &m_green;b=&m_blue;
}

void Color::setRgb(int r, int g, int b)
{
    m_red = r;
    m_green = g;
    m_blue = b;
}

double Color::redF() const
{
    return m_red/COLOR_MAX_VALUE;
}

double Color::greenF() const
{
    return m_green/COLOR_MAX_VALUE;
}

double Color::blueF() const
{
    return m_blue/COLOR_MAX_VALUE;
}
