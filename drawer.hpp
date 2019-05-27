#ifndef DRAWER_HPP
#define DRAWER_HPP
#include "QGLWidget"
#include "level.hpp"

class Drawer {
 public:
  Drawer();
  void draw(const Level& level, QGLWidget& qglWidget);

 private:
  void drawGrid(const Level& level, QGLWidget& qglWidget);
  void drawObjects(const Level& level, QGLWidget& qglWidget);
  void drawStatistics(const Level& level, QGLWidget& qglWidget);
};

#endif  // DRAWER_HPP
