#include "../include/raylib.h"

#include <iostream>
#include <fstream>

int count = 0;

typedef struct {

    Rectangle rect;
    float xpos, ypos = 0;
    Color color;

} BUTTON;

typedef enum {

    MENU,
    INGAME,
    PAUSED,
    EXITCONFORMATION

} STATE;

STATE currentState = STATE::MENU;

void saveCountValue(int countValue) {

    std::ofstream out_file( "countfile" );
    out_file << countValue;
    out_file.close();

}

int getCountValue(std::string filename){
    
    int final_num = 0;
    
    std::ifstream out_file;
    out_file.open( filename );

    if( !( out_file.is_open() ) ) {
        std::cout << "ERROR: COULDN\'T OPEN FILE TO READ. EXITING.";
        return 1;
    }   

    while ( out_file >> final_num ) {
        std::cout << "READING: " << final_num << "\n";
    }

    out_file.close();

    return final_num;

}

void inMenu(){

    ClearBackground(LIGHTGRAY);

    DrawText("Welcome to \'Clicker\', Press space to play!", ( GetScreenWidth() / 2 ) / 2, ( GetScreenHeight() / 2 ) / 2, 25, BLACK);

    if ( IsKeyPressed( KEY_SPACE ) ) {
        currentState = STATE::INGAME;
    }

    if ( IsKeyPressed( KEY_ESCAPE ) ) {   
        currentState = STATE::EXITCONFORMATION;
    }

}

void inGame() {

    ClearBackground(LIGHTGRAY);

    // Create a button object and assign values to it.
    BUTTON increment_button;

    increment_button.color = BLACK;
    increment_button.xpos = ( ( float ) GetScreenWidth() / 2 ) - 400;
    increment_button.ypos = ( ( float ) GetScreenHeight() / 2 ) / 4;
    increment_button.rect = { increment_button.xpos, increment_button.ypos, 100, 100};

    DrawRectangleRec( increment_button.rect, increment_button.color );

    DrawText ( TextFormat("%i", count), GetScreenWidth() / 2, 125, 25, BLACK );
    DrawText ( "Press CTRL + S to save your points value.", 250, 250, 25, BLACK );
    DrawText ( "Press CTRL + L to load your saved points value.", 250, 275, 25, BLACK );

    // Clicking mechanics
    if (CheckCollisionPointRec( GetMousePosition(), increment_button.rect ) && IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        std::cout << "BUTTON PRESSED. COUNT IS NOW: " << count << "\n";
        count++;
    }

    if ( IsKeyDown( KEY_LEFT_CONTROL ) && IsKeyPressed( KEY_S ) ) {
        std::cout << "\n\n" << "KEY_LEFT_CONTROL && KEY_S DETECTED." << "\n\n";
        saveCountValue(count);
    }

    if ( IsKeyDown( KEY_LEFT_CONTROL ) && IsKeyPressed( KEY_L ) ) {
        std::cout << "\n\n" << "KEY_LEFT_CONTROL && KEY_L DETECTED." << "\n\n";
        count = getCountValue( "countfile" );
    }

    if( IsKeyPressed ( KEY_P ) ) {
        currentState = STATE::PAUSED;
    }

    if ( IsKeyPressed( KEY_ESCAPE ) ) {   
        currentState = STATE::EXITCONFORMATION;
    }

}

void paused() {

    ClearBackground( LIGHTGRAY );

    DrawText( "Game Paused, Press SPACE to continue.", GetScreenWidth() / 2, GetScreenHeight() / 2, 25, BLACK );

    if ( IsKeyPressed( KEY_SPACE ) ) {
        currentState = STATE::INGAME;
    }

    if ( IsKeyPressed( KEY_ESCAPE ) ) {   
        currentState = STATE::EXITCONFORMATION;
    }

}

void confirm_exit() {

    ClearBackground( LIGHTGRAY );

    DrawText("Are you sure you want to exit program? [Y/N]", ( ( GetScreenWidth() / 2 ) / 2 ) - 98, ( ( GetScreenHeight() / 2 ) / 2 ) - 15, 30, BLACK);

    if ( IsKeyPressed( KEY_Y ) ) { CloseWindow(); }
    else if ( IsKeyPressed( KEY_N ) ) { currentState = STATE::INGAME; }
    
}

void initialize() {

    const double screenWidth = 1000;
    const double screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "clicker");

    SetExitKey(KEY_NULL); // To provide confirm exit screen

    while ( !WindowShouldClose() ) {

        BeginDrawing();

        switch ( currentState ) {
            case STATE::MENU:
                // called every frame
                inMenu();
                break;

            case STATE::INGAME:
                inGame();
                break;
            case STATE::PAUSED:
                paused();
                break;
            case STATE::EXITCONFORMATION:
                confirm_exit();
                break;
        }        

        EndDrawing();
        
    }

    CloseWindow();

}




int main( void ) {
    
    SetTargetFPS(69420); // nice.

    initialize();
    
    return 0;
}