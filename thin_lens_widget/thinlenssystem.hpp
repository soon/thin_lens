#ifndef THINLENSSYSTEM_HPP
#define THINLENSSYSTEM_HPP

#include <QWidget>
#include <memory>

#include "abstractobject.hpp"

namespace ThinLens
{

enum TYPE
{
    COLLECTING,
    DIVERGING
};

class ThinLensSystem : public QWidget
{
    Q_OBJECT

public:
    explicit ThinLensSystem
    (
        AbstractObject *object,
        TYPE state = TYPE::COLLECTING,
        int focus = 10,
        QWidget *parent = 0
    );

    TYPE getState() const noexcept;
    void setState(const TYPE &type) noexcept;
    void switchState() noexcept;

    AbstractObject *getObject() const noexcept;
    void setObject(AbstractObject* object) noexcept;

protected:
    void paintEvent(QPaintEvent *) noexcept;
    
private:
    AbstractObject                  *_object;
    std::shared_ptr<AbstractObject> _image;

    TYPE _state;
    int _focus;
};

} // namespace ThinLens

#endif // THINLENSSYSTEM_HPP
