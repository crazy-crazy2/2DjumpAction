#include "DxLib.h"

//画面サイズ定義
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

int canjumpFrag = 1; //ジャンプできるか
double F = -1.0f; //マリオジャンプのときに加える力。ジャンプのときは-10,それ以外は-1

double x = 100;
double y = 450;
double y_prev = y; //マリオジャンプのときの前回のy座標を格納する変数。１フレーム前のy座標
int yuka = SCREEN_HEIGHT - 50;

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);              //ウィンドウモードにする。

	LONGLONG StartTime;

    if (DxLib_Init() == -1) return -1; // ＤＸライブラリ初期化処理 エラーが起きたら終了 

	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    int i, a = 0, time, White;
    White = GetColor(255, 255, 255); // 白色の値を取得

	// 現在経過時間を得る
	StartTime = GetNowHiPerformanceCount();

	MarioJumpGravity(&input, &y, &y_prev, yuka); //マリオジャンプセット

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64dマイクロ秒", time);//文字列表示
    
	WaitKey();                     // キーの入力待ち(『WaitKey』を使用)
    DxLib_End();                   // ＤＸライブラリ使用の終了処理
    return 0;                      // ソフトの終了
}