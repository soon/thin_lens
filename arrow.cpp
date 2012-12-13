#include "arrow.hpp"

#include <QtCore/QPoint>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/qmath.h>

Arrow::Arrow(const QPoint &begin, const QPoint &end)
    : _begin(begin), _end(end)
{

}

QPoint Arrow::getBegin() const
{
    return _begin;
}

QPoint Arrow::getEnd() const
{
    return _end;
}

double Arrow::height() const
{
    return qSqrt(qPow(_begin.x() - _end.x(), 2) + qPow(_begin.y() - _end.y(), 2));
}

void Arrow::setBegin(const QPoint &begin)
{
    _begin = begin;
}

void Arrow::setEnd(const QPoint &end)
{
    _end = end;
}

void Arrow::paint(QPainter &painter)
{
    painter.drawLine(_begin, _end);

    // Fix this
    int r = static_cast<int>(height()) * _RATIO;
    painter.drawEllipse(_end, r, r);
}

ThinLens::AbstractObject *Arrow::clone() const
{
    return new Arrow(*this);
}
