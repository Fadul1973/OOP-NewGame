#include "Tile.h"



Tile::Tile(int x, int y)
{
   // TODO: add floor maybe
    this->x = x;
    this->y = y;
}

int Tile::GetX() const
{
    return x;
}

int Tile::GetY() const 
{
    return y;
}


bool Tile::IsAtPosition(int x, int y) const
{
    return this->x == x && this->y == y;
}

void Tile::SetX(int x)
{
    this->x = x;
}

void Tile::SetY(int y)
{
    this->y = y;
}
