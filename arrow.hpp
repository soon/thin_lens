#ifndef ARROW_HPP
#define ARROW_HPP

#include <QPoint>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/qmath.h>

#include "thin_lens_widget/abstractobject.hpp"

class Arrow : public ThinLens::AbstractObject
{
public:
    explicit Arrow(const QPoint &begin, const QPoint &end);
    
    QPoint getBegin() const;
    QPoint getEnd() const;

    void setBegin(const QPoint &);
    void setEnd(const QPoint &);

    void paint(QPainter *, QPaintEvent *);

private:
    QPoint _begin;
    QPoint _end;

    // static const double _ANGLE = M_PI / 18;
    static constexpr double _RATIO = 0.1;
};

#endif // ARROW_HPP
