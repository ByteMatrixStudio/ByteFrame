#include "byteframe.hpp"
#include <raylib.h>
#include <algorithm> 

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

struct Paddle {
    bf::Vec2 pos;  
    float w;
    float h;
};

struct Ball {
    bf::Vec2 pos;
    bf::Vec2 vel;  
    float radius;
};


void DrawPaddle(bf::Canvas& c, const Paddle& p) {
    c.drawRect(
        static_cast<size_t>(p.w),
        static_cast<size_t>(p.h),
        static_cast<size_t>(p.pos.x),
        static_cast<size_t>(p.pos.y),
        bf::WHITE
    );
}


void DrawBall(bf::Canvas& c, const Ball& b) {
    c.drawCircle(
        static_cast<int>(b.pos.x),
        static_cast<int>(b.pos.y),
        b.radius,
        bf::WHITE
    );
}


bool BallHitsPaddle(const Paddle& p, const Ball& b) {
    float px = p.pos.x;
    float py = p.pos.y;
    float pw = p.w;
    float ph = p.h;

    
    float closestX = std::max(px, std::min(b.pos.x, px + pw));
    float closestY = std::max(py, std::min(b.pos.y, py + ph));

    float dx = b.pos.x - closestX;
    float dy = b.pos.y - closestY;
    float dist2 = dx * dx + dy * dy;

    return dist2 <= b.radius * b.radius;
}

void ResetBall(Ball& ball) {
    ball.pos.x = WIDTH / 2.0f;
    ball.pos.y = HEIGHT / 2.0f;
    ball.vel.x = 250.0f; 
    ball.vel.y = 120.0f;
}

int main() {
   
    bf::Canvas canva(WIDTH, HEIGHT);

    InitWindow(WIDTH, HEIGHT, "ByteFrame Pong..ish");
    SetTargetFPS(60);

    Image img{};
    img.data = canva.data();
    img.width = WIDTH;
    img.height = HEIGHT;
    img.mipmaps = 1;
    img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

    Texture2D tex = LoadTextureFromImage(img);

  
    Paddle left{
        { 50.0f, HEIGHT / 2.0f - 50.0f },
        20.0f,
        100.0f
    };

  
    Paddle right{
        { WIDTH - 70.0f, HEIGHT / 2.0f - 50.0f },
        20.0f,
        100.0f
    };

    Ball ball{
        { WIDTH / 2.0f, HEIGHT / 2.0f },
        { 250.0f, 120.0f },
        10.0f
    };

    int scoreLeft = 0;
    int scoreRight = 0;

    float paddleSpeed = 300.0f;

   
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        
     
        if (IsKeyDown(KEY_W)) left.pos.y -= paddleSpeed * dt;
        if (IsKeyDown(KEY_S)) left.pos.y += paddleSpeed * dt;

       
        if (IsKeyDown(KEY_UP))   right.pos.y -= paddleSpeed * dt;
        if (IsKeyDown(KEY_DOWN)) right.pos.y += paddleSpeed * dt;

     
        if (left.pos.y < 0.0f) left.pos.y = 0.0f;
        if (left.pos.y + left.h > HEIGHT) left.pos.y = HEIGHT - left.h;

        if (right.pos.y < 0.0f) right.pos.y = 0.0f;
        if (right.pos.y + right.h > HEIGHT) right.pos.y = HEIGHT - right.h;

  
        ball.pos.x += ball.vel.x * dt;
        ball.pos.y += ball.vel.y * dt;

        if (ball.pos.y - ball.radius < 0.0f) {
            ball.pos.y = ball.radius;
            ball.vel.y *= -1.0f;
        }
        if (ball.pos.y + ball.radius > HEIGHT) {
            ball.pos.y = HEIGHT - ball.radius;
            ball.vel.y *= -1.0f;
        }

        if (ball.pos.x + ball.radius < 0.0f) {
           
            scoreRight++;
            ResetBall(ball);
        }
        if (ball.pos.x - ball.radius > WIDTH) {
            
            scoreLeft++;
            ResetBall(ball);
        }

       
        if (ball.vel.x < 0.0f && BallHitsPaddle(left, ball)) {
            ball.pos.x = left.pos.x + left.w + ball.radius;
            ball.vel.x *= -1.0f;

            float rel = (ball.pos.y - left.pos.y) / left.h - 0.5f; 
            ball.vel.y += rel * 200.0f;
        }

        if (ball.vel.x > 0.0f && BallHitsPaddle(right, ball)) {
            ball.pos.x = right.pos.x - ball.radius;
            ball.vel.x *= -1.0f;

            float rel = (ball.pos.y - right.pos.y) / right.h - 0.5f;
            ball.vel.y += rel * 200.0f;
        }

       
        canva.fill(bf::GREY);  

        DrawPaddle(canva, left);
        DrawPaddle(canva, right);
        DrawBall(canva, ball);

        
        int scale = 5;
        canva.drawNumber(scoreLeft, WIDTH / 2 - 80, 20, scale, bf::WHITE);
        canva.drawNumber(scoreRight, WIDTH / 2 + 20, 20, scale, bf::WHITE);

       
        UpdateTexture(tex, canva.data());

        BeginDrawing();
        DrawTexture(tex, 0, 0, WHITE);
        DrawFPS(700, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
