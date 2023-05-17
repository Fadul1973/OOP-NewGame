#pragma once
#include <vector>
#include "Wall.h"

class Level
{
	public:
		// constructor
		Level();

		// getters
		vector<Wall> GetLevel() const;

		// setters
		void SetWallsForLevel(vector<int>wallCoordinates);

	private:
		// data members
		vector<Wall> walls;
};

