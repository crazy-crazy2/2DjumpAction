#include "DxLib.h"
#include<math.h>

//画面サイズ定義
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

int canjumpFrag = 1; //ジャンプできるか
int v0 = 0; //初速度
int times = 0;
double x = 100;
double y = 450;
double gravity = 0.5;
int yuka = SCREEN_HEIGHT - 50;
int JumpCount = 0; //ジャンプカウント,ジャンプの段数
double jumpSpeed = -10.0f;
double VY; //y方向の速度
double doubleJumpVy = 0.1f; //ダブルジャンプできる範囲のy方向の速度
int jump_count = 1;

//ダブルジャンプ(2段ジャンプ)
void DoubleJump(int* inputP, double* y, int yuka) {
	if (JumpCount == 0) {
		if (*inputP & PAD_INPUT_1) {
			JumpCount = 1;
			VY = jumpSpeed;

		}
	}
	else {
		VY += gravity;
		*y += VY;

		if (*y >= yuka) {
			*y = yuka;
			JumpCount = 0;
		}

		//2段ジャンプ処理
		if (fabs(VY) < doubleJumpVy && (*inputP & PAD_INPUT_1) && JumpCount < jump_count) {
			VY = jumpSpeed;
			JumpCount++;
		}
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);              //ウィンドウモードにする。

	LONGLONG StartTime;

    if (DxLib_Init() == -1) return -1; // ＤＸライブラリ初期化処理 エラーが起きたら終了 

	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    int i, a = 0, time, White;
    White = GetColor(255, 255, 255); // 白色の値を取得

	
	// 現在経過時間を得る
	StartTime = GetNowHiPerformanceCount();
	
	DoubleJump(&input,&y,yuka); //ダブルジャンプセット

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64dマイクロ秒", time);//文字列表示
    
	WaitKey();                     // キーの入力待ち(『WaitKey』を使用)
    DxLib_End();                   // ＤＸライブラリ使用の終了処理
    return 0;                      // ソフトの終了
}