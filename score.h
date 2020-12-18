#ifndef INC_BITS_H
#define INC_BITS_H
#include <bits/stdc++.h>
#endif

#ifndef INC_SDL_H
#define INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif



class SCORE{
	public: 
		int val;
		SDL_Texture *pic;
		SDL_Rect model;
		SCORE(char side, int x){
			val = x;
			model.h = ScoreHeight;
			model.w = ScoreWidth;
			if(side == 'L')  model.x = ScreenWidth / 6 - ScoreWidth / 2;
			if(side == 'R')  model.x = ScreenWidth * 5 / 6 - ScoreWidth / 2;
			model.y = ScreenHeight * 3 / 4;
		}
		const char *choose_route(){
			return router();
		}
	
	private:
		const char *router(){
			switch(val){
				case 0:{
					return number00_path;
					break;
				}
				case 1:{
					return number01_path;
					break;
				}
				case 2:{
					return number02_path;
					break;
				}
				case 3:{
					return number03_path;
					break;
				}
				case 4:{
					return number04_path;
					break;	
				}
				case 5:{
					return number05_path;
					break;
				}
				case 6:{
					return number06_path;
					break;	
				}
				case 7:{
					return number07_path;
					break;
				}
				case 8:{
					return number08_path;
					break;
				}
				case 9:{
					return number09_path;
					break;
				}
				case 10:{
					return number10_path;
					break;
				}
				case 11:{
					return number11_path;
					break;
				}
				case 12:{
					return number12_path;
					break;
				}
				case 13:{
					return number13_path;
					break;
				}
				case 14:{
					return number14_path;
					break;
				}
				case 15:{
					return number15_path;
					break;
				}
			}
		}
};
