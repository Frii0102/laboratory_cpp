#pragma once
#include <ostream>

struct Point {
    double x{0.0};
    double y{0.0};
};

// Лінійна інтерполяція між a і b: a + t*(b - a)
inline Point lerp(const Point& a, const Point& b, double t) {
    return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
}

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    return (os << p.x << ' ' << p.y);
}