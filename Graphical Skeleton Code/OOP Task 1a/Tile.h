#pragma once
class Tile
{
public:


    // constructors
    Tile(int x, int y);

    // assessors
    int GetX() const;
    int GetY() const;
    bool IsAtPosition(int x, int y) const;
    void SetX(int x);
    void SetY(int y);

private:
    // data members
    int x, y;

};

