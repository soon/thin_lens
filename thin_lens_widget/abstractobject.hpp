#ifndef ABSTRACTOBJECT_HPP
#define ABSTRACTOBJECT_HPP

#include <QtCore/QPoint>
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
    virtual double height() const = 0;

    virtual void setBegin(const QPoint &) = 0;
    virtual void setEnd(const QPoint &) = 0;

    virtual void paint(QPainter &) = 0;

    virtual AbstractObject *clone() const = 0;
};

} // namespace ThinLens

#endif // ABSTRACTOBJECT_HPP
