#include "Game.h"
#include <stdlib.h>

Game::Game(RandomNumberGenerator* random)
    : food(random), poison(random)
{

}

void Game::Setup()
{
    allLevels.SetUpLevel("Level1");
    allLevels.SetUpLevel("Level2");
    allLevels.SetUpLevel("Level3");
    allLevels.SetUpLevel("Level4");
    allLevels.SetUpLevel("Level5");
    allLevels.SetUpLevel("Level6");
    allLevels.SetUpLevel("Level7");
    allLevels.SetUpLevel("Level8");
    allLevels.SetUpLevel("Level9");
    allLevels.SetUpLevel("Level10");
    allLevels.SetUpLevel("Level11");
    poison.SetX(SIZE - 5);
    poison.SetY(SIZE - 5);
}

void Game::ProcessInput(int key)
{
    player.Move(key);
}

vector<vector<char>> Game::PrepareGrid()
{
    // create the 2D grid
    vector<vector<char>> grid;

    // for each row
    for (int row = 1; row <= SIZE; ++row)
    {
        // create the inner vector to add to the 2D grid
        vector<char> line;

        // for each column, work out what's in that position and add the relevant char to the 2D grid
        for (int col = 1; col <= SIZE; ++col)
        {
            if (row == player.GetY() && col == player.GetX())
            {
                line.push_back(PLAYER);
            }
            else if (player.IsTailAtPosition(col, row))
            {
                line.push_back(TAIL);

            }
            else if (IsWallAtPosition(col, row)) // setting walls
            {
                line.push_back(WALL);
                if (IsFoodPoisonAtPosition(col, row, food)) // if food is on the same location - generate location for food
                {
                    GenerateNewFood(food);
                }
                else if (IsFoodPoisonAtPosition(col, row, poison)) // if poison on the same location - generate location for poison
                {
                    GenerateNewFood(poison);
                }
            }
            else if (IsFoodPoisonAtPosition(col, row, food)) // setting food
            {
                line.push_back(FOOD);
                if (IsFoodPoisonAtPosition(col, row, poison))   // if poison on the same location - generate location for poison
                {
                    GenerateNewFood(poison);
                }
            }
            else if (IsFoodPoisonAtPosition(col, row, poison)) // set up poison
            {
                if (!IsWallAtPosition(col, row) || (!IsFoodPoisonAtPosition(col, row, food))) // if neither food or wall is at position - push poison
                {
                    line.push_back(POISON);
                }
                else
                {
                    GenerateNewFood(poison);
                }
            }
            else
            {
                line.push_back(FLOOR);
            }
        }

        // now that the row is full, add it to the 2D grid
        grid.push_back(line);
    }

    return grid;
}

vector<vector<char>> Game::PrepareNonGamePlayGrid()
{
    // create the 2D grid
    vector<vector<char>> grid;

    // for each row
    for (int row = 1; row <= SIZE; ++row)
    {
        // create the inner vector to add to the 2D grid
        vector<char> line;

        // for each column, work out what's in that position and add the relevant char to the 2D grid
        for (int col = 1; col <= SIZE; ++col)
        {
            line.push_back(FLOOR);
        }

        // now that the row is full, add it to the 2D grid
        grid.push_back(line);

    }
    return grid;
}

void Game::CheckTail()
{
    player.CheckTail();
}

bool Game::IsFoodPoisonAtPosition(int x, int y, Food& f) const
{
    if (f.IsAtPosition(x, y))
    {
        return true;
    }
    return false;
}


bool Game::IsWallAtPosition(int x, int y) const
{
for (size_t i = 0; i < walls.size(); ++i)
{
    if (walls[i].IsAtPosition(x, y))
    {
        return true;
    }
}

return false;
}

void Game::CheckFood()
{
    if (IsFoodPoisonAtPosition(GetPlayerX(), GetPlayerY(), food))
    {      
        player.AddTail(1);
        GenerateNewFood(food);
        AddScore(1);
        
    } else  if (IsFoodPoisonAtPosition(GetPlayerX(), GetPlayerY(), poison))
    {
        player.AddTail(2);
        GenerateNewFood(poison);
        AddScore(2);
    }
}


