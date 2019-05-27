#include "point.hpp"

Point::Point(int iX, int iY) {
  iX_ = iX;
  iY_ = iY;
}

int Point::x() const { return iX_; }

void Point::setX(int iX) { iX_ = iX; }

int Point::y() const { return iY_; }

void Point::setY(int iY) { iY_ = iY; }
