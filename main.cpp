#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_video.h"
#include <bits/stdc++.h>
using namespace std;
#define INC_SDL_H
#define INC_BITS_H

//My own header files
#include "constants.h"
#include "pole.h"
#include "player.h"
#include "ball.h"
#include "physics.h"
#include "hints.h"
#include "score.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Event e;
POLE *pole = new POLE();
PLAYER *player1 = new PLAYER('L');
PLAYER *player2 = new PLAYER('R');
BALL *ball = new BALL('L');
HINT *serve_hint = new HINT();
HINT *win_hint = new HINT();
HINT *end_hint = new HINT();
SCORE *Lscore = new SCORE('L', 0);
SCORE *Rscore = new SCORE('R', 0);
    
using namespace std;

//remove the background of the god damnnnn pictures
SDL_Surface *remove_back(SDL_Surface *original){
	SDL_Surface *ret = NULL;
	if(original != NULL){
		ret = original;
	}
	if(ret != NULL){
		SDL_SetColorKey(ret, SDL_TRUE, SDL_MapRGB(ret->format, 0xFF, 0xFF, 0xFF));
	}
	return ret;
}

bool INIT(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 0;
    }
	//create window
    if (SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 0;
    }
    SDL_SetWindowTitle(window, "Volleyball Game");
//  cout << "create window.\n";
    //load background
    surface = SDL_LoadBMP(background_path);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 0;
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_FreeSurface(surface);
//  cout << "load background.\n";
    //load pole
    surface = IMG_Load(pole_path);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return 0;
    }
    pole->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    if(!pole->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 0;
	}
	SDL_RenderCopy(renderer, pole->pic, NULL, &pole->model);
	SDL_FreeSurface(surface); 
//	cout << "load pole.\n";
	//load serve hint
	surface = IMG_Load(serve_hint_path);
	if(!surface){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		return 0;
	}
	serve_hint->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
	if(!serve_hint->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 0;
	}
	SDL_RenderCopy(renderer, serve_hint->pic, NULL, &serve_hint->model);
	SDL_FreeSurface(surface);
	//load end_hint
	surface = IMG_Load(end_hint_path);
	if(!surface){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		return 0;
	}
	end_hint->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
	if(!end_hint->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 0;
	}
	SDL_RenderCopy(renderer, end_hint->pic, NULL, &end_hint->model);
	SDL_FreeSurface(surface);
	
	
//	cout << "init complete.\n";
	return 1;
}

void PLAYER_INIT(){
    //load left player
    surface = IMG_Load(leftplayer_path);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return ;
    }
    player1->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    if(!player1->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return ;
	}
	SDL_RenderCopy(renderer, player1->pic, NULL, &player1->model);
	SDL_FreeSurface(surface);
//	cout << "load player1.\n"; 
	//load right player
    surface = IMG_Load(rightplayer_path);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return ;
    }
    player2->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    if(!player2->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return ;
	}
	SDL_RenderCopy(renderer, player2->pic, NULL, &player2->model);
	SDL_FreeSurface(surface);
//	cout << "load player2.\n"; 
}

void BALL_INIT(){
	//load ball
	surface = IMG_Load(ball_path);
	if(!surface){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		return ;
	}
	ball->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
	if(!ball->pic){
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return ;
	}
	SDL_RenderCopy(renderer, ball->pic, NULL, &ball->model);
	SDL_FreeSurface(surface);
} 

void change_form(int side, int phase){
	switch(side * 10 + phase){
		case 11:{
			player1->model.w = PlayerWidth2;
			player1->model.h = PlayerHeight2;
			player1->status = 2;
			surface = IMG_Load(leftplayer_raisehand_path);
		    if (!surface){
       			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		    	return ;
    		}
    		player1->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    		if(!player1->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        		return ;
			}
			SDL_RenderCopy(renderer, player1->pic, NULL, &player1->model);
			SDL_FreeSurface(surface);
			break;
		}
		case 12:{
			player1->model.w = PlayerWidth1;
			player1->model.h = PlayerHeight1;
			player1->status = 1;
			if(player1->model.x + player1->model.w > ScreenWidth / 2)  player1->model.x = ScreenWidth / 2 - player1->model.w;
			surface = IMG_Load(leftplayer_path);
		    if (!surface){
       			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		    	return ;
    		}
    		player1->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    		if(!player1->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        		return ;
			}
			SDL_RenderCopy(renderer, player1->pic, NULL, &player1->model);
			SDL_FreeSurface(surface);
			break;
		}
		case 21:{
			player2->model.w = PlayerWidth2;
			player2->model.h = PlayerHeight2;
			player2->status = 2;
			surface = IMG_Load(rightplayer_raisehand_path);
		    if (!surface){
       			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		    	return ;
    		}
    		player2->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    		if(!player2->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        		return ;
			}
			SDL_RenderCopy(renderer, player2->pic, NULL, &player2->model);
			SDL_FreeSurface(surface);
			break;
		}
		case 22:{
			player2->model.w = PlayerWidth1;
			player2->model.h = PlayerHeight1;
			player2->status = 1;
			surface = IMG_Load(rightplayer_path);
		    if (!surface){
       			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		    	return ;
    		}
    		player2->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    		if(!player2->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        		return ;
			}
			SDL_RenderCopy(renderer, player2->pic, NULL, &player2->model);
			SDL_FreeSurface(surface);
			break;
		}
	}
}
    
