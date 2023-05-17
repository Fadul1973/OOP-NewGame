#pragma once

#include <assert.h>	
#include <string>		
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "Food.h"
#include "AllLevels.h"
#include "Constants.h"

using namespace std;

class Game
{
   public:    
      // Constructor
       Game(RandomNumberGenerator* random);

      // Accessors
       vector<vector<char>> PrepareGrid();
       vector<vector<char>> PrepareNonGamePlayGrid();
       bool IsRunning() const;
       bool IsEating();
       bool IsWallAtPosition(int x, int y) const;
       bool IsFoodPoisonAtPosition(int x, int y, Food& f) const;
       int GetPlayerX() const;
       int GetPlayerY() const;
       int GetScore() const;
       int GetMovement() const;
       int GetSpeed() const;
       int GetLevelIndex() const;
       string GetPlayerName() const;

       // Mutators
       void Setup();
       void ProcessInput(int key);
       void CheckFood();
       void CheckTail();
       void CheckCollision();
       void AddScore(int x);
       void SetMovement(int x);
       void SetSpeed(int s);
       void GenerateNewFood(Food&food);
       void UpdateGameStatus();
       void SetPlayerName(string s);
       void ResetPlayer();
       void LoadLevel();
       void LoadLevelWalls();
       void KillPlayer();

    protected:
       Player player;
       Food food;
       Food poison;

      
         
    private:
       AllLevels allLevels;
       vector<Wall> walls; // should be a pointer - just could not make it work with other functions that we prepared before considering this
       bool gameOver = false;
       bool loadOnce = false;      
       int movement= 0;
       int speed = 120;
       int levelIndex = -1;


};