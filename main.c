#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int boxSize = 20; 

int playerPosX;
int playerPosY;
float playerSize;

int objectivePosX;
int objectivePosY;
float objectiveSize;

struct box{
    int posX;
    int posY;
    bool exists;
    bool isPickedUp;
};

//const int boxListSize = 10;
struct box boxList[10]; //currently the value of 10 is hardcoded in quite a few places (for loops and such)
			//I don't like that but not sure how to make it variable... blegh... things to learn

//run this before we start drawing
void createAllBoxes() {  
   int xCoord;
   int yCoord;	   
   for(int i = 0; i < 10; i++) {
	xCoord = rand() % 770 + 30;
	yCoord = rand() % 420 + 30;
	struct box newBox = {xCoord, yCoord, true, false};
	boxList[i] = newBox;
   }
}

//run this every draw "frame" ? (is that how you say that idk)
void drawAllBoxes() {
    for(int i = 0; i < 10; i++) {
	if(boxList[i].exists)
		DrawRectangle(boxList[i].posX, boxList[i].posY, boxSize, boxSize, BROWN);
    }
}

//checks if the player collides with a box; if yes, updates that box's 'isPickedUp' value
void playerCollisionDetection() {
    int threshold = 7;
    int xDiff;
    int yDiff;
    for(int i = 0; i < 10; i++) {
	if((!boxList[i].isPickedUp)) {
            xDiff = playerPosX - boxList[i].posX - 10;
            yDiff = playerPosY - boxList[i].posY - 10; 
            if((xDiff < threshold && xDiff > -threshold) && (yDiff < threshold && yDiff > -threshold)) 
	        boxList[i].isPickedUp = true;
        }	
    }
}


//checks if the objective collides with a box; if yes, update that box's 'exists' value to false so that it isn't drawn
//i would like to actually remove the struct as well rather than only not draw it. Problem for another time...
void objectiveCollisionDetection() {
    int threshold = 30;
    int xDiff;
    int yDiff;
    for(int i = 0; i < 10; i++) {
	if((boxList[i].exists)) {    
	    xDiff = objectivePosX - boxList[i].posX - 10;
	    yDiff = objectivePosY - boxList[i].posY - 10;
	    if((xDiff < threshold && xDiff > -threshold) && (yDiff < threshold && yDiff > -threshold)) 
		boxList[i].exists = false;
	}
    }
}

//handles movement for player and moves boxes with the isPickedUp value of true
void handleMovement() {
	
    //handle player movement	
    if(IsKeyDown(KEY_UP)) {
	playerPosY--;
    }		    
    if(IsKeyDown(KEY_RIGHT)) {
	playerPosX++;
    }
    if(IsKeyDown(KEY_DOWN)) {
	playerPosY++;
    }
    if(IsKeyDown(KEY_LEFT)) {
	playerPosX--;
    }

    //handle box movement
    //NOTE: when you set it up so that only one box can be carried at a time, you won't want to do movement handling for
    //every box; only the box that is being carried
    for(int i = 0; i < 10; i++) {
	if(boxList[i].isPickedUp) {
	    if(IsKeyDown(KEY_UP)) 
		boxList[i].posY--;

	    if(IsKeyDown(KEY_RIGHT)) 
		boxList[i].posX++;
	        
	    if(IsKeyDown(KEY_DOWN)) 
		boxList[i].posY++;
	    
	    if(IsKeyDown(KEY_LEFT)) 
		boxList[i].posX--;
	}

    }
}

int main() {

    srand(time(NULL));
    
    char *stringOne = "Use the arrow keys to move around!";
    char *stringTwo = "Take the";
    char *stringThree = " box ";
    char *stringFour = "to the";
    char *stringFive = " circle!";
    //char *stringSix = "YOU HAVE WON!!!!";

    const int screenWidth = 800;
    const int screenHeight = 450;

    playerPosX = screenWidth/2;
    playerPosY = screenHeight/2;
    playerSize = 15.0;

    objectivePosX = screenWidth/3 * 2;
    objectivePosY = screenHeight/5 * 3 ;
    objectiveSize = 25.0;

    //create window and set target fps
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    ToggleFullscreen();
    HideCursor();
    SetTargetFPS(144);               

    //create box structs
    createAllBoxes();

    //draw loop
    while (!WindowShouldClose())
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
          
	    //draw the boxes!
	    drawAllBoxes();
	    
	    //movement
	    handleMovement();
           	    
	    //check if player collided with any boxes
	    playerCollisionDetection();

	    //check if any boxes have collided with the objective
	    objectiveCollisionDetection();

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
