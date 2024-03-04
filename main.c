#include "include/raylib.h"
#include <stdio.h>

void runDemo() {
    
}

int main() {

    char *stringOne = "Use the arrow keys to move around!";
    char *stringTwo = "Take the";
    char *stringThree = " box ";
    char *stringFour = "to the";
    char *stringFive = " circle!";
    char *stringSix = "YOU HAVE WON!!!!";

    const int screenWidth = 800;
    const int screenHeight = 450;

    int playerPosX = screenWidth/2;
    int playerPosY = screenHeight/2;
    int playerSize = 15.0;

    int boxPosX = screenWidth/3;
    int boxPosY = screenHeight/4 * 3;
    int boxSize = 20;

    int objectivePosX = screenWidth/3 * 2;
    int objectivePosY = screenHeight/5 * 3 ;
    int objectiveSize = 15.0;

    int posYdiff;
    int posXdiff;

    int differenceThreshold = 10;

    bool boxIsPickedUp = false;
    bool objectiveReached = false;

    int timeCounter = 0; //find a better way to implement timers
    bool inEnding = false;
    bool end = false;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    ToggleFullscreen();

    SetTargetFPS(60);               

    while (!WindowShouldClose() && !end)
    {
        BeginDrawing();

            ClearBackground(WHITE);
            
            //draw game instructions
            DrawText(stringOne, screenWidth/3, screenHeight/12 * 1, 10, GRAY);
            DrawText(stringTwo, screenWidth/12 * 4, screenHeight/12 * 2, 10, GRAY);
            DrawText(stringThree, screenWidth/12 * 5, screenHeight/12 * 2, 10, BROWN);
            DrawText(stringFour, screenWidth/12 * 6, screenHeight/12 * 2, 10, GRAY);
            DrawText(stringFive, screenWidth/12 * 7, screenHeight/12 * 2, 10, GREEN);


            //make a little guy and a little box for him and a little green circle for him to take the box to :).
            DrawCircle(objectivePosX, objectivePosY, objectiveSize, GREEN);
            DrawCircle(playerPosX, playerPosY, playerSize, BLACK);
            DrawRectangle(boxPosX, boxPosY, boxSize, boxSize, BROWN);


            //collision detection
            if(!boxIsPickedUp) {
                posYdiff = playerPosY - boxPosY - boxSize/2;
                posXdiff = playerPosX - boxPosX - boxSize/2;
                boxIsPickedUp = ((posYdiff < differenceThreshold && posYdiff > -differenceThreshold) && (posXdiff < differenceThreshold && posXdiff > -differenceThreshold));
            }

            if(!inEnding) {
                //movement controls
                if(IsKeyDown(KEY_UP)) {
                    playerPosY--; //as you go farther down on the Y axis, Y gets larger. interesting
                    if(boxIsPickedUp)
                        boxPosY--;
                }
                if(IsKeyDown(KEY_RIGHT)) {
                    playerPosX++; 
                    if(boxIsPickedUp)
                        boxPosX++;
                }
                if(IsKeyDown(KEY_DOWN)) {
                    playerPosY++; 
                    if(boxIsPickedUp)
                        boxPosY++;
                }
                if(IsKeyDown(KEY_LEFT)) {
                    playerPosX--; 
                    if(boxIsPickedUp)
                        boxPosX--;
                }
            }

            //check if objective is reached (only check when box is picked up since if box isn't picked up, objective literally can't be reached)
            if(boxIsPickedUp) {
                posYdiff = objectivePosY - boxPosY - boxSize/2;
                posXdiff = objectivePosX - boxPosX - boxSize/2;
                objectiveReached = ((posYdiff < differenceThreshold && posYdiff > -differenceThreshold) && (posXdiff < differenceThreshold && posXdiff > -differenceThreshold));
            }

            //check if objective is reached; if yes, trigger ending
            if(objectiveReached) {
                DrawText(stringSix, screenWidth/5, screenHeight/2, 50, GRAY);
                inEnding = true;
                timeCounter++;

                if(timeCounter > 100) {
                    end = true;
                }
            }
            //have an objective that player has to take box to
            //then EndDrawing(); followed by CloseWindow(); if 
            //player position matches objective's position

            //changes happening ayoo!!!!


        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}