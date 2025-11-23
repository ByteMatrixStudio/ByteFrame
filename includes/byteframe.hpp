#ifndef BF_HPP
#define BF_HPP

#include <cstdint>
#include <vector>
#include <cstddef>

namespace bf {

struct Vec2 {
  float x, y;
};

class Color {
public:
  uint8_t r, g, b, a;

  Color();
  Color(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa = 255);

  uint32_t toU32();
  static Color toColor(uint32_t rgba);
};

extern Color GREY;
extern Color RED;
extern Color WHITE;
extern Color GREEN;
extern Color BLUE;

class Canvas {
public:
  Canvas(size_t w, size_t h);

  void fill(Color col);
  void drawRect(size_t w, size_t h, size_t x, size_t y, Color col);
  void drawPixel(size_t x, size_t y, Color color);
  void rd_canvas_to_ppm(const char *filename);

  void drawEllipse(int cx, int cy, float rx, float ry, Color col);
  void drawCircle(int cx, int cy, float r, Color col);
  void drawVline(size_t start, size_t end, size_t x, size_t w, Color col);
  void drawHline(size_t start, size_t end, size_t y, size_t w, Color col);
  void drawTriangle(Vec2 v1, Vec2 v2, Vec2 v3, Color col);

  uint32_t *data();

private:
  size_t width, height;
  std::vector<uint32_t> pixels;
  float rd_solve_y(Vec2 a, Vec2 b, float x);
};

}
#endif // BF_HPP
