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
double y_prev = y; //マリオジャンプのときの前回のy座標を格納する変数。１フレーム前のy座標
double F = -1.0f; //マリオジャンプのときに加える力。ジャンプのときは-10,それ以外は-1

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
void SinJump(int* inputP) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag) {
			canjumpFrag = 0;
			jumpFrames = 0;
		}
	}
}
//サインジャンプセット
void SinJumpGravity(int* inputP, double* y, int yuka) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag) {
			canjumpFrag = 0;
			jumpFrames = 0;
		}
	}
	if (canjumpFrag == 0) {

		*y = -heightJump * sin(radPerFrame * jumpFrames) + yuka;
		jumpFrames += 1;

		if (*y > yuka) {
			*y = yuka;
			canjumpFrag = 1;
		}

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
void PhysicsJump(int* v0,int* time,int* inputP) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag == 1) {
			*v0 = 10;
			*time = 0;
			canjumpFrag = 0;
		}
	}
}
//物理法則ジャンプセット
void PhysicsJumpGravity(int* inputP,int* v0,int* time,double* y,int yuka) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag == 1) {
			*v0 = 10;
			*time = 0;
			canjumpFrag = 0;
		}
	}

	*y = (0.5 * gravity * (*time) * (*time) - *v0 * (*time)) + yuka;

	if (*y >= yuka) {
		*y = yuka;
		canjumpFrag = 1;
	}
}

//マリオジャンプ(前の位置情報との加減算のみのジャンプ)
void MarioJump(int* inputP) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag == 1) {
			F = -10.0;
			canjumpFrag = 0;
		}
	}
}
//マリオグラビティ
void MarioGravity(double* y,double* y_p,int yuka) {
	double y_temp = *y;
	*y += (*y - *y_p) + F;
	*y_p = y_temp;
	F = 1;

	if (*y >= yuka) {
		*y = yuka;
		canjumpFrag = 1;
	}
}
//マリオジャンプセット(ジャンプと重力の一体型)
void MarioJumpGravity(int* inputP, double* y, double* y_p, int yuka) {
	if (*inputP & PAD_INPUT_1) {
		if (canjumpFrag == 1) {
			F = -10.0;
			canjumpFrag = 0;
		}
	}
	double y_temp = *y;
	*y += (*y - *y_p) + F;
	*y_p = y_temp;
	F = 1;

	if (*y >= yuka) {
		*y = yuka;
		canjumpFrag = 1;
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

	//ジャンプ関数(別々)。ジャンプセットからジャンプ要素だけを関数化。
	//PhysicsJump(&v0, &time,&input);
	//SinJump(&input);
	//MarioJump(&input);
	

	//重力関数(別々)。ジャンプセットから重力要素だけを関数化。利用したい関数に合わせた関数(PhysicsJumpを使いたければPhysicsGravityといったように)をコメント外しすること。それ以外はコメントにすること。
	//PhysicsGravity(&y, &v0, 450, time);
	//SinGravity(&y, 450);
	//MarioGravity(&y, &y_prev,yuka);
	
	//ジャンプセット(ジャンプと重力の関数を合わせた関数。面倒な人はこれひとつでジャンプと重力を実装できる)
	SinJumpGravity(&input, &y, yuka);
	//PhysicsJumpGravity(&input, &v0, &time, &y, yuka); //物理法則ジャンプセット
	//MarioJumpGravity(&input, &y, &y_prev, yuka); //マリオジャンプセット



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