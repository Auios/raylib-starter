#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include <string>

int main(void) {
  const int screenWidth = 1280;
  const int screenHeight = 1000;
  InitWindow(screenWidth, screenHeight, "Raylib Starter with ImGui");
  Camera3D camera = {0};
  camera.position = (Vector3){10.0f, 10.0f, 10.0f}; // Camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                              // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;           // Camera mode type

  Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
  SetTargetFPS(60);
  rlImGuiSetup(true);
  bool show_demo_window = true;

  std::string settingsPath = "settings.json";

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_Q)) {
      show_demo_window = !show_demo_window;
    }

    UpdateCamera(&camera, CAMERA_ORBITAL);
    BeginDrawing();
    {
      ClearBackground(BLACK);
      BeginMode3D(camera);
      {
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

        DrawGrid(10, 1.0f);
      }
      EndMode3D();

      DrawText("Press Q to toggle the demo window", 10, 10, 20, WHITE);

      rlImGuiBegin();
      if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
      }
      rlImGuiEnd();
    }
    EndDrawing();
  }
  
  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
