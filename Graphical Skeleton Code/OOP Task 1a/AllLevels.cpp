#include "AllLevels.h"

AllLevels::AllLevels()
{

}

void AllLevels::SetUpLevel(string fileName)
{
    vector<int>readLevel;
    string name = fileName + ".csv";
    int yAxis = 0;
    ifstream file;
    string data;
    file.open(name, ios::in);
    if (file.fail())
        cout << "Levels failed to load";
    else
    {
        while (getline(file, data))
        {

            for (int i = 0; i < 20; i++)
            {
                if (data[i] == 'x')
                {
                    readLevel.push_back(yAxis + 1);
                    readLevel.push_back(i + 1);
                }
            }
            yAxis++;
        }
    }
    file.close();
    Level level;
    level.SetWallsForLevel(readLevel);
    allLevels.push_back(level);
}

Level AllLevels::GetSpecificLevel(int level) const
{
    return allLevels[level];
}