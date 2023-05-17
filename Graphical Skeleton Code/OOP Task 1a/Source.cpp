#include <iostream>
#include "raylib.h"
#include "Game.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <assert.h>
#include "Constants.h"
#include <fstream>
#include <algorithm>  // for sort() method
#include "RandomNumberGenerator.h"


static int option; // 1 start game, 2 scores, 3 exit

using namespace std;



void checkIfCloseWindow(bool& mainGamePlay, bool& mainMenuActive, bool& mainGameActive, bool& scoreMenuActive, bool& gameOverActive)
{
    if (WindowShouldClose())
    {
         mainGamePlay = false;
         mainMenuActive = false;
         mainGameActive = false;
         scoreMenuActive = false;
         gameOverActive = false;
    }
}


void initGrid(Game& game, Texture2D apple, Texture2D L, Texture2D R, Texture2D U, Texture2D D, Texture2D body, Texture2D grass, Texture2D wall)
{
    const int cellSize = (int)((float)GetScreenHeight() / (float)(SIZE));

    const auto grid = game.PrepareGrid();

    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            int xPosition = x * cellSize;
            int yPosition = y * cellSize;

            switch (grid[y][x])
            {
            case FLOOR:   DrawTexture(grass, xPosition, yPosition, WHITE); break;
            case WALL:    DrawTexture(wall, xPosition, yPosition, WHITE); break;
            case PLAYER:
                if (game.GetMovement() == 1)
                {

                    DrawTexture(R, xPosition, yPosition, WHITE);     break;
                }
                else if (game.GetMovement() == 2)
                {
                    DrawTexture(L, xPosition, yPosition, WHITE);     break;

                }
                else if (game.GetMovement() == 3)
                {

                    DrawTexture(U, xPosition, yPosition, WHITE);     break;
                }
                else if (game.GetMovement() == 4 || game.GetMovement() == 0)
                {
                    DrawTexture(D, xPosition, yPosition, WHITE);     break;

                }
            case TAIL:   DrawTexture(body, xPosition, yPosition, WHITE);     break;
            case POISON: DrawTexture(apple, xPosition, yPosition, WHITE);     break;
            case FOOD:   DrawTexture(apple, xPosition, yPosition, WHITE);     break;

            default:     assert(false);  // if this hits you probably forgot to add your new tile type :)
            }
        }
    }
}

void initNonGamePlayGrid(Game& game)
{
    const int cellSize = (int)((float)GetScreenHeight() / (float)(SIZE));

    const auto grid = game.PrepareNonGamePlayGrid();

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int xPosition = i * cellSize;
            int yPosition = j * cellSize;

            switch (grid[i][j])
            {
            case FLOOR:
            {
                DrawRectangle(xPosition, yPosition, cellSize, cellSize, DARKGREEN); break;
            }
            default:
                break;
            }
        }
    }
}

void displayMainMenu(int option, char*& snake, char*& newGame, char*& allScores, char*& exitText)
{
    this_thread::sleep_for(chrono::milliseconds(120));
    snake = "SNAKE";
    DrawText(snake, 220, 30, 48, BLACK);

    if (option == 1)
    {
        DrawText(newGame, 220, 150, 30, WHITE);
        DrawText(allScores, 220, 200, 30, BLACK);
        DrawText(exitText, 220, 250, 30, BLACK);
    }
    else if (option == 2)
    {
        DrawText(newGame, 220, 150, 30, BLACK);
        DrawText(allScores, 220, 200, 30, WHITE);
        DrawText(exitText, 220, 250, 30, BLACK);
    }
    else if (option == 3)
    {
        DrawText(newGame, 220, 150, 30, BLACK);
        DrawText(allScores, 220, 200, 30, BLACK);
        DrawText(exitText, 220, 250, 30, WHITE);
    }
}

void displayGameOver(char*& snake, Game& game, Rectangle& textBox, char* name)
{
    this_thread::sleep_for(chrono::milliseconds(120));
    snake = "GAME OVER";
    DrawText(snake, 150, 30, 48, BLACK);
    DrawText(TextFormat("YOUR SCORE: %08i", game.GetScore()), 175, 300, 20, BLACK);
    DrawText(TextFormat("ENTER YOUR NAME AND PRESS ENTER"), 95, 120, 20, WHITE);
    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawText("_", textBox.x + 8 + MeasureText(name, 30), textBox.y + 12, 40, BLACK);
    DrawText(name, textBox.x + 5, textBox.y + 8, 40, BLACK);
}