void Game::GenerateNewFood(Food& f)
{
    f.SetNewFood(f);
}


void Game::KillPlayer()
{
    player.KillPlayer();
}

void Game::UpdateGameStatus()
{
    if (player.IsAlive())
    {
        gameOver = false;
    }
    else
    {
        gameOver = true;
    }
}

void Game::SetPlayerName(string s)
{
    player.SetPlayerName(s);
}

void Game::ResetPlayer()
{
    SetMovement(0);
    player.ResetPlayer();
}

void Game::LoadLevel()
{
    if ((player.GetScore() == 96 && !loadOnce) && levelIndex == -1) // level 1
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = true;
    }
    else if ((player.GetScore() == 192 && !loadOnce) && levelIndex == 0) // level 2
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = true;
    }
    else if ((player.GetScore() == 288 && !loadOnce) && levelIndex == 1) // level 3
    {
        ResetPlayer();
        levelIndex++;
        LoadLevelWalls();
        loadOnce = true;
    }
    else if ((player.GetScore() == 384 && !loadOnce) && levelIndex == 2) // level 4 
    {
        levelIndex++;
        LoadLevelWalls();        
        loadOnce = false;
    }
    else if ((player.GetScore() == 480 && !loadOnce) && levelIndex == 3) // level 5 
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    else if ((player.GetScore() == 586 && !loadOnce) && levelIndex == 4) // level 6 
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    else if ((player.GetScore() == 682 && !loadOnce) && levelIndex == 5) // level 7 
    {
        ResetPlayer();
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    else if ((player.GetScore() == 778 && !loadOnce) && levelIndex == 6) // level 8 
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    else if ((player.GetScore() == 874 && !loadOnce) && levelIndex == 7) // level 9 
    {
        levelIndex++;
        LoadLevelWalls();      
        loadOnce = false;
    }
    else if ((player.GetScore() == 970 && !loadOnce) && levelIndex == 8) // level 10 
    {
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    else if ((player.GetScore() == 1066 && !loadOnce) && levelIndex == 9) // level 11 
    {
        ResetPlayer();
        levelIndex++;
        LoadLevelWalls();
        loadOnce = false;
    }
    
}

void Game::LoadLevelWalls()
{
    walls.clear();
    for each (Wall wall in allLevels.GetSpecificLevel(levelIndex).GetLevel())
    {
        walls.push_back(wall);
    }
}

int Game::GetScore() const
{
    return player.GetScore();
}

int Game::GetMovement() const
{
    return movement;
}

int Game::GetSpeed() const
{
    return speed;
}

int Game::GetLevelIndex() const
{
    return levelIndex;
}

string Game::GetPlayerName() const
{
    return player.GetPlayerName();
}

int Game::GetPlayerX() const
{
    return player.GetX();
}

int Game::GetPlayerY() const
{
    return player.GetY();
}

bool Game::IsRunning() const
{
    if (gameOver)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Game::IsEating()
{
    if (IsFoodPoisonAtPosition(GetPlayerX(), GetPlayerY(), food))
    {
        return true;
    }
    else  if (IsFoodPoisonAtPosition(GetPlayerX(), GetPlayerY(), poison))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::CheckCollision()
{
    if (IsWallAtPosition(GetPlayerX(), GetPlayerY()))
    {     
        KillPlayer();
    }

    if (player.IsTailAtPosition(GetPlayerX(), GetPlayerY()))
    {
        KillPlayer();
    }
}

void Game::AddScore(int x)
{
    player.AddScore(x);
    if (x == 1)
    {
        loadOnce = false;
    }
    else if (x == 2)
    {
        loadOnce = true;
    }
}

void Game::SetMovement(int x)
{
    movement = x;
}

void Game::SetSpeed(int s)
{
    speed = s;
}
