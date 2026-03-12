#include "raylib.h"
#include <math.h>
#define BALL_COUNT 25
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define BOUNDS_MARGIN 50

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

    if (b->x <= BOUNDS_MARGIN || b->x >= SCREEN_WIDTH - BOUNDS_MARGIN){
        if (b->x <= BOUNDS_MARGIN) b->x = BOUNDS_MARGIN;
        if (b->x >= SCREEN_WIDTH - BOUNDS_MARGIN) b->x = SCREEN_WIDTH - BOUNDS_MARGIN;
        b->vx *= -1;
    }
    if (b->y <= BOUNDS_MARGIN || b->y >= SCREEN_HEIGHT - BOUNDS_MARGIN){
        if (b->y <= BOUNDS_MARGIN) b->y = BOUNDS_MARGIN;
        if (b->y >= SCREEN_HEIGHT - BOUNDS_MARGIN) b->y = SCREEN_HEIGHT - BOUNDS_MARGIN;
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
    if(distance < 120)
        DrawLine(a->x,a->y,b->x,b->y,WHITE);
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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib test");
    SetTargetFPS(60);
    
    for(int i = 0 ; i < BALL_COUNT; i++){
        balls[i].x = GetRandomValue(BOUNDS_MARGIN, SCREEN_WIDTH - BOUNDS_MARGIN);
        balls[i].y = GetRandomValue(BOUNDS_MARGIN, SCREEN_HEIGHT - BOUNDS_MARGIN);

        balls[i].vx = GetRandomValue(-6,6);
        balls[i].vy = GetRandomValue(-6,6);

        balls[i].radius = GetRandomValue(20,50);
        balls[i].color = (Color){
            GetRandomValue(50,255),
            GetRandomValue(50,255),
            GetRandomValue(50,255),
            180
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
        DrawRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,(Color){0,0,0,40});
        for(int i = 0 ; i < BALL_COUNT; i++){
            DrawBall(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();
}