void displayHighestScores(char*& snake, Game& game, vector<Player>& top10List, vector<string>top10Names)
{
    this_thread::sleep_for(chrono::milliseconds(120));
    snake = "    TOP 10";
    DrawText(snake, 150, 30, 48, BLACK);
    DrawText(TextFormat("POS"), 70, 100, 20, BLACK);
    DrawText(TextFormat("NAME"), 200, 100, 20, BLACK);
    DrawText(TextFormat("SCORE"), 350, 100, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 120, 20, BLACK);
    DrawText(TextFormat("1."), 70, 140, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 160, 20, BLACK);
    DrawText(TextFormat("2."), 70, 180, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 200, 20, BLACK);
    DrawText(TextFormat("3."), 70, 220, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 240, 20, BLACK);
    DrawText(TextFormat("4."), 70, 260, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 280, 20, BLACK);
    DrawText(TextFormat("5."), 70, 300, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 320, 20, BLACK);
    DrawText(TextFormat("6."), 70, 340, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 360, 20, BLACK);
    DrawText(TextFormat("7."), 70, 380, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 400, 20, BLACK);
    DrawText(TextFormat("8."), 70, 420, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 440, 20, BLACK);
    DrawText(TextFormat("9."), 70, 460, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 480, 20, BLACK);
    DrawText(TextFormat("10."), 70, 500, 20, BLACK);
    DrawText(TextFormat("----------------------------------------------"), 70, 520, 20, BLACK);
    DrawText(TextFormat("PRESS ENTER TO GO BACK"), 150, 560, 20, WHITE);

    int posY = 140;

    for (int i = 0; i < top10List.size(); i++)
    {
        DrawText(top10Names[i].c_str(), 200, posY, 20, BLACK);
        DrawText(TextFormat("%02i", top10List[i].GetScore()), 350, posY, 20, BLACK);
        posY += 40;
    }
}

void processUserNameInput(char* name, int& key, int& letterCount, Game& game, bool& mainMenuActive, bool& mainGameActive, bool& mainGamePlay)
{
    key = GetKeyPressed();

    while (key > 0)
    {
        // Limit range for allowed keys
        if ((key > 32) && (key < 123) && (letterCount < MAX_INPUT_CHARS))
        {
            name[letterCount] = (char)key;
            letterCount++;
        }

        key = GetKeyPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        name[letterCount] = '\0';
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        if (letterCount > 0)
        {
            mainGamePlay = false;
            game.SetPlayerName(name);
        }
    }
}

void updateAllScores(vector<Player>& allPlayerScores, Game& game)
{
    if (game.GetPlayerName() != "")
    {
        Player player;
        player.SetPlayerName(game.GetPlayerName());
        player.SetScore(game.GetScore());
        allPlayerScores.push_back(player);
    }
}

void updateTop10List(vector<Player> allPlayerScores, vector<Player>& top10List)
{
    top10List.clear();

    vector<int>scores;
    for each (Player player in allPlayerScores) // we get all scores
    {
        scores.push_back(player.GetScore());
    }

    sort(scores.begin(), scores.end()); // sorting scores in ascending order

    while (scores.size() > 10)          // keeps only top 10 scores or whatever the number
    {
        scores.erase(scores.begin());
    }

    int size = scores.size() - 1;       // we get size of scores that we will use to know how many iterations to do on scores

    for (int i = size; i >= 0; i--)
    {
        for (int j = 0; j < allPlayerScores.size(); j++)
        {
            if (scores[i] == allPlayerScores[j].GetScore())
            {
                top10List.push_back(allPlayerScores[j]);
                allPlayerScores.erase(allPlayerScores.begin() + j); // deletes the player object from specified position
                j = allPlayerScores.size();
            }
        }
    }
}

vector<string>getTop10Names(vector<Player>& top10List)
{
    vector<string> top10Names;
    for (int i = 0; i < 10; i++)
    {
        char name[MAX_INPUT_CHARS];
        top10Names.push_back(name);                             // Can't get rid of this warning - when initializing 'name', then a lot of things go very wrong
    }

    for (int x = 0; x < top10List.size(); x++)                  // size becomes 2 (all names)
    {
        int length = top10List[x].GetPlayerName().length();     // length becomes number of chars of name
        string name = top10List[x].GetPlayerName();             // name becomes specific player name
        for (int y = 0; y < length; y++)                        // y is 0 and y is less that number of chars in the name
        {
            top10Names[x][y] = (char)name[y];
            if (y == (length - 1))
            {
                top10Names[x].erase(length);;                   // clean up char array from junk data
            }
        }
    }
    return top10Names;
}

