/* MoveableSprite Class */
#ifndef MOVEABLESPRITE_H
#define MOVEABLESPRITE_H
#include "Sprite.h"
#include <string>
using namespace std;

// MoveableSprite declaration
class MoveableSprite : public Sprite
{
	private:
		int distance;
	
	public:
		// Constructors
		MoveableSprite();
		MoveableSprite(int, string, int);
		MoveableSprite(int, string, int, int, int);

		// Mutators and accessors
		void setDistance(int);
		int getDistance() const;

		// Functions to move the sprite
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
};

#endif 