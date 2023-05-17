#include "Food.h"
#include "Constants.h"

Food::Food(RandomNumberGenerator* random)
	: Tile(SIZE / 3, SIZE / 3), random(random)
{

}

void Food::SetNewFood(Food& food)
{
	food.SetX(random->GetRandomValue(17));
	food.SetY(random->GetRandomValue(17));
}


