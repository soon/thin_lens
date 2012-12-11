#ifndef THINLENSSYSTEM_HPP
#define THINLENSSYSTEM_HPP

#include <QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <memory>

#include "abstractobject.hpp"

namespace ThinLens
{

class ThinLensSystem : public QWidget
{
    Q_OBJECT

public:
    explicit ThinLensSystem
    (
        AbstractObject &object,
        int focus = 10,
        QWidget *parent = 0
    );

    int getFocus() const noexcept;
    void setFocus(int) noexcept;
    void switchType() noexcept;

    const AbstractObject& getObject() const noexcept;
    void setObject(AbstractObject &object) noexcept;

    const AbstractObject& getImage() const noexcept;

protected:
    void paintEvent(QPaintEvent *);

private:
    void _drawAxis(QPainter &) const noexcept;
    void _drawLens(QPainter &) const noexcept;
    void _drawRays(QPainter &) const noexcept;

    void _drawRaysFromPoint(QPainter &, const QPoint &) const noexcept;
    
private:
    AbstractObject                  &_object;
    std::shared_ptr<AbstractObject> _image;

    int _focus;
};

} // namespace ThinLens

#endif // THINLENSSYSTEM_HPP
