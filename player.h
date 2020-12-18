#ifndef INC_BITS_H
#include <bits/stdc++.h>
#define INC_BITS_H
#endif

#ifndef INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h" 
#define INC_SDL_H
#endif



class PLAYER{
	public:
		int dy, status;
		SDL_Texture *pic;
		SDL_Rect model;
		PLAYER(char side){
			status = 1;
			model.h = PlayerHeight1;
			model.w = PlayerWidth1;
			if(side == 'L'){
				model.x = ScreenWidth / 4 - PlayerWidth1 / 2;
			}
			if(side == 'R'){
				model.x = ScreenWidth * 3 / 4 - PlayerWidth1 / 2;
			}
			model.y = ScreenHeight/3 + (PoleHeight - PlayerHeight1);
		}
		
	private:
};
