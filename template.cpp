/* 
 * Programmer: Julio Lockhart
 * CMPT 464 - 01
 * Final Project
 * Due Date: 4/29/2013
 *
 * This is my version of the PlayStation Hit Game, Kingdom Hearts.
 * The purpose of the game is defeat the boss called Darkside. While
 * attempting to beat the boss, these projectiles, the boss' spells, 
 * will come flying from the right side of the screen to the left.
 * Everytime there is a collision, the characters Hit Points drops
 * one. To attack the boss, you must be colliding with boss, then 
 * press space bar. Every 6th hit ( 6 taps of the space bar ), the 
 * boss' life is dropped by 1. Depending if the user wins or losses,
 * and good ending or bad ending is shown. 
 */

// Includes, namespace and prototypes
#include "template.h"
#include "Sprite.h"
#include "MoveableSprite.h"
#include<String>
using namespace AGK;
app App;

/* Function Prototypes */
void loadImages();
void createImages();
void loadMusic();
void showInstructions();
void mainMenu();
void gameState(MoveableSprite &);
void hideTitleScreen();
void moveSora(MoveableSprite &);
void endGame();
void showGoodEnding();
void showBadEnding();
void setBossSpellsPosition();
void spawnBossSpells();
void detectCollision();
void soraAttack();
void depleteBossHealth();
void hideGameScreens();

/* Resolution */
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 740;

/* Load Image Constants */
const int LOAD_MAIN_IMAGE = 1;
const int LOAD_START_IMAGE = 2;
const int LOAD_INSTRUCTION_IMAGE = 3;
const int LOAD_INSTRUCTIONS_BUTTON_IMAGE = 4;	
const int LOAD_BACKGROUND = 5;
const int LOAD_SORA_STANCE = 6;
const int LOAD_DARKSIDE = 7;
const int LOAD_SORA_NORMAL = 8;
const int LOAD_SORA_CRITICAL = 9;
const int LOAD_BOSS_ATTACK1 = 10;
const int LOAD_BOSS_ATTACK2 = 11;
const int LOAD_BOSS_ATTACK3 = 12;
const int LOAD_BOSS_ATTACK4 = 13;
const int LOAD_BOSS_ATTACK5 = 14;
const int LOAD_BOSS_ATTACK6 = 15;
const int LOAD_HEALTH_BAR1 = 24;
const int LOAD_HEALTH_BAR2 = 25;
const int LOAD_HEALTH_BAR3 = 26;
const int LOAD_HEALTH_BAR4 = 27;
const int LOAD_HEALTH_BAR5 = 28;
const int LOAD_HEALTH_BAR6 = 29;
const int LOAD_HEALTH_BAR7 = 30;
const int LOAD_HEALTH_BAR8 = 31;
const int LOAD_HEALTH_BAR9 = 32;
const int LOAD_HEALTH_BAR10 = 33;
const int LOAD_HEALTH_BAR11 = 34;
const int LOAD_HEALTH_BAR12 = 35;
const int LOAD_HEALTH_BAR13 = 36;
const int LOAD_HEALTH_BAR14 = 37;
const int LOAD_HEALTH_BAR15 = 38;
const int LOAD_HEALTH_BAR16 = 39;
const int LOAD_BOSS_HEALTH = 40;
const int LOAD_BOSS_HEALTH2 = 41;
const int LOAD_BOSS_HEALTH3 = 42;
const int LOAD_BOSS_HEALTH4 = 43;
const int LOAD_BOSS_HEALTH5 = 44;
const int LOAD_BOSS_HEALTH6 = 45;
const int LOAD_BOSS_HEALTH7 = 46;
const int LOAD_BOSS_HEALTH8 = 47;
const int LOAD_BOSS_HEALTH9 = 49;
const int LOAD_BOSS_HEALTH10 = 50;
const int LOAD_BOSS_HEALTH11 = 51;
const int LOAD_BOSS_HEALTH12 = 52;
const int LOAD_BOSS_HEALTH13 = 53;
const int LOAD_BOSS_HEALTH14 = 54;
const int LOAD_BOSS_HEALTH15 = 55;
const int LOAD_BOSS_HEALTH16 = 56;
const int LOAD_BOSS_HEALTH17 = 57;
const int LOAD_BOSS_HEALTH18 = 58;
const int LOAD_BOSS_HEALTH19 = 59;
const int LOAD_BOSS_HEALTH20 = 60;
const int LOAD_BAD_ENDING = 61;
const int LOAD_GOOD_ENDING = 71;
const int LOAD_SORA_DEAD = 73;
const int LOAD_ATTACK1 = 74;
const int LOAD_ATTACK2 = 75;
const int LOAD_ATTACK3 = 76;
const int LOAD_ATTACK4 = 77;
const int LOAD_ATTACK5 = 78;
const int LOAD_ATTACK6 = 79;
const int LOAD_GAME_MENU = 80;

