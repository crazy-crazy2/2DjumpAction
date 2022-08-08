#include"DxLib.h"
#include<math.h>
#include"teigi.cpp"

#define PI 3.14159265359

//画面サイズ定義
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

//キャラクタ定義
const int chara_width = 32;
const int chara_height = 32;
double x = 100;
double y = 450;
int charaH[12]; //ハンドル
int canjumpFrag = 1; //ジャンプできるか

//キャラクタ速度関係
int v0 = 0; //初速度
int time = 0;
double gravity = 0.5;

//エネミー定義
const int enemy_width = 32;
const int enemy_height = 32;
int x_enemy = 300;
int y_enemy = SCREEN_HEIGHT - 50;
int enemyH[12];

//キャラ初期化
void Chara_Init() {
	LoadDivGraph("obake.png", 12, 3, 4, 32, 32, charaH);
}

int jumpFrames = 0; //ジャンプ中のフレームカウント
double radPerFrame = 2 * PI / 40;
int heightJump = 100;

//sin波を利用した重力
void SinGravity(double* y,int yuka) {
	
	if (canjumpFrag == 0) {
		
		*y = -heightJump * sin(radPerFrame * jumpFrames) + yuka;
		jumpFrames += 1;
		
		if (*y > yuka) {
			*y = yuka;
			canjumpFrag = 1;
		}
	
	}
	
}
//sin波を利用したジャンプ
void SinJump() {
	if (canjumpFrag) {
		canjumpFrag = 0;
		jumpFrames = 0;
	}
}

//物理の公式重力
void PhysicsGravity(double* y, int* v0, int yuka, int time) {
	*y = (0.5 * gravity * time * time - *v0 * time) + yuka;

	if (*y >= yuka) {
		*y = yuka;
		canjumpFrag = 1;
	}
}
//物理公式のジャンプ
void PhysicsJump(int* v0,int* time) {
	
	if (canjumpFrag == 1) {
		*v0 = 10;
		*time = 0;
		canjumpFrag = 0;
	}	
}
int yuka = SCREEN_HEIGHT - 50;
//キャラ移動
void Chara_Move() {
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input & PAD_INPUT_RIGHT) {
		x += 5;
	}
	if (input & PAD_INPUT_LEFT) {
		x -= 5;
	}
	if (input & PAD_INPUT_1) {
		//利用したい関数以外はコメントにすること
		//PhysicsJump(&v0, &time);
		SinJump();
	}

	//利用したい関数に合わせた関数(PhysicsJumpを使いたければPhysicsGravityといったように)をコメント外しすること。それ以外はコメントにすること。
	//PhysicsGravity(&y, &v0, 450, time);
	SinGravity(&y, 450);

	time += 1;
}
//キャラ描画
void Chara_Draw() {
	DrawGraph(x, y, charaH[8], TRUE);
}
//エネミー初期化
void Enemy_Init() {
	LoadDivGraph("Enemy.png",12,3,4,32,32,enemyH);
}
//エネミー移動
void Enemy_Move() {
	x_enemy -= 2;
	if (x_enemy < 0) x_enemy = SCREEN_WIDTH;
}

void Enemy_Draw() {
	DrawGraph(x_enemy, y_enemy, enemyH[5], TRUE);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1) return -1;

	Chara_Init();

	Enemy_Init();

	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		//キャラ移動
		Chara_Move();
		//エネミー移動
		Enemy_Move();

		//キャラ描画
		Chara_Draw();
		//エネミー描画
		Enemy_Draw();

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}