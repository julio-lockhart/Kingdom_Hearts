/* Sprite Class */
#ifndef SPRITE_H
#define SPRITE_H
#include <string>
using namespace std;

class Sprite
{
	private:
		int spriteIndex; // The sprite index
		int loadIndex; // The load image index
		int blackToAlpha; // Sets black pixels visible/invisible 
		int spriteDepth;
		int visibility;
		int horzFlip, vertFlip;
		string imageFile; // The name of the image file

	public:
		// Constructors
		Sprite();
		Sprite(int, string);
		//Sprite(int, string, int);

		// Mutators
		void createSprite();
		void createSprite( int, int );
		void loadSprite(int, string, int);
		void createSprite(int, string);
		void setVisible( int );
		void setPosition(float, float);
		void setSpriteDepth(int);
		void setImage( int );
		void setFlip( int, int );
		void setX(float);
		void setY(float);
		void deleteSprite();

		// Accessors
		int getSpriteIndex() const;
		string getImageFile() const;
		int getLoadIndex() const;
		int getAlphaToBlack() const;
		float getX() const;
		float getY() const;
		
		// Destructor
		~Sprite();
};

#endif