/* Sprite Index Constants */
const int MAIN_IMAGE = 1;
const int START_IMAGE = 2;
const int INSTRUCTION_IMAGE = 3;
const int BATTLE_BACKGROUND = 4;
const int SORA_STANCE = 5;
const int DARKSIDE = 6;
const int NORMAL_HUD = 7;
const int BOSS_ATTACK1 = 11;
const int BOSS_ATTACK2 = 12;
const int BOSS_ATTACK3 = 13;
const int BOSS_ATTACK4 = 14;
const int BOSS_ATTACK5 = 15;
const int BOSS_ATTACK6 = 16;
const int GAME_MENU = 23;
const int HEALTH_BAR1 = 27;
const int BOSS_HEALTH1 = 28;
const int INSTRUCTION_BUTTON = 50;
const int GAME_OVER_BAD = 37;
const int GAME_OVER_GOOD = 38;

/* Sprite Depth */
const int MAX_DEPTH = 1000;
const int MIN_DEPTH = 0;

/* Sprite Positioning */
const float START_BUTTON_X = 50;
const float START_BUTTON_Y = 550;
const float INSTRUCTION_IMAGE_X = 50;
const float INSTRUCTION_IMAGE_Y = 650;
const float SORA_START_X = 200;
const float SORA_START_Y = 600;
const float DARKSIDE_START_X = 550;
const float DARKSIDE_START_Y = (SCREEN_HEIGHT) - 420;
const float NORMAL_HUD_X = 920;
const float NORMAL_HUD_Y = 560;

/* Random Constants */
const int RANDOM_X_MIN	= 640;
const int RANDOM_X_MAX	= 1280;
const int RANDOM_Y_MIN	= 0;
const int RANDOM_Y_MAX	= SCREEN_HEIGHT;

/* Game States */
const int MAIN_STATE = 1;
const int GAME_STATE = 2;
const int BAD_GAME_OVER_STATE = 3;
const int GOOD_GAME_OVER_STATE = 4;

/* Sound Index */
const int MAIN_THEME = 1;
const int BATTLE_THEME = 2;
const int END_THEME = 3;
const int LOW_HEALTH = 4;
const int HIT_SOUND = 5;
const int HURT_SOUND = 6;
const int BOSS_SOUND = 7;
const int BOSS_SAYING = 8;
const int BOSS_SAYING2 = 9;

/* Global Constants */
int g_gameState = MAIN_STATE;
const int SONG_LOOP = 1;
const int INVISIBLE = 0;
const int VISIBLE = 1;
const int HIDE_BLACK_PIXELS = 1;
const int SORA_SPEED = 5;
const int UPDATE_MIN = 0;
const int ARRAY_SIZE = 6;
const int ATTACK_SPEED = 4;
const int OFFSCREEN	= -100;

/* Global Counters */
int COUNT_SORA_HP = 0;
int COUNT_BOSS_HP = 0;
int ATTACK_COUNTER = 0;
bool collision1 = false;
bool collision2 = false;
bool collision3 = false;
bool collision4 = false;
bool collision5 = false;
bool collision6 = false;

/* Instances of Sprite and Moveable Sprite Classes */
Sprite darkside( DARKSIDE, "Images/Darkside.png" );
MoveableSprite sora(SORA_STANCE, "Images/sora_stance.png", SORA_SPEED);
MoveableSprite bossSpells[ARRAY_SIZE];

