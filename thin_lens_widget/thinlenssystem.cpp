#include "thinlenssystem.hpp"

#include <Qt>
#include <QtCore/QRect>
#include <QtCore/QPoint>
#include <QtCore/QString>

#include <string>
#include <algorithm>
#include <stdexcept>
#include <cmath>

#include "geometry/line.hpp"

namespace ThinLens
{

ThinLensSystem::ThinLensSystem
(
    AbstractObject &object,
    int focus,
    unsigned flags,
    QWidget *parent
) :
    QWidget(parent),
    _object(object),
    _image(_object.clone()),
    _focus(focus),
    _flags(flags)
{

}

int ThinLensSystem::getFocus() const noexcept
{
    return _focus;
}

void ThinLensSystem::setFocus(int focus) noexcept
{
    _focus = focus;
    update();
}

void ThinLensSystem::switchType() noexcept
{
    _focus = -_focus;
    update();
}

const AbstractObject &ThinLensSystem::getObject() const noexcept
{
    return _object;
}

void ThinLensSystem::setObject(AbstractObject &object) noexcept
{
    _object = object;
    _image.reset(_object.clone());
    update();
}

const AbstractObject &ThinLensSystem::getImage() const noexcept
{
    return *_image;
}

int ThinLensSystem::getObjectDistance() const noexcept
{
    return std::abs(width() / 2 - _object.getBegin().x());
}

void ThinLensSystem::setObjectDistance(int dist) noexcept
{
    _object.setBegin(_object.getBegin() + QPoint(dist, 0));
    _object.setEnd(_object.getEnd() + QPoint(dist, 0));
    update();
}

int ThinLensSystem::getImageDistance() const
{
    if(!_image)
        throw std::invalid_argument("No image");
    // return _image -> getBegin().x() - width() / 2;
    auto d = getObjectDistance();
    return ((d == _focus) ? (0) : ((_focus * d) / (d - _focus)));
}

unsigned ThinLensSystem::getFlags() const noexcept
{
    return _flags;
}

void ThinLensSystem::setFlags(unsigned flags) noexcept
{
    _flags = flags;
}

QPoint ThinLensSystem::getFocalPoint(const QPoint &point) const noexcept
{
    return QPoint(width() / 2 + ((point.x() > width() / 2) ? (-_focus) : (_focus)), height() / 2);
}

QPoint ThinLensSystem::getAxisCenter() const noexcept
{
    return QPoint(width() / 2, height() / 2);
}

void ThinLensSystem::_drawAxis(QPainter &painter) const noexcept
{
    painter.drawLine(0, height() / 2, width(), height() / 2);

    painter.drawLine
    (
        width() / 2 + _focus, height() / 2 - 5,
        width() / 2 + _focus, height() / 2 + 5
    );

    painter.drawLine
    (
        width() / 2 + 2 * _focus, height() / 2 - 5,
        width() / 2 + 2 * _focus, height() / 2 + 5
    );

    painter.drawLine
    (
        width() / 2 - _focus, height() / 2 - 5,
        width() / 2 - _focus, height() / 2 + 5
    );

    painter.drawLine
    (
        width() / 2 - 2 * _focus, height() / 2 - 5,
        width() / 2 - 2 * _focus, height() / 2 + 5
    );

    // Switch F and F' if the object in the right side of the lens
    auto k = ((_object.getBegin().x() > width() / 2) ? (-1) : (1));
    if(std::abs(_focus) > 10)
    {
        painter.drawText(width() / 2 + _focus * k - 2,  height() / 2 + 20, "F");
        painter.drawText(width() / 2 - _focus * k - 2,  height() / 2 + 20, "F'");
    }
    if(std::abs(_focus) > 20)
    {
        painter.drawText
        (
            width() / 2 + 2 * _focus * k - 2,   height() / 2 + 20, "2F"
        );

        painter.drawText
        (
            width() / 2 - 2 * _focus * k - 2,   height() / 2 + 20, "2F'"
        );
    }
}

void ThinLensSystem::_drawLens(QPainter &painter) const noexcept
{
    auto dist = std::max
    (
        std::abs(height() / 2 - _object.getBegin().y()),
        std::abs(height() / 2 - _object.getEnd().y())
    ) + 20;
    painter.drawLine
    (
        width() / 2, height() / 2 - dist,
        width() / 2, height() / 2 + dist
    );

    auto delta = ((_focus > 0) ? (10) : (-10));

    painter.drawLine
    (
        width() / 2,                    height() / 2 - dist,
        width() / 2 + std::abs(delta),  height() / 2 - dist + delta
    );
    painter.drawLine
    (
        width() / 2,                    height() / 2 - dist,
        width() / 2 - std::abs(delta),  height() / 2 - dist + delta
    );
    painter.drawLine
    (
        width() / 2,                    height() / 2 + dist,
        width() / 2 + std::abs(delta),  height() / 2 + dist - delta
    );
    painter.drawLine
    (
        width() / 2,                    height() / 2 + dist,
        width() / 2 - std::abs(delta),  height() / 2 + dist - delta
    );
}

void ThinLensSystem::_drawRaysFromPoint
(
    QPainter &painter,
    const QPoint &point
) const noexcept
{
    // From point to lens || OX
    painter.drawLine(point, QPoint(width() / 2, point.y()));

    // From point to axis center
    painter.drawLine(point, getAxisCenter());

    try
    {
        auto end = _calculatePoint(point);

        // From end to lens || OX
        painter.drawLine(end, QPoint(width() / 2, point.y()));

        // From end to axis center
        painter.drawLine(end, getAxisCenter());
    }
    catch(std::invalid_argument)
    {
        // TODO
    }
}

void ThinLensSystem::_drawRays(QPainter &painter) const noexcept
{
    _drawRaysFromPoint(painter, _object.getBegin());
    _drawRaysFromPoint(painter, _object.getEnd());
}

void ThinLensSystem::_drawInfo(QPainter &painter) const noexcept
{
    QString info;

    info += QString("F: ") += QString::number(_focus);
    info += ((_focus > 0) ? (" (collecting)") : (" (diverging)"));
    info += '\n';

    info += QString("d: ") += QString::number(getObjectDistance()) += '\n';
    try
    {
        auto f = getImageDistance();
        info += QString("f: ") += QString::number(f);
        info += ((f > 0) ? (" (real)") : (" (imaginary)"));
        info += '\n';
    }
    catch(std::invalid_argument)
    {
        info += "f: No image\n";
    }

    info += '\n';
    info += QString("Object height: ") += QString::number(_object.height()) += '\n';
    if(_image)
    {
        info += QString("Image height: ") += QString::number(_image -> height()) += '\n';
        info += QString("k: ") += QString::number(_image -> height() / _object.height()) += '\n';
    }
    painter.drawText(QRect(20, 20, 150, 150), Qt::TextWordWrap, info);
}

QPoint ThinLensSystem::_calculatePoint(const QPoint &p) const
{
    using namespace soon::geometry;

    // From point to axis center
    Line l1(p, getAxisCenter());

    // From lens to focal point
    Line l2(width() / 2, p.y(), getFocalPoint(p));
    if(l1 == l2)
    {
        Line rnd(p.x(), p.y() + 100000, getAxisCenter());
        auto intersectionWithFocal = QPoint(getFocalPoint(p).x(), rnd.y(getFocalPoint(p).x()));
        l2 = Line(width() / 2, height() / 2 - 100000, intersectionWithFocal);
        // FIXME
        // Line focal(width() / 2 + _focus * k, height() / 2, width() / 2 + _focus * k, height() / 2 - 10);
        // Line rnd(p.x(), p.y() - 10, width() / 2, height() / 2);
        // auto frp = focal & rnd;
        // l1 = Line(p, width() / 2 + 10, height() / 2);
        // l2 = Line(width() / 2 + 10, height() / 2, frp);

    }
    return l1 & l2;
}

void ThinLensSystem::_calculateImage() noexcept
{
    try
    {
        auto begin = _calculatePoint(_object.getBegin());
        auto end = _calculatePoint(_object.getEnd());
        if(!_image)
            _image.reset(_object.clone());
        _image -> setBegin(begin);
        _image -> setEnd(end);
    }
    catch(std::invalid_argument)
    {
        _image.reset();
    }
}

void ThinLensSystem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    _drawAxis(painter);
    _drawLens(painter);

    _object.paint(painter);

    _calculateImage();
    if(_image)
        _image -> paint(painter);

    if(_flags & showRays)
        _drawRays(painter);

    if(_flags & showInfo)
        _drawInfo(painter);

}

} // namespace ThinLens
