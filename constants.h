//all constants are stored here and set to be constants
const char *background_path = "./img/background.bmp";
const char *pole_path = "./img/pole.png";
const char *leftplayer_path = "./img/player1.png";
const char *rightplayer_path = "./img/player2.png";
const char *leftplayer_raisehand_path = "./img/player1_raisehand.png";
const char *rightplayer_raisehand_path = "./img/player2_raisehand.png";
const char *ball_path = "./img/ball.png";
const char *serve_hint_path = "./img/serve_hint.png";
const char *win_hint1_path = "./img/win_hint1.png";
const char *win_hint2_path = "./img/win_hint2.png";
const char *end_hint_path = "./img/end_hint.png";

const int ScreenWidth = 1000;
const int ScreenHeight = 625;
const int PoleWidth = 100;
const int PoleHeight = 200;

const int PlayerHeight1 = 180;
const int PlayerHeight2 = 190;
const int PlayerWidth1 = 90;
const int PlayerWidth2 = 70;

const int dt = 10;
const int initial_speed = 15;
const int dx = 3;
const int g = -1;

const int ball_size = 60;
const int initial_height = 20;
const int MAX_Score = 15;
const int HintWidth = 300;
const int HintHeight = 50;
const int ScoreWidth = 127;
const int ScoreHeight = 81;

const char *number00_path = "./img/number_00.png";
const char *number01_path = "./img/number_01.png";
const char *number02_path = "./img/number_02.png";
const char *number03_path = "./img/number_03.png";
const char *number04_path = "./img/number_04.png";
const char *number05_path = "./img/number_05.png";
const char *number06_path = "./img/number_06.png";
const char *number07_path = "./img/number_07.png";
const char *number08_path = "./img/number_08.png";
const char *number09_path = "./img/number_09.png";
const char *number10_path = "./img/number_10.png";
const char *number11_path = "./img/number_11.png";
const char *number12_path = "./img/number_12.png";
const char *number13_path = "./img/number_13.png";
const char *number14_path = "./img/number_14.png";
const char *number15_path = "./img/number_15.png";

const int ballv_spy = 25;
const int ballv_dy = 40;
const int ballv_spx = 8;
const int ballv_dx = 4;

void delay(int deltaT){
	double t = clock();
	while((clock() - t) / CLOCKS_PER_SEC * 1000 < deltaT){}
}