// Begin app, called once at the start
void app::Begin( void )
{
	/* Set Resolution */
	agk::SetVirtualResolution( SCREEN_WIDTH, SCREEN_HEIGHT );

	/* Set Title */
	agk::SetWindowTitle( "Kingdom Hearts" );

	/* Load Music, Images and create the images */
	loadMusic();
	loadImages();
	createImages();
}

// Main loop, called every frame
void app::Loop ( void )
{
	switch(g_gameState)
	{	
		/* Main Menu State */
		case MAIN_STATE:
			mainMenu();

			/* If enter is pressed, start the game */
			if( agk::GetRawKeyPressed( AGK_KEY_ENTER ) )
			{
				hideTitleScreen();
				g_gameState = GAME_STATE;
			}

			break;
		
		/* Playing Game State */
		case GAME_STATE:
			/* Sets Main Menu invisible, and battle ground visible */
			gameState( sora );
			/* Allows user to move character */
			moveSora( sora ); 
			/* Spawns Boss Attacks */
			spawnBossSpells(); 
			/* Detect Collision with Boss attacks and Main Character */
			detectCollision();
			/* Attack Sequence of Sora */
			soraAttack();
			/* Determines boss health */
			depleteBossHealth();
			/* Determines which ending to show */
			endGame();

			break;

		case GOOD_GAME_OVER_STATE:	
			showGoodEnding();
			break;

		case BAD_GAME_OVER_STATE:
			showBadEnding();
			break;
	}

	/* Sync AGK */
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

/* Load Images */
void loadImages()
{
	/* Characters */
	sora.loadSprite( LOAD_SORA_STANCE, "Images/sora_stance.png", 
		HIDE_BLACK_PIXELS );
	darkside.loadSprite( LOAD_DARKSIDE, "Images/darkside.png", 
		HIDE_BLACK_PIXELS );

	/* Load: Main Menu */
	agk::LoadImage( LOAD_MAIN_IMAGE, "Images/main_menu.png" );
	agk::LoadImage( LOAD_START_IMAGE, "Images/start_button.png" );
	agk::LoadImage( LOAD_INSTRUCTIONS_BUTTON_IMAGE, 
		"Images/instruction_button.png" );
	agk::LoadImage( LOAD_INSTRUCTION_IMAGE, "Images/instruction.png" );
	
	/* Load: Battle Background */
	agk::LoadImage( LOAD_BACKGROUND, "Images/mickeysthrone.png" );

	/* Load: Battle Stage - Sora Sprites */
	agk::LoadImage( LOAD_SORA_NORMAL, "Images/sora_normal.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_SORA_DEAD, "Images/sora_dead.png",
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_SORA_CRITICAL, "Images/sora_critical.png", 
		HIDE_BLACK_PIXELS);
	agk::LoadImage( LOAD_GAME_MENU, "Images/menu.png", 
		HIDE_BLACK_PIXELS );
	
	/* Load: Battle Stage - Boss Sprites */
	bossSpells[0].loadSprite( LOAD_BOSS_ATTACK1, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );
	bossSpells[1].loadSprite( LOAD_BOSS_ATTACK2, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );
	bossSpells[2].loadSprite( LOAD_BOSS_ATTACK3, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );
	bossSpells[3].loadSprite( LOAD_BOSS_ATTACK4, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );
	bossSpells[4].loadSprite( LOAD_BOSS_ATTACK5, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );
	bossSpells[5].loadSprite( LOAD_BOSS_ATTACK6, 
		"Images/boss_attack.png", HIDE_BLACK_PIXELS );

	/* Load: Battle Stage - Sora's Health */
	agk::LoadImage( LOAD_HEALTH_BAR1, "Images/health_bar.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR2, "Images/health_bar2.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR3, "Images/health_bar3.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR4, "Images/health_bar4.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR5, "Images/health_bar5.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR6, "Images/health_bar6.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR7, "Images/health_bar7.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR8, "Images/health_bar8.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR9, "Images/health_bar9.png",
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR10, "Images/health_bar10.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR11, "Images/health_bar11.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR12, "Images/health_bar12.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR13, "Images/health_bar13.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR14, "Images/health_bar14.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR15, "Images/health_bar15.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_HEALTH_BAR16, "Images/health_bar16.png", 
		HIDE_BLACK_PIXELS );

	/* Load: Battle Stage - Boss' Health */
	agk::LoadImage( LOAD_BOSS_HEALTH, "Images/boss_health.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH2, "Images/boss_health2.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH3, "Images/boss_health3.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH4, "Images/boss_health4.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH5, "Images/boss_health5.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH6, "Images/boss_health6.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH7, "Images/boss_health7.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH8, "Images/boss_health8.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH9, "Images/boss_health9.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH10, "Images/boss_health10.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH11, "Images/boss_health11.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH12, "Images/boss_health12.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH13, "Images/boss_health13.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH14, "Images/boss_health14.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH15, "Images/boss_health15.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH16, "Images/boss_health16.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH17, "Images/boss_health17.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH18, "Images/boss_health18.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH19, "Images/boss_health19.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_BOSS_HEALTH20, "Images/boss_health20.png", 
		HIDE_BLACK_PIXELS );
	
	/* Load Attack Sequence Images */
	agk::LoadImage( LOAD_ATTACK1, "Images/attack1.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_ATTACK2, "Images/attack2.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_ATTACK3, "Images/attack3.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_ATTACK4, "Images/attack4.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_ATTACK5, "Images/attack5.png", 
		HIDE_BLACK_PIXELS );
	agk::LoadImage( LOAD_ATTACK6, "Images/attack6.png", 
		HIDE_BLACK_PIXELS );

	/* Load Good and Bad ending images */
	agk::LoadImage( LOAD_BAD_ENDING, "Images/game_over_bad.png" );
	agk::LoadImage( LOAD_GOOD_ENDING, "Images/game_over_good.png" );
}

/* Create Images and set Depth, Visibility and Position */
void createImages()
{
	/* Characters */
	sora.createSprite( SORA_STANCE, LOAD_SORA_STANCE );
	sora.setVisible( INVISIBLE );
	sora.setSpriteDepth( 0 );
	sora.setFlip( 0, 0 );
	sora.setPosition( SORA_START_X, SORA_START_Y );

	darkside.createSprite( DARKSIDE, LOAD_DARKSIDE );
	darkside.setVisible( INVISIBLE );
	darkside.setSpriteDepth( 500 );
	darkside.setFlip( 1, 0 );
	darkside.setPosition( DARKSIDE_START_X, DARKSIDE_START_Y );

	/* Battle State */
	agk::CreateSprite( BATTLE_BACKGROUND, LOAD_BACKGROUND );
	agk::SetSpriteVisible( BATTLE_BACKGROUND, INVISIBLE );
	agk::SetSpriteDepth( BATTLE_BACKGROUND, 1000 );

	agk::CreateSprite( NORMAL_HUD, LOAD_SORA_NORMAL );
	agk::SetSpriteVisible( NORMAL_HUD, INVISIBLE );
	agk::SetSpriteDepth( NORMAL_HUD, 0 );
	agk::SetSpritePosition(NORMAL_HUD, NORMAL_HUD_X, NORMAL_HUD_Y);

	agk::CreateSprite( BOSS_HEALTH1, LOAD_BOSS_HEALTH );
	agk::SetSpriteVisible( BOSS_HEALTH1, INVISIBLE );
	agk::SetSpriteDepth( BOSS_HEALTH1, 0 );
	agk::SetSpritePosition(BOSS_HEALTH1, 700, 0);

	/* Create Boss Attack Sprites */
	bossSpells[0].createSprite( BOSS_ATTACK1, LOAD_BOSS_ATTACK1 );
	bossSpells[0].setVisible( INVISIBLE );

	bossSpells[1].createSprite( BOSS_ATTACK2, LOAD_BOSS_ATTACK2 );
	bossSpells[1].setVisible( INVISIBLE );

	bossSpells[2].createSprite( BOSS_ATTACK3, LOAD_BOSS_ATTACK3 );
	bossSpells[2].setVisible( INVISIBLE );

	bossSpells[3].createSprite( BOSS_ATTACK4, LOAD_BOSS_ATTACK4 );
	bossSpells[3].setVisible( INVISIBLE );

	bossSpells[4].createSprite( BOSS_ATTACK5, LOAD_BOSS_ATTACK5 );
	bossSpells[4].setVisible( INVISIBLE );

	bossSpells[5].createSprite( BOSS_ATTACK6, LOAD_BOSS_ATTACK6 );
	bossSpells[5].setVisible( INVISIBLE );

	for( int i = 0; i < 6; i++ )
	{
		bossSpells[i].setSpriteDepth( 1000 );
	}

	agk::CreateSprite( GAME_MENU, LOAD_GAME_MENU );
	agk::SetSpriteVisible( GAME_MENU, INVISIBLE );

	agk::CreateSprite( HEALTH_BAR1, LOAD_HEALTH_BAR1 );
	agk::SetSpriteVisible( HEALTH_BAR1, INVISIBLE );

	agk::CreateSprite( GAME_OVER_BAD, LOAD_BAD_ENDING );
	agk::SetSpriteVisible(GAME_OVER_BAD, INVISIBLE);
	agk::SetSpriteDepth(GAME_OVER_BAD, 1000);

	agk::CreateSprite( GAME_OVER_GOOD, LOAD_GOOD_ENDING );
	agk::SetSpriteVisible(GAME_OVER_GOOD, INVISIBLE);
	agk::SetSpriteDepth(GAME_OVER_GOOD, 1000);

}

/* Show Main Menu */
void mainMenu()
{
	if( !agk::GetMusicPlaying() )
		agk::PlayMusic( MAIN_THEME, SONG_LOOP );

	agk::CreateSprite( MAIN_IMAGE, LOAD_MAIN_IMAGE );
	agk::SetSpriteDepth( MAIN_IMAGE, MAX_DEPTH );

	agk::CreateSprite( START_IMAGE, LOAD_START_IMAGE );
	agk::SetSpriteDepth( START_IMAGE, MAX_DEPTH );
	agk::SetSpritePosition( START_IMAGE, START_BUTTON_X, 
		START_BUTTON_Y );

	agk::CreateSprite( INSTRUCTION_BUTTON, 
		LOAD_INSTRUCTIONS_BUTTON_IMAGE );
	agk::SetSpriteDepth( INSTRUCTION_BUTTON, 1000 );
	agk::SetSpritePosition( INSTRUCTION_BUTTON, 
		START_BUTTON_X, START_BUTTON_Y + 100 );

	if( agk::GetRawKeyPressed( AGK_KEY_SPACE ) )
	{
		agk::SetSpriteVisible( START_IMAGE, INVISIBLE );
		agk::SetSpriteVisible( MAIN_IMAGE, INVISIBLE );

		agk::CreateSprite( INSTRUCTION_IMAGE, LOAD_INSTRUCTION_IMAGE );
		agk::SetSpriteDepth( INSTRUCTION_IMAGE, 1000 );
	}
}

/* Set Initial Position of Boss Attacks */
void setBossSpellsPosition()
{	
	for( int i = 0; i < ARRAY_SIZE; i++ )
	{
		float randomX = agk::Random( RANDOM_X_MIN, RANDOM_X_MAX );
		float randomY = agk::Random( RANDOM_Y_MIN, RANDOM_Y_MAX );
		bossSpells[i].setPosition( randomX, randomY );
	}
}
 
/* Spawn the boss Spells */
void spawnBossSpells()
{
	/* Random X and Y values */
	float randomX = agk::Random( RANDOM_X_MIN, RANDOM_X_MAX );
	float randomY = agk::Random( RANDOM_Y_MIN, RANDOM_Y_MAX );

	int attack1 = bossSpells[0].getX();
	int attack2 = bossSpells[1].getX();
	int attack3 = bossSpells[2].getX();
	int attack4 = bossSpells[3].getX();
	int attack5 = bossSpells[4].getX();
	int attack6 = bossSpells[5].getX();

	/* Collision# is a global boolean. Determines if character has
	 * been hit or not. Resets when Sprite goes off screen */
	if( bossSpells[0].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[0].getSpriteIndex(), 
			randomX, randomY );
		collision1 = false;
	}
	else if( bossSpells[1].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[1].getSpriteIndex(), 
			randomX, randomY );
		collision2 = false;
	}
	else if( bossSpells[2].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[2].getSpriteIndex(), 
			randomX, randomY );
		collision3 = false;
	}
	else if( bossSpells[3].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[3].getSpriteIndex(), 
			randomX, randomY );
		collision4 = false;
	}
	else if( bossSpells[4].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[4].getSpriteIndex(), 
			randomX, randomY );
		collision5 = false;
	}
	else if( bossSpells[5].getX() < OFFSCREEN )
	{
		agk::SetSpritePosition( bossSpells[5].getSpriteIndex(), 
			randomX, randomY );
		collision6 = false;
	}
	else
	{
		bossSpells[0].setX( attack1 - ATTACK_SPEED );
		bossSpells[1].setX( attack2 - ATTACK_SPEED );
		bossSpells[2].setX( attack3 - ATTACK_SPEED );
		bossSpells[3].setX( attack4 - ATTACK_SPEED );
		bossSpells[4].setX( attack5 - ATTACK_SPEED );
		bossSpells[5].setX( attack5 - ATTACK_SPEED );
	}
}


