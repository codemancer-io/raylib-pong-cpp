#include "raylib.h"

int player_score = 0;
int cpu_score = 0;

Color Green = Color{38, 185, 154,255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

class Ball {
  public:
    float x, y;
    int speed_x, speed_y;
    int radius;

  void Draw() {
     DrawCircle(x, y, radius, Yellow);
  }

  void Update() {
    x += speed_x;
    y += speed_y;


    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()) {
      cpu_score++;
      ResetBall();
    }
    if (x - radius <= 0 ) { 
      player_score++;
      ResetBall();
    }
  }

  void ResetBall() {
    x = GetScreenWidth() /2 ;
    y = GetScreenHeight() / 2; 

    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)];

  }

};

class Paddle {
protected:
  void LimitMovement() {
    if (y <= 0) {
      y = 0;
    }
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }

public:
  float x, y;
  float width, height;
  int speed; 

  void Draw() {
    DrawRectangleRounded(Rectangle{x, y , width, height}, 0.8, 0,  WHITE);
  }

  void Update() {
    if (IsKeyDown(KEY_UP)){
      y = y - speed;
    }
    if (IsKeyDown(KEY_DOWN)) { 
      y = y + speed;
    }
    LimitMovement();
  }
};

class CpuPaddle: public Paddle {
  public:
    void Update(int ball_y) {
      if (y + height/2 > ball_y) {
        y  = y - speed;
      }
      if (y + height/2 <= ball_y) {
        y = y + speed;
      }
      LimitMovement();
    }
};

Ball ball; 
Paddle player;
CpuPaddle cpu;

int main() {
  int width = 1280;
  int height = 800;
  int frameRate = 60;
  int radius = 20;

  InitWindow(width, height, "My Pong Game");
  SetTargetFPS(frameRate);

  ball.radius = radius;
  ball.x = width/2;
  ball.y= height/2;
  ball.speed_x = 7;
  ball.speed_y = 7;


  player.width = 25;
  player.height = 120;
  player.x = width - player.width - 10;
  player.y = height / 2 - player.height/2;
  player.speed = 6;

  cpu.width = 25;
  cpu.height = 120;
  cpu.x = 10;
  cpu.y = height / 2 - cpu.height /2 ;
  cpu.speed = 6;

  while(WindowShouldClose() == false) {
    BeginDrawing();

    // Updateing
    ball.Update();
    cpu.Update(ball.y);
    player.Update();


    // Checking for collisions 
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y},ball.radius, Rectangle{player.x, player.y, player.width,player.height})){
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
      ball.speed_x *= -1;
    }

    ClearBackground(Dark_Green);

    DrawRectangle(0,0,width/2, height, Green);
    DrawCircle(width/2,height/2,200, Light_Green);
    DrawLine(width/2,0,width/2,height,WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();
    DrawText(TextFormat("%i", cpu_score), width/4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", player_score),3 * (width/4) - 20, 20, 80, WHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}