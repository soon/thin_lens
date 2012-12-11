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
    explicit Arrow(const QPoint &, const QPoint &);

    QPoint getBegin() const;
    QPoint getEnd() const;

    void setBegin(const QPoint &);
    void setEnd(const QPoint &);

    void paint(QPainter &);

    ThinLens::AbstractObject *clone() const;

private:
    QPoint _begin;
    QPoint _end;

    // static constexpr double _ANGLE = M_PI / 18;
    static constexpr double _RATIO = 0.1;
};

#endif // ARROW_HPP
