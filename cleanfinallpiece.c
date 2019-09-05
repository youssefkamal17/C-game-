#include<stdio.h>
#include "raylib.h"
#include<stdlib.h>
#include<time.h>
#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1
#define NUM_MAX_MISSILES     2
//////////////////////////////////////////Globalss///////////////////////////////////////////
int screenWidth = 800;
int screenHeight = 450;
int dimnsion1=235;
int dimnsion2=100;
static int activeEnemies;
static bool gameOver = false;

                   
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY,ENDING } GameScreen;
typedef struct Missiles{
   Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Missiles;
static Missiles missiles[NUM_MAX_MISSILES];
void Initprops(void){
///////////////////////////////Initialize missiles////////////////////////////////////////
       
    for (int i = 0; i < 1; i++)
    {
        missiles[i].rec.width = 135;
        missiles[i].rec.height = 135 ;
        missiles[i].rec.x = GetRandomValue(0, screenWidth);
        missiles[i].rec.y = dimnsion1;
        missiles[i].speed.x = GetRandomValue(10, 15);
        missiles[i].speed.y = 7;
        missiles[i].active = true;
        missiles[i].color = RED;
    } 
}

//////////////////////////////////////Main///////////////////////////////////////////////////
int main(void)
{   //intialising GI textures
    InitWindow(screenWidth, screenHeight, "Gravity Boy -by Youssef Kamal");
    Texture2D menu = LoadTexture("resources/menu2.png"); 
    Texture2D win = LoadTexture("resources/winner2.png");
    Texture2D lose = LoadTexture("resources/lose.png");
    Texture2D logo = LoadTexture("resources/logo.png");
      
    
    Texture2D scarfy = LoadTexture("resources/scarfy.png");     // Texture loading
    Image image = LoadImage("resources/backgamex8.1.png");   // Loaded in CPU memory (RAM)
    ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update) <-- ISSUE
    Texture2D texture = LoadTextureFromImage(image);    // Image converted to texture, GPU memory (VRAM)     
    InitAudioDevice();
    Sound fxOgg = LoadSound("resources/backmusic.ogg"); //music loading 
    
    Vector2 position1 = { 100.0f, 235.0f };
    Vector2 position2 = { 100.0f, 100.0f };
    Vector2 position3 = { 100.0f, 235.0f };
    Vector2 position4 = { 0, 0};
    Vector2 position5 = { 177 ,12};
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height }; //sprite the frames from the spritesheet (character )
    int currentFrame = 0;
    int currentFrame2 = 0;
    Rectangle frameRec2 = { 0.0f, 0.0f, (float)texture.width/8, (float)texture.height }; //sprite the frames from the spritesheet (background)
    int framesCounter = 0;
    int framesCounter6=0;
    int time=0;
    int framesCounter2 = 0;
    int framesSpeed = 7;           // Number of spritesheet frames shown by second
    int framesSpeed2 = 7; 
    int flag =0 ;
    Rectangle rect1 = { 100, 235, (scarfy.width/6)-20, scarfy.height };
        
       
    
            
    
    GameScreen currentScreen = LOGO;
    int framesCounter0 = 0;          
    
    Initprops();
    SetTargetFPS(80);               // Set desired framerate (frames-per-second)
