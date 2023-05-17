#include "Tile.h"
#include "RandomNumberGenerator.h"



class Food : public Tile
{
	public:
		Food(RandomNumberGenerator* random);
		void SetNewFood(Food& food);

	private:
		RandomNumberGenerator* random = nullptr;

};