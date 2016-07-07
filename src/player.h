#include <string>
#include <iostream>

using namespace std;

#include <vector>

#if defined(__APPLE__)
	#include "SDL2/SDL.h"
	#include "SDL2_image/SDL_image.h"
	#include "SDL2_mixer/SDL_mixer.h"
	#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif


class Player {

public:

	// is the player active - still alive?
	bool active;

	string moveDir;

	// variable to hold the list of bullets
	//vector<TankBullet> bulletList;

	// string to hold the path to the player's texture
	string playerPath;

	// player's texture to hold img
	SDL_Texture *playerT;

	// player's SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect playerR;

	// float for player speed
	float speed;

	//float for the player's position to avoid precision loss
	float pos_X, pos_Y;

	// vars used to get the angle between the tank's position and the turret's position
	float x, y, tankangle;

	// keep the last angle so the  player can fire in the correct direction
	float oldAngle;

	// add X and Y values
	int Xvalue, Yvalue;

	// Point that will be used to rotate the turret - relative to the turret barrel's RECT
	SDL_Point center;

	// Player's creation method using passed in values for renderer, path to the texture
	// starting position X, starting position Y
	Player(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	// update the player using the passed in deltaTime
	void Update(float deltaTime);

	// draw the player main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	// reset the player
	void Reset();

	void Ydir(int dir);

	void Xdir(int dir);

private:

	//void CreateBullet();




};
