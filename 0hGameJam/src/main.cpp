
// todo get rid of this
#include <vector>

#include "raylib.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256


#define UNIT 32

float rVP()
{
    return (float)GetRandomValue(0.f, SCREEN_WIDTH - UNIT);
}

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "0hGameJam");
    SetTargetFPS(60);

    InitAudioDevice();


    // plants
    Texture2D pTex = LoadTexture("resources/plant.png");

    // clouds
    Texture2D cTex = LoadTexture("resources/cloud.png");

    Texture2D rTex = LoadTexture("resources/rain.png");

	Sound hitS = LoadSound("resources/hit.wav");
	SetSoundVolume(hitS, 0.9f);

	Sound missS = LoadSound("resources/miss.wav");
	SetSoundVolume(missS, 0.9f);
    // game

    int cPs[7] = { 4, 40, 76, 112, 148, 184, 220 };

    int pCps = GetRandomValue(0, 7);
    int pX = cPs[pCps];


    int score = 0;

    int rX = -100;
    bool bIsRaining = false;
    int rCps = 0;

    const int rFRAMES = 5;
    int rFrames = 0;
    

    float timer = 0.f;
    float plantTimer = 0.f;
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // music 

        if (bIsRaining)
        {
            rFrames++;
            if (rFrames > rFRAMES)
            {
                bIsRaining = false;
                rFrames = 0;


                printf("%d %d", pCps, rCps);
                // hit plant
                if (pCps == rCps)
                {
                    pCps = GetRandomValue(0, 7);
                    if (pCps > 6)
                    {
                        pCps = 6;
                    }
                    pX = cPs[pCps];
                    score++;
                    PlaySound(hitS);
                }
                else
                {
                    // miss
                    PlaySound(missS);
                }
            }
        }

        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            float mX = GetMouseX();
            float mY = GetMouseY();
            if (mY > 75 && mY < 75 + UNIT)
            {
                bIsRaining = true;
                rCps = (int)(mX / 36);

                if (rCps > 7)
                {
                    rCps = 7;
                }
                rX = cPs[rCps];
                plantTimer = 0.f;
            }
        }

        timer += GetFrameTime();


        plantTimer += GetFrameTime();
        if (!bIsRaining && plantTimer > 2.f)
        {
            pCps = GetRandomValue(0, 7);
            if (pCps > 6)
            {
                pCps = 6;
            }
            pX = cPs[pCps];
            plantTimer = 0.f;
        }

        // draw
        BeginDrawing();

            ClearBackground(DARKGRAY);

			//DrawLine(MAZE_TILE_SIZE, 0, col * MAZE_TILE_SIZE, SCREEN_HEIGHT, GRAY);

            // daw clouds
            int cX = 32 / 8;
            for (int i = 0; i < 7; i++)
            {
			    DrawTexture(cTex, cX, 75, WHITE);
                cX += (32 / 8) + UNIT;
            }

            // draw plant
			DrawTexture(pTex, pX, SCREEN_HEIGHT - 32, WHITE);

            if (bIsRaining)
            {
			    DrawTexture(rTex, rX, 75 + UNIT, WHITE);
            }
        
            // draw game
            DrawText("Click cloud to make plant happy!", 15, 2, 10, LIGHTGRAY);
            DrawText(TextFormat("Plants watered: %d", score), 20, 25, 10, LIGHTGRAY);
            DrawText(TextFormat("Time: %.2f", timer), 20, 38, 10, LIGHTGRAY);
        
        EndDrawing();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadTexture(test);
    UnloadTexture(pTex);
    UnloadTexture(cTex);
    UnloadTexture(rTex);

    //UnloadMusicStream(test);   // Unload music stream buffers from RAM
    UnloadSound(hitS);
    UnloadSound(missS);

    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
