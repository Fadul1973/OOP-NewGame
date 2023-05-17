#include "Player.h"


Player::Player() : x(0), y(0), alive(true), dx(0), dy(0)
{
    PositionInMiddleOfGrid();
}

int Player::GetX() const
{
    return x;
}

int Player::GetY() const
{
    return y;
}


bool Player::IsAtPosition(int x, int y) const
{
    return this->x == x && this->y == y;
}

bool Player::IsAlive() const
{
    return alive;
}

string Player::GetPlayerName() const
{
    return name;
}

int Player::GetScore() const
{
    return score;
}

void Player::Move(int key)
{
    switch (key)
    {
    case KEY_LEFT:
        dx = -1;
        dy = 0;
        break;
    case KEY_RIGHT:
        dx = +1;
        dy = 0;
        break;
    case KEY_UP:
        dx = 0;
        dy = -1;
        break;
    case KEY_DOWN:
        dx = 0;
        dy = +1;
        break;
    default:
        // not a key we care about, so do nothing
        break;
    }

    // update mouse coordinates if move is possible
    if (((x + dx) >= 1) && ((x + dx) <= SIZE) && ((y + dy) >= 1) && ((y + dy) <= SIZE))
    {
        UpdatePosition(dx, dy);
    }
    else if (((x + dx) < 1) || ((x + dx) > SIZE))
    {
        UpdatePositionForXAxis();
    }
    else if (((y + dy) < 1) || ((y + dy) > SIZE))
    {
        UpdatePositionForYAxis();
    }
}

void Player::KillPlayer()
{
    alive = false;
}

void Player::AddTail(int x)
{
    tailLength = tailLength + x;
}


void Player::ResetPlayer()
{
    PositionInMiddleOfGrid();
    tailLength = 0;
    for (int i = 0; i < 200; i++) // resets all tale values to 0 - fixed the bug, that when snake is reset to size 0, some part of it randomly uploaded everywhere
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

void Player::SetPlayerName(string n)
{
    name = n;
}

void Player::AddScore(int x)
{
    if (x == 1)
    {
        score += 8;
    }
    else if (x == 2)
    {
      score -= 8;

    }
}

void Player::SetScore(int s)
{
    score = s;
}

void Player::UpdatePosition(int dx, int dy)
{
    
    x += dx;
    y += dy;
}

void Player::UpdatePositionForXAxis()
{
    if (x >= 20)
    {
        x = 1;
    }
    else
    {
        x = 20;
    }
}

void Player::UpdatePositionForYAxis()
{
    if (y >= 20)
    {
        y = 1;
    }
    else
    {
        y = 20;
    }
}

void Player::PositionInMiddleOfGrid()
{
    x = SIZE / 2;
    y = SIZE / 2;
}

void Player::CheckTail()
{

    int previousX = tailX[0]; // previous x co-ordinate of tail
    int previousY = tailY[0]; // previous y co-ordinate of tail
    tailX[0] = x; // positions tail on snake co-ordinate
    tailY[0] = y; // positions tail on snake co-ordinate
    int previous2X, previous2Y; // previous 2 co-ordinates

    for (int i = 1; i < tailLength; i++) // increases length of tail
    {
        previous2X = tailX[i]; // assigns previous 2 co-ordinates
        previous2Y = tailY[i]; // assigns previous 2 co-ordinates
        tailX[i] = previousX; // tail extension = previous x to position next tail
        tailY[i] = previousY; // tail extension = previous y to position next tail
        previousX = previous2X; // moves previous value down
        previousY = previous2Y; // moves previous value down
    }


}

bool Player::IsTailAtPosition(int x, int y) const
{

    for (int i = 0; i < tailLength; i++)
    {
            if (tailX[i] == x && tailY[i] == y)
            {
                return true;
            }
  
    }

    return false;
}
