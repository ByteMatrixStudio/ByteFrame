#include <byteframe.hpp>
#include <raylib.h>
#define WIDTH 800
#define HEIGHT 600

int main(void) {
    bf::Canvas canva(WIDTH, HEIGHT);
    InitWindow(WIDTH, HEIGHT, "hello from Raylib");

    Image img = {
        .data = canva.data(),
        .width = WIDTH,
        .height = HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D tex = LoadTextureFromImage(img);

    bf::Vec2 t1 = { 200, 50 };
    bf::Vec2 t2 = { 400, 200 };
    bf::Vec2 t3 = { 600, 50 };

    while (!WindowShouldClose()) {
        canva.fill(bf::WHITE);


        canva.drawDigit(3, 150, 150, 10, bf::PURPLE);         // single "3"
        canva.drawNumber(42, 450, 450, 15, bf::YELLOW);       // "42"
        canva.drawNumber(123, 600, 20, 3, bf::ORANGE);       // "123" smaller


        canva.drawTriangle(t1, t2, t3, bf::RED);
        canva.drawRect(160, 80, 0, 0, bf::BLUE);
        canva.drawCircle(300, 300, 50, bf::GREEN);



        BeginDrawing();
        UpdateTexture(tex, canva.data());
        DrawTexture(tex, 0, 0, WHITE);
        DrawFPS(700, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
