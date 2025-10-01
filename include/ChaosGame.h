#pragma once
#include <vector>
#include <random>
#include <optional>
#include "Point.h"

class ChaosGameFunctor {
public:
    // ratio ∈ (0,1), за замовчуванням 0.5
    explicit ChaosGameFunctor(Point initial,
                              std::vector<Point> anchors,
                              double ratio = 0.5,
                              std::optional<uint32_t> seed = std::nullopt);

    // Повертає наступну точку послідовності
    Point operator()();

    // Доступ до стану
    const Point& current() const noexcept { return curr_; }
    const std::vector<Point>& anchors() const noexcept { return anchors_; }
    double ratio() const noexcept { return ratio_; }

private:
    std::vector<Point> anchors_;
    Point curr_;
    double ratio_;
    std::mt19937 rng_;
    std::uniform_int_distribution<std::size_t> dist_;
};