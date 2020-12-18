#ifndef INC_BITS_H
#include <bits/stdc++.h>
#define INC_BITS_H
#endif

#ifndef INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h" 
#define INC_SDL_H
#endif



class POLE{
	public:
		SDL_Texture *pic;
		SDL_Rect model;
		POLE(){
			model.h = PoleHeight;
			model.w = PoleWidth;
			model.x = ScreenWidth / 2 - model.w/2;
			model.y = ScreenHeight / 3;
		}
	
	private:
} ;
