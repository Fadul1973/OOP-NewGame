#include "Level.h"

Level::Level()
{

}

vector<Wall> Level::GetLevel() const
{
	return walls;
}

void Level::SetWallsForLevel(vector<int>wallCoordinates)
{

	for (int i = 0; i < wallCoordinates.size(); i++)
	{
		if (i > 0)
		{
			if (i % 2 == 1)
			{
				walls.push_back(Wall(wallCoordinates[i - 1], wallCoordinates[i]));
			}
		}
	}
}