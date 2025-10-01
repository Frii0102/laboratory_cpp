#include <stdexcept>
#include <utility>
#include <algorithm>
#include <functional>

#include "ChaosGame.h"

ChaosGameFunctor::ChaosGameFunctor(Point initial,
                                   std::vector<Point> anchors,
                                   double ratio,
                                   std::optional<uint32_t> seed)
    : anchors_(std::move(anchors)),
      curr_(initial),
      ratio_(ratio),
      rng_(seed ? std::mt19937{*seed} : std::mt19937{std::random_device{}()})
{
    if (anchors_.empty()) {
        throw std::invalid_argument("At least one base point is required.");
    }
    if (!(ratio_ > 0.0 && ratio_ < 1.0)) {
        throw std::invalid_argument("Ratio must be in the open interval (0,1).");
    }
    dist_ = std::uniform_int_distribution<std::size_t>(0, anchors_.size() - 1);
}

Point ChaosGameFunctor::operator()() {
    std::size_t i = dist_(rng_);
    curr_ = lerp(curr_, anchors_[i], ratio_);
    return curr_;
}