////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    
        switch(currentScreen) 
        {
            case LOGO: 
            {
                
                           
                framesCounter0++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter0 > 120)
                {
                    currentScreen = TITLE;
                    PlaySound(fxOgg);
                }
            } break;
            case TITLE: 
            {
                

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                     
                }
            } break;
            case GAMEPLAY:
            { 

            /////////////////////////////game updates////////////////////////////////////////  
        framesCounter++;
        
        if(time<=4800){
        time++;}
   
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            
            if (currentFrame > 5) currentFrame = 0;
            
            frameRec.x = (float)currentFrame*(float)scarfy.width/6;
           
        }
        framesCounter2++;
        if (framesCounter2 >= (60/framesSpeed2))
        {
            framesCounter2 = 0;
            currentFrame2++;
            
            if (currentFrame2 > 5) currentFrame2 = 0;
            
            
            frameRec2.x = (float)currentFrame2*(float)texture.width/8;
        }
        
        
        
        if (IsKeyPressed(KEY_UP)){
            
            UnloadTexture(scarfy);
            Image image = LoadImage("resources/scarfy.png"); 
            ImageFlipVertical(&image);
            ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);             
            Texture2D scarfyg = LoadTextureFromImage(image);
            position1.y = position2.y ;
            rect1.y=position2.y ;
     
        }
        else if (IsKeyPressed(KEY_DOWN)){
            UnloadTexture(scarfy);
            Image image = LoadImage("resources/scarfy.png"); 
            ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);         
            Texture2D scarfyg = LoadTextureFromImage(image);
            position1.y = position3.y ;
            rect1.y=position3.y ; }


       

if (!gameOver) {
  for (int i = 0; i < NUM_MAX_MISSILES; i++) {
    if (time > 160) {
      if (rect1.x < missiles[i].rec.x + missiles[i].rec.width &&
        rect1.x + rect1.width > missiles[i].rec.x &&
        rect1.y < missiles[i].rec.y + missiles[i].rec.height &&
        rect1.y + rect1.height > missiles[i].rec.y) gameOver = true;
    }
    if (missiles[i].active) {
      missiles[i].rec.x -= missiles[i].speed.x;
      if (missiles[i].rec.x < 0) {
        missiles[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
        int randomValue = GetRandomValue(100, 235);
        if (randomValue != 100 || randomValue != 235) {
          if (abs(randomValue - 100) == abs(randomValue - 235))
            randomValue = 235;
          else if (abs(randomValue - 100) < abs(randomValue - 235))
            randomValue = 100;
          else if (abs(randomValue - 100) > abs(randomValue - 235))
            randomValue = 235;
        }

        missiles[i].rec.y = randomValue;

      }

    }

  }

}

if (gameOver == true) currentScreen = ENDING;
if (time > 4800) currentScreen = ENDING;
            
            
     
            } break;
            case ENDING: 
            {
                time=0;
               if(gameOver)flag=1;
               else flag=0;

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    gameOver = false;
                    currentScreen = TITLE;
                    PlaySound(fxOgg);
                }  
            } break;
            default: break;
        }
     
        

//////////////////////////////////////////Drawing section////////////////////////////////////////
       
BeginDrawing();

ClearBackground(RAYWHITE);

 switch (currentScreen) {
 case LOGO:
   {
     DrawTexture(logo, 0, 0, WHITE);

   }
   break;
 case TITLE:
   {

     DrawTexture(menu, 0, 0, WHITE);

   }
   break;
 case GAMEPLAY:
   {
     DrawTextureRec(texture, frameRec2, position4, WHITE);
     //DrawRectangleRec(rect1,BLACK);

     DrawTextureRec(scarfy, frameRec, position1, RAYWHITE); // Draw part of the texture 
     for (int i = 0; i < 5; i++) {

       if (missiles[i].active) {

         if (time > 160)

           DrawRectangleRec(missiles[i].rec, missiles[i].color);
       }
     }

     DrawRectangle(177, 12, 446, 33, WHITE);

     DrawRectangle(177, 12, 0.0929 * time, 33, YELLOW);

     DrawText(FormatText("SCORE: %d/60", (int) time / 80), 10, 10, 20, BLACK);

   }
   break;
 case ENDING:
   {
     if (flag == 1) DrawTexture(lose, 0, 0, WHITE);
     else if (flag == 0) DrawTexture(win, 0, 0, WHITE);

   }
   break;
 default:
   break;
 }

 EndDrawing();
///////////////////////////////////////////////////////////////////////////////////////////////////
    }

//////////////////////////////////////////De-Initialization////////////////////////////////////////
   
    
    
    CloseWindow();        // Close window and OpenGL context
///////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;
} 
