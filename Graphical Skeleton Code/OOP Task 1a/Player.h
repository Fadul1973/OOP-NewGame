#pragma once

#include "Constants.h"
#include <string>

using namespace std;

class Player
{
    public:
        // constructor
        Player();


        // assessors
        int GetX() const;
        int GetY() const;
        bool IsAtPosition(int x, int y) const;
        bool IsTailAtPosition(int x, int y) const;
        bool IsAlive() const;
        string GetPlayerName() const;
        int GetScore() const;

        void CheckTail();

        // mutators
        void Move(int key);
        void KillPlayer();
        void AddTail(int x);
        void ResetPlayer();
        void SetPlayerName(string n);
        void AddScore(int x);
        void SetScore(int s);
        
    private:
        // data members
        int  x, y;
        string name = "";
        bool alive = true;
        int dx;
        int dy;
        int tailX[200];
        int tailY[200];
        int tailLength = 0;
        int score = 0;

        // supporting functions 
        void PositionInMiddleOfGrid();
        void UpdatePosition(int dx, int dy);
        void UpdatePositionForXAxis();
        void UpdatePositionForYAxis();
};