void updateCSVFile(vector<Player>& allPlayerScores, Game& game)
{
    if (game.GetPlayerName() != "")
    {
        ofstream file;
        file.open("scores.csv", ios::out);
        if (file.fail())
            cout << "Issue with file - Please get in touch with your IT deparment" << endl;
        else
        {
            for each (Player player in allPlayerScores)
            {
                file << "Name: " << player.GetPlayerName() << endl;
                file << "Score: " << player.GetScore() << endl;
            }

            file.close();
        }
    }
}

void loadFromFile(vector<Player>& allPlayerScores)
{
    int count = 0;
    Player LoadPlayer;
    ifstream file;
    string data;
    file.open("scores.csv", ios::in);
    if (file.fail())
        exit(0);
    else
    {
        while (getline(file, data))
        {
            count++;
            if (data[0] == 'N')
            {
                data.erase(0, 6);
                LoadPlayer.SetPlayerName(data);
            }
            else if (data[0] == 'S')
            {
                data.erase(0, 7);
                LoadPlayer.SetScore(stoi(data));
            }
            if (count % 2 == 0)
                allPlayerScores.push_back(LoadPlayer);
        }

        file.close();
    }
}

void displayMainGamePlayText(Game& game, char*& snake, int & score)
{
    score = game.GetScore();
    if (game.GetLevelIndex() == 9)
    {
        DrawText("Bonus Round", 220, 30, 48, BLACK);
    }
    DrawText(snake, 220, 30, 48, BLACK);
    DrawText(TextFormat("SCORE: %08i", score), 400, 30, 20, WHITE);
}

void checkMainMenuUserInput(Game& game, Sound& menuSound, bool& mainMenuActive, bool& mainGameActive, bool& scoreMenuActive, bool& mainGamePlay, vector<Player>& allPlayerScores, vector<Player>& top10List)
{
    /*
     * Checking if user is changing selection in main menu
     */
    if (game.IsRunning())
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            PlaySound(menuSound);
            option += 1;
            if (option > 3)
            {
                option = 1;
            }
        }
        else if (IsKeyPressed(KEY_UP))
        {
            PlaySound(menuSound);
            option -= 1;
            if (option < 1)
            {
                option = 3;
            }
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            PlaySound(menuSound);
            if (option == 1)
            {
                mainMenuActive = false;
                mainGameActive = true;
            }
            else if (option == 2)
            {
                mainMenuActive = false;
                scoreMenuActive = true;
                updateTop10List(allPlayerScores, top10List);
            }
            else if (option == 3)
            {
                mainMenuActive = false;
                mainGamePlay = false;
                exit(0);
            }
        }
    }
}

void checkScoresUserInput(Game& game, bool& mainMenuActive, bool& scoreMenuActive)
{
    if (game.IsRunning())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            mainMenuActive = true;
            scoreMenuActive = false;
        }
    }
}

void checkMainGameUserInput(Game& game, char*& snake, Sound moveSound)
{
    if (game.IsRunning())
    {
        if (IsKeyPressed(KEY_RIGHT) && game.GetMovement() != 2) { PlaySound(moveSound);  game.SetMovement(1); }
        if (IsKeyPressed(KEY_LEFT) && game.GetMovement() != 1) { PlaySound(moveSound); game.SetMovement(2); }
        if (IsKeyPressed(KEY_UP) && game.GetMovement() != 4) { PlaySound(moveSound); game.SetMovement(3); }
        if (IsKeyPressed(KEY_DOWN) && game.GetMovement() != 3) { PlaySound(moveSound); game.SetMovement(4); }


        switch (game.GetMovement())
        {
        case 1:
            snake = "";
            this_thread::sleep_for(chrono::milliseconds(game.GetSpeed()));
            game.ProcessInput(KEY_RIGHT);
            break;
        case 2:
            snake = "";
            this_thread::sleep_for(chrono::milliseconds(game.GetSpeed()));
            game.ProcessInput(KEY_LEFT);
            break;
        case 3:
            snake = "";
            this_thread::sleep_for(chrono::milliseconds(game.GetSpeed()));
            game.ProcessInput(KEY_UP);
            break;
        case 4:
            snake = "";
            this_thread::sleep_for(chrono::milliseconds(game.GetSpeed()));
            game.ProcessInput(KEY_DOWN);
            break;
        default:
            break;
        }
    }
}

