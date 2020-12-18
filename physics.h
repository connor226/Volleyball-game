#ifndef INC_BITS_H
#include <bits/stdc++.h>
using namespace std;
#endif



SDL_Rect operator +(const SDL_Rect &r, const pair<int, int> &v){
	SDL_Rect ret = r;
	ret.x += v.X;
	ret.y += (v.Y / 10);
	return ret;
}

int detect_collision_Player1(BALL *ball, PLAYER *player1, POLE *pole){
	if(abs(player1->model.x + player1->model.w/2 - ball->model.x) < ball_size*3/2 && ball->model.x <= pole->model.x + PoleWidth/2){
		if(player1->model.y - ball->model.y < ball_size && ball->model.y <= player1->model.y){
			ball->model.y = player1->model.y - ball_size;
			if(ball->model.x < player1->model.x){
				return 4;  //dx = dx, dy = -dy;
			}
			if(ball->model.x >= player1->model.x){
				if(player1->status == 1)  return 1;  //dx = 0, dy = -dy;
				else{
					const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
					if(currentKeyStates[SDL_SCANCODE_D])  return 3;  //dx = 3, dy = -1;
					else  return 2;  // dx = -dx, dy = -dy;
				}
			}
		}
		if(ball->model.y > player1->model.y){
			if(ball->model.x < player1->model.x){
				ball->model.x = max(0, player1->model.x - ball_size);
				if(ball->model.x == 0 && player1->model.x < ball_size)  player1->model.x = ball_size;
				return 5;  //dx = dx+3, dy = dy;
			}
			else{
				ball->model.x = min(player1->model.x + player1->model.w, pole->model.x + PoleWidth / 2 - ball_size);
				if(ball->model.x == pole->model.x + PoleWidth / 2 - ball_size && player1->model.x > ball->model.x - player1->model.w)  player1->model.x = ball->model.x - player1->model.w - 1;
				return 6;  //dx = -dx, dy = dy;
			}
		}
	}
	return 0;
}

int detect_collision_Player2(BALL *ball, PLAYER *player2, POLE *pole){
	if(abs(player2->model.x + player2->model.w/2 - ball->model.x - ball_size) < ball_size*3/2 && ball->model.x >= pole->model.x + PoleWidth/2){
		if(player2->model.y - ball->model.y < ball_size && ball->model.y <= player2->model.y){
			ball->model.y = player2->model.y - ball_size;
			if(ball->model.x + ball_size > player2->model.x + player2->model.w){
				return 4;  //dx = dx, dy = -dy;
			}
			if(ball->model.x + ball_size <= player2->model.x + player2->model.w){
				if(player2->status == 1)  return 1;  //dx = 0, dy = -dy;
				else{
					const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
					if(currentKeyStates[SDL_SCANCODE_LEFT])  return 3;  //dx = 3, dy = -1;
					else  return 2;  // dx = -dx, dy = -dy;
				}
			}
		}
		if(ball->model.y > player2->model.y){
			if(ball->model.x > player2->model.x){
				ball->model.x = min(ScreenWidth - ball_size, player2->model.x + player2->model.w);
				if(ball->model.x == ScreenWidth - ball_size && player2->model.x > ball->model.x - player2->model.w)  player2->model.x = ball->model.x - player2->model.w;
				return 5;  //dx = dx+3, dy = dy;
			}
			else{
				ball->model.x = max(player2->model.x - ball_size, pole->model.x + PoleWidth / 2);
				if(ball->model.x == pole->model.x + PoleWidth / 2 && player2->model.x < ball->model.x + ball_size)  player2->model.x = ball->model.x + ball_size + 1;
				return 6;  //dx = -dx, dy = dy;
			}
		}
	}
	return 0;
}

int detect_collision_Pole(BALL *ball, POLE *pole){
	if(abs(ball->model.x + ball_size / 2 - pole->model.x - PoleWidth / 2) < ball_size/2){
		if(ball->model.y > pole->model.y - ball_size / 2){
			if(ball->v.X > 0)  ball->model.x = pole->model.x + PoleWidth/2 - ball_size;
			else  ball->model.x = pole->model.x + PoleWidth/2;
			return 1;
		}
		else  if(ball->model.y > pole->model.y - ball_size){
			if(ball->v.X > 0)  ball->model.x = pole->model.x + PoleWidth/2;
			else  ball->model.x = pole->model.x + PoleWidth/2 - ball_size;
			ball->model.y = pole->model.y - ball_size;
			return 2;
		}
	}
	return 0;
}

int detect_collision_Boundary(BALL *ball, POLE *pole){
	if(ball->model.x <= 0) {
		ball->model.x = 0;
		return 1;  //dx = -dx
	}
	if(ball->model.x >= ScreenWidth - ball_size){
		ball->model.x = ScreenWidth - ball_size;
		return 2;  //dx = -dx
	}
	if(ball->model.y <= 0) {
		ball->model.y = 1;
		return 3;  //dy = 0;
	}
	if(ball->model.y + ball_size >= pole->model.y + PoleHeight){
		ball->model.y = pole->model.y + PoleHeight - ball_size;
		return 4;  //someone gets score 
	}
}

bool NextStep(BALL *ball, PLAYER *player1, PLAYER *player2, POLE *pole){
	ball->v.Y -= g;
	ball->model = ball->model + ball->v;
	int check;
	
	//check collision with player 1
	check = detect_collision_Player1(ball, player1, pole);
	switch(check){
		case 1:{
			ball->v.X = 0;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 2:{
			ball->v.X = ballv_dx;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 3:{
			ball->v.X = ballv_spx;
			ball->v.Y = -ballv_spy;
			break;
		}
		case 4:{
			ball->v.X = -ballv_dx;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 5:{
			ball->v.X = ballv_dx;
			ball->v.Y = ballv_dy;
			break;
		}
		case 6:{
			ball->v.X = -ballv_dx;
			ball->v.Y = ballv_dy;
			break;
		}
	}
	
	//check collision with player 2
	check = detect_collision_Player2(ball, player2, pole);
	switch(check){
		case 1:{
			ball->v.X = 0;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 2:{
			ball->v.X = -ballv_dx;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 3:{
			ball->v.X = -ballv_spx;
			ball->v.Y = -ballv_spy;
			break;
		}
		case 4:{
			ball->v.X = ballv_dx;
			ball->v.Y = -ballv_dy;
			break;
		}
		case 5:{
			ball->v.X = ballv_dx;
			ball->v.Y = ballv_dy;
			break;
		}
		case 6:{
			ball->v.X = -ballv_dx;
			ball->v.Y = ballv_dy;
			break;
		}
	}
	
	//check collision with pole
	check = detect_collision_Pole(ball, pole);
	switch(check){
		case 1:{
			ball->v.X = -ball->v.X;
			break;
		}
		case 2:{
			ball->v.X = ball->v.X/ballv_dx;
			ball->v.Y = 0;
			break;
		}
	}
	
	//check collision with boundaries
	check = detect_collision_Boundary(ball, pole);
	switch(check){
		case 1:{
			ball->v.X = -ball->v.X;
			break;
		}
		case 2:{
			ball->v.X = -ball->v.X;
			break;
		}
		case 3:{
			ball->v.Y = 0;
			break;
		}
		case 4:{
			return true;
			break;
		}
	}
	return false;
}