/* Load Music */
void loadMusic()
{
	agk::LoadMusic( MAIN_THEME, "Music/main_theme.mp3" );
	agk::LoadMusic( BATTLE_THEME, "Music/battle_music.mp3" );
	agk::LoadMusic( END_THEME, "Music/ending_theme.mp3" );
	agk::LoadSound( LOW_HEALTH, "Music/low_health.wav" );
	agk::LoadSound( HIT_SOUND, "Music/hit_sound.wav" );
	agk::LoadSound( HURT_SOUND, "Music/hurt_sound.wav" );
	agk::LoadSound( BOSS_SOUND, "Music/boss_sound.wav" );
	agk::LoadSound( BOSS_SAYING, "Music/boss_saying.wav" );
	agk::LoadSound( BOSS_SAYING2, "Music/boss_saying2.wav" );
}

/* Hides the Main Menu */
void hideTitleScreen()
{
	agk::StopMusic();
	
	agk::SetSpriteVisible( START_IMAGE, INVISIBLE );
	agk::SetSpriteVisible( INSTRUCTION_BUTTON, INVISIBLE );
	agk::SetSpriteVisible( MAIN_IMAGE, INVISIBLE );
	agk::SetSpriteVisible( INSTRUCTION_IMAGE, INVISIBLE );
}

