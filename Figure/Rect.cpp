#include "Rect.h"

using namespace Mcoder;

Rect::Rect()
{
    this->x_max = 0.0;
    this->x_min = 0.0;
    this->y_max = 0.0;
    this->y_min = 0.0;
}

Rect::Rect(const Rect &rect)
{
    this->x_max = rect.x_max;
    this->x_min = rect.x_min;
    this->y_max = rect.y_max;
    this->y_min = rect.y_min;
}

Rect::Rect(const double xmax, const double xmin, const double ymax, const double ymin)
{
    this->x_max = xmax;
    this->x_min = xmin;
    this->y_max = ymax;
    this->y_min = ymin;
}

Rect::Rect(const Point ptTL, const Point ptBR)
{
    this->x_max = ptBR.getX();
    this->x_min = ptTL.getX();
#ifdef Y_AXIS_POSITIVE_IS_POSITIVE
    this->y_max = ptTL.getY();
    this->y_min = ptBR.getY();
#else
    this->y_max = ptBR.getY();
    this->y_min = ptTL.getY();
#endif
}

void Rect::setPoint(const Point ptTL, const Point ptBR)
{
    this->x_max = ptBR.getX();
    this->x_min = ptTL.getX();
#ifdef Y_AXIS_POSITIVE_IS_POSITIVE
    this->y_max = ptTL.getY();
    this->y_min = ptBR.getY();
#else
    this->y_max = ptBR.getY();
    this->y_min = ptTL.getY();
#endif
}

double Rect::xmax() const
{
    return this->x_max;
}

double Rect::xmin() const
{
    return this->x_min;
}

double Rect::ymax() const
{
    return this->y_max;
}

double Rect::ymin() const
{
    return this->y_min;
}
