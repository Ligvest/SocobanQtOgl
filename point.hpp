#ifndef POINT_HPP
#define POINT_HPP

class Point {
   public:
    Point(int iX, int iY);

    int x() const;
    void setX(int iX);

    int y() const;
    void setY(int iY);

    Point operator-(const Point& rightPoint) const;
    Point operator+(const Point& rightPoint) const;

   private:
    int iX_;
    int iY_;
};

#endif  // POINT_H
