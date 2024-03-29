#include "DxLib.h"

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

//物理法則ジャンプセット
void PhysicsJumpGravity(int* inputP, int* v0, int* time, double* y, int yuka) {
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);              //ウィンドウモードにする。

	LONGLONG StartTime;

    if (DxLib_Init() == -1) return -1; // ＤＸライブラリ初期化処理 エラーが起きたら終了 

	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    int i, a = 0, time, White;
    White = GetColor(255, 255, 255); // 白色の値を取得

	
	// 現在経過時間を得る
	StartTime = GetNowHiPerformanceCount();
	
	PhysicsJumpGravity(&input, &v0, &times, &y, yuka); //物理法則ジャンプセット

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64dマイクロ秒", time);//文字列表示
    
	WaitKey();                     // キーの入力待ち(『WaitKey』を使用)
    DxLib_End();                   // ＤＸライブラリ使用の終了処理
    return 0;                      // ソフトの終了
}