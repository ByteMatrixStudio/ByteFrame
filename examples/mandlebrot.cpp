//#define _CRT_SECURE_NO_WARNINGS
#include "byteframe.hpp"
#include <raylib.h>
#include <cmath>

// The set consists of all the complex numbers "C" for which the sequence starting at "z=0" does not diverge to infinity. - How beautiful!

constexpr int WIDTH  = 800;
constexpr int HEIGHT = 600;

struct Complex {
    double x;
    double y;

    Complex() : x(0.0), y(0.0) {}
    Complex(double rr, double ii) : x(rr), y(ii) {}

    //Magnitude squared
    double mag2() const {
        return x * x + y * y;
    }

    //Square - the heart of the math <3
    Complex square() const {
        return Complex(
            x * x - y * y,
            2.0 * x * y
        );
    }

    Complex operator+(const Complex& o) const {
        return Complex(x + o.x, y + o.y);
    }

    Complex operator*(const Complex& o) const {
        return Complex(
            x * o.x - y * o.y,
            x * o.y + y * o.x
        );
    }
};

void RenderMandelbrot(bf::Canvas& canvas,
                      double centerX,
                      double centerY,
                      double zoom,
                      int maxIter)
{
    for (int py = 0; py < HEIGHT; ++py) {
        for (int px = 0; px < WIDTH; ++px) {

            double a = centerX + (px - WIDTH  / 2.0) * zoom;
            double b = centerY + (py - HEIGHT / 2.0) * zoom;

            Complex c(a, b);
            Complex z(0.0, 0.0);

            int iter = 0;

            // Wanted to make the code look pretty more like the OG equation  zₙ₊₁ = zₙ² + c

            while (iter < maxIter && z.mag2() <= 4.0) {
                z = z.square() + c;
                ++iter;
            }

            bf::Color col;

            if (iter == maxIter) {
                col = bf::Color(0, 0, 0);
            } else {
                float t = static_cast<float>(iter) / maxIter;

                uint8_t rcol = static_cast<uint8_t>(9.0f  * (1 - t) * t * t * t * 255);
                uint8_t gcol = static_cast<uint8_t>(15.0f * (1 - t) * (1 - t) * t * t * 255);
                uint8_t bcol = static_cast<uint8_t>(8.5f * (1 - t) * (1 - t) * (1 - t) * t * 255);

                col = bf::Color(rcol, gcol, bcol);
            }

            canvas.drawPixel(
                static_cast<size_t>(px),
                static_cast<size_t>(py),
                col
            );
        }
    }
}

int main() {
    bf::Canvas canvas(WIDTH, HEIGHT);

    InitWindow(WIDTH, HEIGHT, "ByteFrame Mandelbrot (Pretty Math)");
    SetTargetFPS(60);

    Image img{};
    img.data    = canvas.data();
    img.width   = WIDTH;
    img.height  = HEIGHT;
    img.mipmaps = 1;
    img.format  = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

    Texture2D tex = LoadTextureFromImage(img);

    double centerX = -0.5;
    double centerY =  0.0;
    double zoom    =  0.005;
    int    maxIter = 200;

    RenderMandelbrot(canvas, centerX, centerY, zoom, maxIter);

    while (!WindowShouldClose()) {

        bool changed = false;

        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f) {
            int mx = GetMouseX();
            int my = GetMouseY();

            double a = centerX + (mx - WIDTH  / 2.0) * zoom;
            double b = centerY + (my - HEIGHT / 2.0) * zoom;

            double zoomFactor = (wheel > 0.0f) ? 0.8 : 1.25;
            zoom *= zoomFactor;

            centerX = a - (mx - WIDTH  / 2.0) * zoom;
            centerY = b - (my - HEIGHT / 2.0) * zoom;

            changed = true;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mx = GetMouseX();
            int my = GetMouseY();

            double a = centerX + (mx - WIDTH  / 2.0) * zoom;
            double b = centerY + (my - HEIGHT / 2.0) * zoom;

            zoom *= 0.8;

            centerX = a - (mx - WIDTH  / 2.0) * zoom;
            centerY = b - (my - HEIGHT / 2.0) * zoom;

            changed = true;
        }

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            int mx = GetMouseX();
            int my = GetMouseY();

            double a = centerX + (mx - WIDTH  / 2.0) * zoom;
            double b = centerY + (my - HEIGHT / 2.0) * zoom;

            zoom *= 1.25;

            centerX = a - (mx - WIDTH  / 2.0) * zoom;
            centerY = b - (my - HEIGHT / 2.0) * zoom;

            changed = true;
        }

        double panSpeed = zoom * 50.0;
        if (IsKeyDown(KEY_LEFT))  { centerX -= panSpeed; changed = true; }
        if (IsKeyDown(KEY_RIGHT)) { centerX += panSpeed; changed = true; }
        if (IsKeyDown(KEY_UP))    { centerY -= panSpeed; changed = true; }
        if (IsKeyDown(KEY_DOWN))  { centerY += panSpeed; changed = true; }

        if (changed) {
            RenderMandelbrot(canvas, centerX, centerY, zoom, maxIter);
        }

        UpdateTexture(tex, canvas.data());

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(tex, 0, 0, WHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