void updateGame(Game& game, bool& gameOverActive, bool& mainGameActive, Sound& gameOverSound, Sound& eatSound)
{
    game.CheckCollision();
    if (game.IsEating())
    {
        PlaySound(eatSound);
    }
    game.CheckFood();
    game.CheckTail();
    game.UpdateGameStatus();
    game.LoadLevel();

    if (!game.IsRunning())
    {
        mainGameActive = false;
        gameOverActive = true;
        PlaySound(gameOverSound);
    }

}

int main() 
{
    // read scores from file
    vector<Player>allPlayerScores;
    loadFromFile(allPlayerScores);
    vector<Player> top10List;

    char* snake = "SNAKE";
    char* newGame = "NEW GAME";
    char* allScores = "SCORES";
    char* exitText = "EXIT";
    InitWindow(600, 600, "OOP Assignment 1");
    SetTargetFPS(60);

    bool mainGamePlay;
    bool mainMenuActive;
    bool mainGameActive;
    bool scoreMenuActive;
    bool gameOverActive;

    // Textures
    Texture2D apple = LoadTexture("Images/apple2.png");
    Texture2D headL = LoadTexture("Images/head2.png");
    Texture2D headR = LoadTexture("Images/head1.png");
    Texture2D headU = LoadTexture("Images/head3.png");
    Texture2D headD = LoadTexture("Images/head4.png");
    Texture2D body1 = LoadTexture("Images/body1.png");
    Texture2D grass = LoadTexture("Images/grass.png");
    Texture2D wall = LoadTexture("Images/wall.png");

    // Sounds
    Sound eatSound = LoadSound("Sound/eatSound.wav");
    Sound moveSound = LoadSound("Sound/moveSound.wav");
    Sound menuSound = LoadSound("Sound/menuSound.wav");
    Sound gameOverSound = LoadSound("Sound/gameOverSound.wav");

    InitAudioDevice();  // Initialize audio device

    while (!WindowShouldClose())
    {
        mainGamePlay = true;

        option = 1;

        /*
        *Used to decide which screen we are on
        */
        mainMenuActive = true;
        mainGameActive = false;
        scoreMenuActive = false;
        gameOverActive = false;

        // sets up game object
        RandomNumberGenerator random;
        Game game(&random);
        game.Setup();
        int score = game.GetScore();

        // sets up game over object
        Rectangle textBox = { GetScreenWidth() / 2 - 130, 200, 250, 50 }; // struct for input box
        char name[MAX_INPUT_CHARS + 1] = "\0";
        int letterCount = 0;
        int key = 0;

        while (mainGamePlay)
        {
            checkIfCloseWindow(mainGamePlay, mainMenuActive, mainGameActive, scoreMenuActive, gameOverActive);
            if (mainMenuActive)
            {
                BeginDrawing();
                ClearBackground(DARKGRAY);
                checkMainMenuUserInput(game, menuSound, mainMenuActive, mainGameActive, scoreMenuActive, mainGamePlay, allPlayerScores, top10List);
                initNonGamePlayGrid(game);
                displayMainMenu(option, snake, newGame, allScores, exitText);
                EndDrawing();
            }
            else if (scoreMenuActive)
            {
                BeginDrawing();
                ClearBackground(DARKGRAY);
                checkScoresUserInput(game, mainMenuActive, scoreMenuActive);
                initNonGamePlayGrid(game);
                displayHighestScores(snake, game, top10List, getTop10Names(top10List));
                EndDrawing();
            }
            else if (mainGameActive)
            {
                BeginDrawing();
                ClearBackground(DARKGRAY);
                updateGame(game, gameOverActive, mainGameActive, gameOverSound, eatSound);
                checkMainGameUserInput(game, snake, moveSound);
                initGrid(game, apple, headL, headR, headU, headD, body1, grass, wall);
                displayMainGamePlayText(game, snake, score);
                EndDrawing();
            }
            else if (gameOverActive)
            {
                BeginDrawing();
                ClearBackground(DARKGRAY);
                initNonGamePlayGrid(game);
                displayGameOver(snake, game, textBox, name);
                processUserNameInput(name, key, letterCount, game, mainMenuActive, mainGameActive, mainGamePlay);
                updateAllScores(allPlayerScores, game);
                updateCSVFile(allPlayerScores, game);
                EndDrawing();
            }
        }
    }
    CloseAudioDevice();      // Close audio device
    CloseWindow();
    return 0;
}