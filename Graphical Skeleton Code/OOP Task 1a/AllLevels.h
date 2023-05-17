#pragma once
#include <vector>
#include "Level.h"
#include <iostream>
#include <string>
#include "Wall.h"
#include <fstream>

using namespace std;

class AllLevels
{
public:
	// constructor
	AllLevels();

	// setters
	void SetUpLevel(string fileName);

	// getters
	Level GetSpecificLevel(int level) const;

private:
	// data members
	vector<Level>allLevels;
};