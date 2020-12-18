#ifndef INC_BITS_H
#include <bits/stdc++.h>
#define INC_BITS_H
#endif

#ifndef INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h" 
#define INC_SDL_H
#endif

#define X first
#define Y second



class BALL{
	public:
		pair<int, int> v;
		SDL_Texture *pic;
		SDL_Rect model;
		BALL(char side){
			v = {0,0};
			model.h = ball_size;
			model.w = ball_size;
			if(side == 'L')  model.x = ScreenWidth / 4 - PlayerWidth1 / 2;
			if(side == 'R')  model.x = ScreenWidth * 3 / 4 - PlayerWidth1 / 2;
			model.y = initial_height;
		}
		
	private:
};