int main(int argc, char *argv[])
{
//Initialise
    if(!INIT())  return 3; 
	
//Real program starts here
	bool Nquit = true, start_serve = false;
	PLAYER_INIT(); 
	BALL_INIT();
    while (Nquit && (Lscore->val < MAX_Score && Rscore->val < MAX_Score)) {
		const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
            Nquit = false;
        }
        else  if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)  start_serve ^= 1;
        if(start_serve){
        	//TODOs
        	bool Special_Event = NextStep(ball, player1, player2, pole);
        	if(Special_Event){
        		start_serve = false;
				if(ball->model.x <= pole->model.x + PoleWidth/2 - ball_size){
					Rscore->val += 1;
					if(Rscore->val < MAX_Score){
						player1 = new PLAYER('L');
						player2 = new PLAYER('R');
						ball = new BALL('R');
						PLAYER_INIT();
						BALL_INIT();
					} 
				}
				else{
					Lscore->val += 1;
					if(Lscore->val < MAX_Score){
						player1 = new PLAYER('L');
						player2 = new PLAYER('R');
						ball = new BALL('L');
						PLAYER_INIT();
						BALL_INIT();
					} 
				}
				continue;
			}
			if(player1->status == 2){
				player1->model.y += player1->dy;
				player1->dy -= g;
				if(player1->dy > initial_speed){
					player1->dy = 0;
					change_form(1, 2);
				}
			}
			if(player2->status == 2){
				player2->model.y += player2->dy;
				player2->dy -= g;
				if(player2->dy > initial_speed){
					player2->dy = 0;
					change_form(2, 2);
				}
			}
        	if(currentKeyStates[SDL_SCANCODE_D]){
        		if(player1->model.x + dx < ScreenWidth / 2 - player1->model.w)  player1->model.x += dx;
			}
        	if(currentKeyStates[SDL_SCANCODE_A]){
        		if(player1->model.x - dx > 0)  player1->model.x -= dx;
			}
			if(currentKeyStates[SDL_SCANCODE_W]){
				if(player1->status == 1){
					player1->dy = -initial_speed;
					change_form(1, 1);
				}
			}
        	if(currentKeyStates[SDL_SCANCODE_LEFT]){
        		if(player2->model.x - dx > ScreenWidth / 2)  player2->model.x -= dx;
			}
			if(currentKeyStates[SDL_SCANCODE_RIGHT]){
				if(player2->model.x + dx < ScreenWidth - player2->model.w)  player2->model.x += dx;
			}
			if(currentKeyStates[SDL_SCANCODE_UP]){
				if(player2->status == 1){
					player2->dy = -initial_speed;
					change_form(2, 1);
				}
			}
			if(currentKeyStates[SDL_SCANCODE_ESCAPE])  Nquit = false;
		}
		//Render
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, pole->pic, NULL, &pole->model);
        SDL_RenderCopy(renderer, player1->pic, NULL, &player1->model);
        SDL_RenderCopy(renderer, player2->pic, NULL, &player2->model);
		SDL_RenderCopy(renderer, ball->pic, NULL, &ball->model);
		if(!start_serve){
			SDL_RenderCopy(renderer, serve_hint->pic, NULL, &serve_hint->model);
	    	//load score
    		surface = IMG_Load(Lscore->choose_route());
		    if (!surface){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
	    		return 3;
    		}
	    	Lscore->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
	    	if(!Lscore->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
       			return 3;
			}
			SDL_RenderCopy(renderer, Lscore->pic, NULL, &Lscore->model);
			SDL_FreeSurface(surface);
		
    		surface = IMG_Load(Rscore->choose_route());
	    	if (!surface){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
	    		return 3;
    		}
    		Rscore->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
    		if(!Rscore->pic){
    			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
       			return 3;
			}
			SDL_RenderCopy(renderer, Rscore->pic, NULL, &Rscore->model);
			SDL_FreeSurface(surface);
		}
		SDL_RenderCopy(renderer, Lscore->pic, NULL, &Lscore->model);
		SDL_RenderCopy(renderer, Rscore->pic, NULL, &Rscore->model);
       	SDL_RenderPresent(renderer);
        delay(dt);
    }
    if(Lscore->val > Rscore->val)  surface = IMG_Load(win_hint1_path);
    else  surface = IMG_Load(win_hint2_path);
	if(!surface){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		return 0;
	}
	win_hint->model.y = ScreenWidth / 4;
	win_hint->pic = SDL_CreateTextureFromSurface(renderer, remove_back(surface));
	if(!win_hint->pic){
   		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
  	     return 0;
	}
	SDL_RenderCopy(renderer, win_hint->pic, NULL, &win_hint->model);
	SDL_FreeSurface(surface);
    while(Nquit){
    	SDL_PollEvent(&e);
    	if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))  Nquit = false;
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    	SDL_RenderCopy(renderer, win_hint->pic, NULL, &win_hint->model);
    	SDL_RenderCopy(renderer, end_hint->pic, NULL, &end_hint->model);
        SDL_RenderPresent(renderer);
	}

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
