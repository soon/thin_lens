#include "line.hpp"

#include <QtCore/QPoint>

#include <limits>
#include <cmath>
#include <stdexcept>

namespace soon
{

namespace geometry
{

Line::Line(int x1, int y1, int x2, int y2) noexcept
    : _k(static_cast<double>(y1 - y2) / (x1 - x2)), _b(y1 - _k * x1)
{

}

Line::Line(const QPoint &p1, const QPoint &p2) noexcept
    : Line(p1.x(), p1.y(), p2.x(), p2.y())
{

}

Line::Line(const QPoint &p, int x, int y) noexcept
    : Line(p.x(), p.y(), x, y)
{

}

Line::Line(int x, int y, const QPoint &p) noexcept
    : Line(p, x, y)
{

}

int Line::y(int x) const noexcept
{
    return static_cast<int>(_k * x + _b);
}

bool operator|| (const Line &l1, const Line &l2) noexcept
{
    return std::abs(l1._k - l2._k) < std::numeric_limits<double>::epsilon();
}

QPoint operator& (const Line &l1, const Line &l2)
{
    if(l1 || l2)
        throw std::invalid_argument("The lines are parralel");
    auto x = -(l1._b - l2._b) / (l1._k - l2._k);
    return QPoint(x, l1.y(x));
}

bool Line::operator== (const Line &l) noexcept
{
    return (*this || l) && (std::abs(_b - l._b) < std::numeric_limits<double>::epsilon());
}

} // namespace geometry

} // namespace soon
