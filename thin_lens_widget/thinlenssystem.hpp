#ifndef THINLENSSYSTEM_HPP
#define THINLENSSYSTEM_HPP

#include <QtGui/QWidget>
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
    enum
    {
        showRays = 0x1,
        showInfo = 0x2     // Show F, f, d, height of object and image
    };

    explicit ThinLensSystem
    (
        AbstractObject &object,
        int focus = 50,
        unsigned flags = showInfo,
        QWidget *parent = 0
    );

    int getFocus() const noexcept;
    void setFocus(int) noexcept;
    void switchType() noexcept;

    const AbstractObject& getObject() const noexcept;
    void setObject(AbstractObject &object) noexcept;

    const AbstractObject& getImage() const noexcept;

    unsigned getFlags() const noexcept;
    void setFlags(unsigned) noexcept;

    int getObjectDistance() const noexcept;
    void setObjectDistance(int) noexcept;

    int getImageDistance() const;
    double getImageHeight() const;

    QPoint getFocalPoint(const QPoint &) const noexcept;
    QPoint getAxisCenter() const noexcept;

protected:
    void paintEvent(QPaintEvent *);

private:
    void _drawAxis(QPainter &) const noexcept;
    void _drawLens(QPainter &) const noexcept;
    void _drawRays(QPainter &) const noexcept;
    void _drawInfo(QPainter &) const noexcept;

    void _drawRaysFromPoint(QPainter &, const QPoint &) const noexcept;

    QPoint _calculatePoint(const QPoint &) const;
    void _calculateImage() noexcept;
    
private:
    AbstractObject                  &_object;
    std::shared_ptr<AbstractObject> _image;

    int _focus;

    unsigned _flags;
};

} // namespace ThinLens

#endif // THINLENSSYSTEM_HPP