/* Game has begun state */
void gameState(MoveableSprite &sora)
{
	if( !agk::GetMusicPlaying() )
		agk::PlayMusic( BATTLE_THEME, 1 );

	agk::SetSpriteVisible( START_IMAGE, INVISIBLE );
	agk::SetSpriteVisible( MAIN_IMAGE, INVISIBLE );
	agk::SetSpriteVisible( INSTRUCTION_IMAGE, INVISIBLE );

	agk::SetSpriteVisible( BATTLE_BACKGROUND, VISIBLE );
	agk::SetSpriteVisible( SORA_STANCE, VISIBLE );
	agk::SetSpriteVisible( DARKSIDE, VISIBLE );
	agk::SetSpriteVisible( NORMAL_HUD, VISIBLE );

	agk::SetSpriteVisible( BOSS_ATTACK1, VISIBLE );
	agk::SetSpriteVisible( BOSS_ATTACK2, VISIBLE );
	agk::SetSpriteVisible( BOSS_ATTACK3, VISIBLE );
	agk::SetSpriteVisible( BOSS_ATTACK4, VISIBLE );
	agk::SetSpriteVisible( BOSS_ATTACK5, VISIBLE );
	agk::SetSpriteVisible( BOSS_ATTACK6, VISIBLE );

	agk::SetSpriteVisible( GAME_MENU, VISIBLE );

	agk::SetSpriteVisible( HEALTH_BAR1, VISIBLE );
	agk::SetSpritePosition( HEALTH_BAR1, 750, 530 );

	agk::SetSpriteVisible( BOSS_HEALTH1, VISIBLE );

	agk::SetSpritePosition(GAME_MENU, 40, 600);
}

