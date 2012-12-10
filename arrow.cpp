#include "arrow.hpp"

#include <QPoint>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/qmath.h>

Arrow::Arrow(const QPoint &begin, const QPoint &end): _begin(begin), _end(end)
{

}

inline QPoint Arrow::getBegin() const
{
    return _begin;
}

inline QPoint Arrow::getEnd() const
{
    return _end;
}

inline void Arrow::setBegin(const QPoint &begin)
{
    _begin = begin;
}

inline void Arrow::setEnd(const QPoint &end)
{
    _end = end;
}

inline void Arrow::paint(QPainter *painter, QPaintEvent *)
{
    painter -> drawLine(_begin, _end);

    // Fix this
    int r = static_cast<int>(qSqrt(qPow(_begin.x() - _end.x(), 2) + qPow(_begin.y() - _end.y(), 2)) * _RATIO);
    painter -> drawEllipse(_end, r, r);
}
