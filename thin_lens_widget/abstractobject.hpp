#ifndef ABSTRACTOBJECT_HPP
#define ABSTRACTOBJECT_HPP

#include <QPoint>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

namespace ThinLens
{

class AbstractObject
{

public:
    virtual ~AbstractObject()
    {

    }

    virtual QPoint getBegin() const = 0;
    virtual QPoint getEnd() const = 0;

    virtual void setBegin(const QPoint &) = 0;
    virtual void setEnd(const QPoint &) = 0;

    virtual void paint(QPainter *, QPaintEvent *) = 0;
};

} // namespace ThinLens

#endif // ABSTRACTOBJECT_HPP