/* Allows user to move character around */
void moveSora(MoveableSprite &sora)
{
	//Get the direction as input from the keyboard.
	float directionX = agk::GetDirectionX();
	float directionY = agk::GetDirectionY();

	/* Get coordinates of Sprite: Sora_Stance */
	float xCoor = agk::GetSpriteX( SORA_STANCE );
	float yCoor = agk::GetSpriteY( SORA_STANCE );

    //Check for left/right arrow keys.
	if (directionX < UPDATE_MIN)
	{
		sora.moveLeft();
		agk::SetSpriteFlip( SORA_STANCE, 1, 0 );
	}
	else if (directionX > UPDATE_MIN)
	{
		sora.moveRight();
	}
	else
	{
		agk::SetSpriteFlip( SORA_STANCE, 0, 0 );
	}

    //Check for up/down arrow keys.
	if (directionY < UPDATE_MIN)
	{
		sora.moveUp();
	}
	else if (directionY > UPDATE_MIN)
	{
		sora.moveDown();
	}
}

/* Detects Collision between Boss's Attacks and Character */
void detectCollision()
{
	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK1 ) 
		&& collision1 == false )
	{
		collision1 = true;

		if( collision1 )
		{
			/* Decrease Sora's Health */
			COUNT_SORA_HP++;
			/* If Sora gets hit while attacking, reset animation to 0
			 * Similar to a recoil */
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK2 ) 
		&& collision2 == false )
	{
		collision2 = true;

		if( collision2 )
		{
			COUNT_SORA_HP++;
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK3 ) 
		&& collision3 == false )
	{
		collision3 = true;

		if( collision3 )
		{
			COUNT_SORA_HP++;
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK4 ) 
		&& collision4 == false )
	{
		collision4 = true;

		if( collision4 )
		{
			COUNT_SORA_HP++;
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK5 ) 
		&& collision5 == false )
	{
		collision5 = true;

		if( collision5 )
		{
			COUNT_SORA_HP++;
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( agk::GetSpriteCollision( SORA_STANCE, BOSS_ATTACK6 ) 
		&& collision6 == false )
	{
		collision6 = true;

		if( collision6 )
		{
			COUNT_SORA_HP++;
			ATTACK_COUNTER = 0;
			agk::PlaySound( HURT_SOUND );
		}
	}

	if( COUNT_SORA_HP >= 11 )
	{
		agk::PlaySound( LOW_HEALTH );
		agk::SetSpriteImage( NORMAL_HUD, LOAD_SORA_CRITICAL );
	}

	/* Show appropriate Health Bar depending on number of times hit */ 
	switch(COUNT_SORA_HP)
	{
		case 1:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR2);
			break;
		case 2:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR3);
			break;
		case 3:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR4);
			break;
		case 4:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR5);
			break;
		case 5:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR6);
			break;
		case 6:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR7);
			break;
		case 7:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR8);
			break;
		case 8:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR9);
			break;
		case 9:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR10);
			break;
		case 10:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR11);
			break;
		case 11:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR12);
			break;
		case 12:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR13);
			break;
		case 13:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR14);
			break;
		case 14:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR15);
			break;
		case 15:
			agk::SetSpriteImage(HEALTH_BAR1, LOAD_HEALTH_BAR16);
			break;

	}
}

