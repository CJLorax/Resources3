#include "player.h"



// Tank creation Method
Player::Player(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y)
{
	// activate the player
	active = true;

	moveDir = "none";

	// set float for player speed
	speed = 200.0f;

	// tank firing sound
	//fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	playerPath = filePath + "archer.png";

	// load the surface into the texture
	playerT = IMG_LoadTexture(renderer, playerPath.c_str());

	// set the SDL_Rect X and Y for the player
	playerR.x = x;
	playerR.y = y;

	// Use SDL_QueryTexture to get the W and H of the player's texture
	int w, h;
	SDL_QueryTexture(playerT, NULL, NULL, &w, &h);
	playerR.w = w;
	playerR.h = h;

	// Set the movement floats to the players original X and Y
	pos_X = x;
	pos_Y = y;

	Yvalue = 0;
	Xvalue= 0;

	// find the center of the texture
	center.x = playerR.w/2;
	center.y = playerR.h/2;


}

void Player::Ydir(int dir)
{

	Yvalue = dir;

}

void Player::Xdir(int dir)
{

	Xvalue = dir;

}

// Tank Draw method
void Player::Draw(SDL_Renderer *renderer)
{
	// Draw the player texture using the vars texture and posRect
	//SDL_RenderCopy(renderer, playerT, NULL, &playerR);

	// Draw the player texture using the vars texture and posRect
		SDL_RenderCopyEx( renderer, playerT, NULL, &playerR, tankangle, &center, SDL_FLIP_NONE);
}

// Tank Update method
void Player::Update(float deltaTime)
{

	// check for gamepad input
	if (Xvalue != 0 || Yvalue != 0) {

		//get the angle that the tank needs to face
		tankangle = atan2(Yvalue, Xvalue) * 180 / 3.14;

		// set this as the old angle and dir some the player/tank can shoot when stopped.
		oldAngle = tankangle;

		//Gives us radians
		float radians = (tankangle * 3.14) / 180;

		// Get need X and Y values to move
				float move_x = speed * cos( radians );
				float move_y = speed * sin( radians );

		// update floats for precision loss
		pos_X += (move_x) * deltaTime;
		pos_Y += (move_y) * deltaTime;

		// Update player position with code to account for precision loss
		playerR.x = (int)(pos_X + 0.5f);
		playerR.y = (int)(pos_Y + 0.5f);

	}

}

