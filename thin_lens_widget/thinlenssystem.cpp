#include "thinlenssystem.hpp"

#include <algorithm>

namespace ThinLens
{

ThinLensSystem::ThinLensSystem
(
    AbstractObject &object,
    int focus,
    QWidget *parent
) : QWidget(parent), _object(object), _image(_object.clone()), _focus(focus)
{

}

inline int ThinLensSystem::getFocus() const noexcept
{
    return _focus;
}

inline void ThinLensSystem::setFocus(int focus) noexcept
{
    _focus = focus;
    update();
}

inline void ThinLensSystem::switchType() noexcept
{
    _focus = -_focus;
    update();
}

inline const AbstractObject& ThinLensSystem::getObject() const noexcept
{
    return _object;
}

inline void ThinLensSystem::setObject(AbstractObject &object) noexcept
{
    _object = object;
    _image.reset(_object.clone());
    update();
}

inline const AbstractObject& ThinLensSystem::getImage() const noexcept
{
    return *_image;
}

inline void ThinLensSystem::_drawAxis(QPainter &painter) const noexcept
{
    painter.drawLine(0, height() / 2, width(), height() / 2);
}

inline void ThinLensSystem::_drawLens(QPainter &painter) const noexcept
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

    static auto delta = ((_focus < 0) ? (10) : (-10));
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

inline void ThinLensSystem::_drawRaysFromPoint
(
    QPainter &painter,
    const QPoint &point
) const noexcept
{
    painter.drawLine(point, QPoint(width() / 2, point.y()));
    // painter.drawLine();
}

inline void ThinLensSystem::_drawRays(QPainter &painter) const noexcept
{
    _drawRaysFromPoint(painter, _object.getBegin());
    _drawRaysFromPoint(painter, _object.getEnd());
}

void ThinLensSystem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);



    _drawAxis(painter);
    _drawLens(painter);

    _object.paint(painter);

    _drawRays(painter);
}

} // namespace ThinLens