/* Allows user to attack */
void soraAttack()
{
	/* Check if the user is colliding with the boss */
	if( agk::GetSpriteCollision(SORA_STANCE, DARKSIDE) )
	{
		/* If Space Bar is pressed, start attack sequence */
		if( agk::GetRawKeyPressed( AGK_KEY_SPACE ) )
		{
			/* Increase Hit Counter */
			agk::PlaySound( HIT_SOUND );
			ATTACK_COUNTER++;
		}
	}

	/* Every 6th hit, decrease the Boss' HP by 1 */
	if( ATTACK_COUNTER == 6 )
	{
		agk::PlaySound( BOSS_SOUND );
		COUNT_BOSS_HP++;
		ATTACK_COUNTER = 0;
	}

	/* Everytime the space bar is pressed, a counter is increased by 1.
	 * Each case represents a new image being shown of the character 
	 * attacking */
	switch( ATTACK_COUNTER )
	{
		case 1:
			sora.setImage( LOAD_ATTACK1 );
			break;
		case 2:
			sora.setImage( LOAD_ATTACK2 );
			break;
		case 3:
			sora.setImage( LOAD_ATTACK3 );
			break;
		case 4:
			sora.setImage( LOAD_ATTACK4 );
			break;
		case 5:
			sora.setImage( LOAD_ATTACK5 );
			break;
		case 6:
			sora.setImage( LOAD_ATTACK6 );
			break;
		default:
			sora.setImage( LOAD_SORA_STANCE );
	}
}

