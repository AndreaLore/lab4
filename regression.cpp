#include "regression.hpp"

#include <stdexcept>

int Regression::size() const { return N_; }

void Regression::add(double x, double y) {
}

Result Regression::fit() const {
  if (N_ < 2) {
    throw std::runtime_error{"Not enough points to run a fit"};
  }

  double const d = N_ * sum_x2_ - sum_x_ * sum_x_;
  if (d == 0.) {
    throw std::runtime_error{"Trying to fit a vertical line"};
  }

  double const a = (sum_y_ * sum_x2_ - sum_x_ * sum_xy_) / d;
  double const b = (N_ * sum_xy_ - sum_x_ * sum_y_) / d;

  double sum_x{};
  double sum_y{};
  double sum_xy{};
  double sum_x2{};

  for (auto const& p : points_) {
    sum_x += p.x;
    sum_y += p.y;
    sum_xy += p.x * p.y;
    sum_x2 += p.x * p.x;
  }

  return {a, b};
}

Result fit(Regression const &reg) {
  // the following call would fail compilation if the fit method weren't const
  return reg.fit();
}
