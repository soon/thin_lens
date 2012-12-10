#include "thinlenssystem.hpp"

#include <algorithm>

namespace ThinLens
{

ThinLensSystem::ThinLensSystem
(
    AbstractObject *object,
    TYPE state,
    int focus,
    QWidget *parent
) : QWidget(parent), _object(object), _state(state), _focus(focus)
{

}

TYPE ThinLensSystem::getState() const noexcept
{
    return _state;
}

void ThinLensSystem::setState(const TYPE& state) noexcept
{
    _state = state;
    update();
}

void ThinLensSystem::switchState() noexcept
{
    _state =
    (
        (_state == TYPE::COLLECTING)    ?
            (TYPE::DIVERGING)           :
            (TYPE::COLLECTING)
    );
    update();
}

AbstractObject *ThinLensSystem::getObject() const noexcept
{
    return _object;
}

void ThinLensSystem::setObject(AbstractObject *object) noexcept
{
    _object = object;
    update();
}

void ThinLensSystem::paintEvent(QPaintEvent *event) noexcept
{
    QPainter painter(this);

    painter.drawLine(0, height() / 2, width(), height() / 2);

    // Drawing the lense
    auto dist = std::max
    (
        std::abs(height() / 2 - _object -> getBegin().y()),
        std::abs(height() / 2 - _object -> getEnd().y())
    ) + 20;
    painter.drawLine
    (
        width() / 2, height() / 2 - dist,
        width() / 2, height() / 2 + dist
    );

    static auto delta = ((_state == TYPE::COLLECTING) ? (10) : (-10));
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

    // Drawing the object
    _object -> paint(&painter, event);
}

} // namespace ThinLens