/* For every 6th hit from the user, decrease the boss' health
 * by 1. This will show the appropriate image of the boss'
 * health depleting. */
void depleteBossHealth()
{
	switch(COUNT_BOSS_HP)
	{
		case 1:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH2);
			break;
		case 2:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH3);
			break;
		case 3:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH4);
			break;
		case 4:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH5);
			break;
		case 5:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH6);
			break;
		case 6:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH7);
			break;
		case 7:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH8);
			break;
		case 8:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH9);
			break;
		case 9:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH10);
			break;
		case 10:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH11);
			break;
		case 11:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH12);
			break;
		case 12:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH13);
			break;
		case 13:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH14);
			break;
		case 14:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH15);
			break;
		case 15:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH16);
			break;
		case 16:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH16);
			break;
		case 17:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH17);
			break;
		case 18:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH18);
			break;
		case 19:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH19);
			break;
		case 20:
			agk::SetSpriteImage(BOSS_HEALTH1, LOAD_BOSS_HEALTH20);
			break;
	}
}

/* Determins weather or not user wins or losses */
void endGame()
{
	/* User has 15 Hit Points, if counter is equal to 15,
	 * switch game state to bad state */
	if( COUNT_SORA_HP == 15 )
	{
		sora.setImage( LOAD_SORA_DEAD );
		agk::StopMusic();

		for( int i = 0; i < ARRAY_SIZE; i++ )
		{
			bossSpells[i].deleteSprite();
		}

		agk::PlaySound( BOSS_SAYING2 );

		/* Sleep 5 secs before switching state */
		agk::Sleep( 5000 );

		hideGameScreens();	
		g_gameState = BAD_GAME_OVER_STATE;
	}

	/* Boss has 20 Hit Points, if counter is equal to 20,
	 * switch state to good state */
	if( COUNT_BOSS_HP == 20 )
	{
		agk::StopMusic();
		agk::PlaySound( BOSS_SAYING );
		agk::Sleep( 4000 );
		hideGameScreens();
		g_gameState = GOOD_GAME_OVER_STATE;
	}
}

/* Hide all images from the Battle State */
void hideGameScreens()
{
	agk::SetSpriteVisible( BATTLE_BACKGROUND, INVISIBLE );
	sora.setVisible( INVISIBLE );
	darkside.setVisible( INVISIBLE );
	agk::SetSpriteVisible( NORMAL_HUD, INVISIBLE );
	agk::SetSpriteVisible( HEALTH_BAR1, INVISIBLE );
	agk::SetSpriteVisible( BOSS_HEALTH1, INVISIBLE );
	agk::SetSpriteVisible( GAME_MENU, INVISIBLE );
}

/* Good Ending */
void showGoodEnding()
{
	if( !agk::GetMusicPlaying() )
		agk::PlayMusic( END_THEME, SONG_LOOP );
	
	agk::SetSpriteVisible(GAME_OVER_GOOD, VISIBLE );
}

/* Bad Ending */
void showBadEnding()
{
	if( !agk::GetMusicPlaying() )
		agk::PlayMusic( END_THEME, SONG_LOOP );
	
	agk::SetSpriteVisible(GAME_OVER_BAD, VISIBLE );
}