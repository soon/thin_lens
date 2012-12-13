#ifndef LINE_HPP
#define LINE_HPP

#include <QtCore/QPointF>

namespace soon
{

namespace geometry
{
// FIXME
// We can't specify a line || OY

class Line
{
public:
    Line(int, int, int, int) noexcept;
    Line(const QPoint &, const QPoint &) noexcept;
    Line(const QPoint &, int, int) noexcept;
    Line(int, int, const QPoint &) noexcept;

    int y(int x) const noexcept;

    friend bool operator|| (const Line &, const Line &) noexcept;
    friend QPoint operator& (const Line &, const Line &);
    bool operator== (const Line &) noexcept;

private:
    double _k;
    double _b;
};

} // namespace geometry

} // namespace soon

#endif // LINE_HPP
