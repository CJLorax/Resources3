#include <stdio.h>
#include <string>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// deltaTime var intialization - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;


#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/resources/art/";
string audio_dir = currentWorkingDirectory + "/resources/audio/";
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <direct.h>
#define getcwd _getcwd

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "\\resources\\art\\";
string audio_dir = currentWorkingDirectory + "\\resources\\audio\\";
#endif


#include "player.h"

// Main Start ************************************************
int main() {

	// ******************* Create the SDL Window - START *******************
	// Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a SDL Window reference - pointer
	SDL_Window *window = NULL;

	// Create a SDL RenderTarget - pointer
	SDL_Renderer *renderer = NULL;

	// Create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Shooter Example",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	// Create an SDL RenderTarget
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// ******************* Create the SDL Window - END *******************


	// load archer
	//SDL_Texture *archer = IMG_LoadTexture(renderer, (images_dir + "archer.png").c_str());
	//SDL_Rect archerRect;
	//archerRect.x = 0;
	//archerRect.y = 0;
	//archerRect.w = 67;
	//archerRect.h = 49;

	Player player = Player(renderer, images_dir.c_str(), audio_dir.c_str(), 50.0f, 50.0f);



	// ******************* variable creation - start *******************
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;


	// MAIN GAME LOOP START *****************************************

	while( !quit )
	{

		// Create deltaTime - for frame rate independence
		thisTime = SDL_GetTicks();
		deltaTime = (float) (thisTime - lastTime) / 1000;
		lastTime = thisTime;

		// Handle Events on Queue - Keypresses and such START *****************************************
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			 const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

			 if( currentKeyStates[ SDL_SCANCODE_UP ] ){
				 player.Ydir(-1);
			 }else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
				 player.Ydir(1);
			 }else{
				 player.Ydir(0);

			 }


			 if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
				 player.Xdir(-1);
			 }else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
				 player.Xdir(1);
			 }else{
				 player.Xdir(0);

			 }

		}


		player.Update(deltaTime);


			// ******************* Start the SDL Draw Process *******************
			// Clear the SDL RenderTarget
			SDL_RenderClear(renderer);

			// Draw the bkgd
			player.Draw(renderer);


			// present new buffer to the screen
			SDL_RenderPresent(renderer);


	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();

}


