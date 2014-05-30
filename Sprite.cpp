/* Sprite Class Method */
#include "template.h"
#include "Sprite.h"
#include <string>
using namespace std;

// This is the default constructor for the Sprite
// class. It sets index to 1 and imageFile to
// an empty string.
Sprite::Sprite()
{
   spriteIndex = 1;
   imageFile = "";
}

// This Sprite class constructor accepts as arguments
// the sprite index and the name of the image file,
// and initializes the member variables.
Sprite::Sprite(int index, string filename)
{
   spriteIndex = index;
   imageFile = filename;
}

// The Sprite::createSprite member function 
void Sprite::createSprite()
{
   // If the sprite does not already exist,
   // then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
   }
}

// The Sprite::createSprite member function 
void Sprite::createSprite(int index, string filename)
{
   // Set the member variables.
   spriteIndex = index;
   imageFile = filename;

   // If the sprite does not already exist,
   // then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
   }
}

void Sprite::createSprite( int index, int load )
{
	spriteIndex = index;
	loadIndex = load;

	if (!agk::GetSpriteExists(spriteIndex))
	{
		agk::CreateSprite( spriteIndex, loadIndex );
	}
}

void Sprite::loadSprite( int load, string filename, int alpha )
{
	loadIndex = load;
	imageFile = filename;
	blackToAlpha = alpha;

	agk::LoadImage( loadIndex, imageFile.c_str(), blackToAlpha );
}

void Sprite::setVisible(int visibility)
{
	agk::SetSpriteVisible( spriteIndex, visibility );
}

void Sprite::setSpriteDepth( int spriteDepth )
{
	agk::SetSpriteDepth(spriteIndex, spriteDepth);
}

void Sprite::setFlip( int horzFlip, int vertFlip )
{
	agk::SetSpriteFlip( spriteIndex, horzFlip, vertFlip );
}

void Sprite::setImage( int image )
{
	agk::SetSpriteImage( spriteIndex, image );
}

// The Sprite::setPosition member function sets the
// sprite's position.
void Sprite::setPosition(float x, float y)
{
   agk::SetSpritePosition(spriteIndex, x, y);
}

// The Sprite::setX member function sets the
// sprite's X coordinate.
void Sprite::setX(float x)
{
   agk::SetSpriteX(spriteIndex, x);
}

// The Sprite::setY member function sets the
// sprite's Y coordinate.
void Sprite::setY(float y)
{
   agk::SetSpriteY(spriteIndex, y);
}

void Sprite::deleteSprite()
{
	agk::DeleteSprite( spriteIndex );
}

// The Sprite::getSpriteIndex member function
// returns the sprite's index.
int Sprite::getSpriteIndex() const
{
   return spriteIndex;
}

// The Sprite::getImageFile member function
// returns the name of the image file used to 
// create this sprite.
string Sprite::getImageFile() const
{
   return imageFile;
}

 //The Sprite::getX member function returns the
 //sprite's X coordinate.
float Sprite::getX() const
{
   return agk::GetSpriteX(spriteIndex);
}

// The Sprite::getY member function returns the
// sprite's Y coordinate.
float Sprite::getY() const
{
   return agk::GetSpriteY(spriteIndex);
}

// The Sprite class destructor deletes the
// sprite from memory.
Sprite::~Sprite()
{
   agk::DeleteSprite(spriteIndex);
}