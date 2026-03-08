#include "raylib.h"
#include <math.h>
#define BALL_COUNT 25

typedef struct { 
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    Color color;
}Ball;
Ball balls[BALL_COUNT];

void BallUpdate(Ball *b){
    b->x += b->vx;
    b->y += b->vy;

    if (b->x <= 50 || b->x >= 750){
        if (b->x <= 50) b->x = 50;
        if (b->x >= 750) b->x = 750;
        b->vx *= -1;
    }
    if (b->y <= 50 || b->y >= 750){
        if (b->y <= 50) b->y = 50;
        if (b->y >= 750) b->y = 750;
        b->vy *= -1;
    }
}

void DrawBall(Ball* b){
    DrawCircle(b->x,b->y,b->radius,b->color);
}

bool checkBallCollision(Ball *a, Ball *b){
    float dx = a->x - b->x;
    float dy = a->y - b->y;

    float distance = sqrtf(dx*dx+dy*dy);
    float rad = a->radius + b->radius;
    return distance <= rad;
}

void resolveCollision(Ball *a, Ball *b){
    a->x -= a->vx;
    a->y -= a->vy;

    b->x -= b->vx;
    b->y -= b->vy;

    float temp_vx = a->vx;
    float temp_vy = a->vy;

    a->vx = b->vx;
    a->vy = b->vy;

    b->vx = temp_vx;
    b->vy = temp_vy;
}

int main() {
    InitWindow(800, 800, "raylib test");
    SetTargetFPS(60);
    
    for(int i = 0 ; i < BALL_COUNT; i++){
        balls[i].x = GetRandomValue(50,750);
        balls[i].y = GetRandomValue(50,750);

        balls[i].vx = GetRandomValue(-6,6);
        balls[i].vy = GetRandomValue(-6,6);

        balls[i].radius = GetRandomValue(20,50);
        balls[i].color = (Color){
            GetRandomValue(50,255),
            GetRandomValue(50,255),
            GetRandomValue(50,255),
            255
        };
    }
    

    
    while (!WindowShouldClose()) {

        for (int i = 0; i < BALL_COUNT; i++) {
            BallUpdate(&balls[i]);
        }
        
        for (int i = 0 ; i < BALL_COUNT; i++){
            for (int j = i+1 ; j < BALL_COUNT; j++){
                if(checkBallCollision(&balls[i],&balls[j])){
                    resolveCollision(&balls[i],&balls[j]);
                }
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0 ; i < BALL_COUNT; i++){
            DrawBall(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();
}