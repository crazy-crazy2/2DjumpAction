#define NOMINMAX
#include "DxLib.h"
#include <math.h>
#include <algorithm>
#define PI 3.141592654f


//画面サイズ設定
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//マップチップ定義
const int SIZE_MAP_X = 32;
const int SIZE_MAP_Y = 32;
const int NUM_CHIP_X = 10;
const int NUM_CHIP_Y = 4;
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y;
int chip[NUM_CHIP_ALL];

//マップチップ数
const int NUM_MAP_X = 25;
const int NUM_MAP_Y = 18;

//クリア判定用変数
bool gameCrear = FALSE;

//ステージデータ
int data[] = {
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,

	19, 0, 0, 0, 0,  0, 0, 11, 11, 11,  11, 11, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 11, 11,  0, 11, 11, 11, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 11, 11,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,11,0,0,19,

	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 18, 0, 18, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 18, 0, 0,  0, 0, 0, 0, 0,11,11,11,0,19,
	19, 13, 13, 13, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 11,11,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	19, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,0,0,0,0,19,
	10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10, 10,10,10,10,10,
};

//マップの初期化
void Map_Init() {
	LoadDivGraph("mapchip.png", NUM_CHIP_ALL, NUM_CHIP_X, NUM_CHIP_Y, SIZE_MAP_X, SIZE_MAP_Y, chip);

}

//マップ描画
void Map_Draw() {
	if (gameCrear) return; //クリアフラグが建っていたら飛ばす
	//背景の表示
	for (int j = 0; j < NUM_MAP_Y; j++) {
		for (int i = 0; i < NUM_MAP_X; i++) {
			int no = data[i + j * NUM_MAP_X];
			DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, chip[no], FALSE);
		}
	}
}

//Music系のハンドル
//BGM//
int bgmHandle;
//SE//
int jumpSEHandle;
int shotSEHandle;
int shotBrackSEHandle;
int shotBulletSEHandle;

int getItemSEHandle;

int clearSEHandle;

//BGM,SE初期化、ロード
void Music_Init() {
	jumpSEHandle = LoadSoundMem("魔王魂 効果音 システム38.ogg");
	bgmHandle = LoadSoundMem("魔王魂  8bit29.ogg");
	shotSEHandle = LoadSoundMem("魔王魂  銃02.ogg");
	shotBrackSEHandle = LoadSoundMem("魔王魂  銃05.ogg");
	shotBulletSEHandle = LoadSoundMem("魔王魂  爆発05.ogg");
	getItemSEHandle = LoadSoundMem("魔王魂 効果音 システム10.ogg");
	clearSEHandle = LoadSoundMem("魔王魂 効果音 ジングル12.ogg");
}

//キャラクタ定義
const int chara_width = 32; //キャラクタの幅
const int chara_height = 32; //キャラクタの高さ
float x = (SCREEN_WIDTH - chara_width) / 2 ; //キャラクタのx座標
float y = (SCREEN_HEIGHT - chara_height) / 2 + 30; //キャラクタのy座標
float yadd = 0.0f; //y方向の速度vy
float gravity = 0.2f; //重力
float initVy = -6.0f; //y方向の初速度
//前回の位置
float old_x = 0.0f;
float old_y = 0.0f;

bool damaged = FALSE; //ダメージを受けているか
int damageCounter = 0; //ダメージカウンター

//攻撃
int shot_x = 0; //弾が出る位置
int shot_y = 0;
int shotBrack_x = 0; //暗黒弾が出る位置
int shotBrack_y = 0;
int shotBullet_x = 0; //鉛弾が出る位置
int shotBullet_y = 0;
bool isShot = false; //通常弾を撃っているか
bool isShot2 = false; //動きを止める弾(暗黒弾)を撃っているか
bool isShot3 = false; //鉛玉を撃っているか
bool canShotBrackball = false; //動きを止める弾(暗黒弾)が「撃てるか」どうか
int canBrackBallFlag = 0; //暗黒弾が「撃てるか」のフラグ(int)
int canShotBulletFlag = 0; //鉛弾が撃てるかのフラグ

bool jFlag = FALSE; //ジャンプフラグ

int chara_act[12]; //キャラクタ画像格納

int act_motion[] = { 0,1,2,1, }; //アニメーションモーション
int act_index = 0; 
const int MAX_MOTION_INDEX = 4; //モーション最大数

const int ACT_SPEED = 20; //アニメーション変化の速度
int act_wait = ACT_SPEED;
const int ACT_NUM_X = 3; //キャラチップの数x
const int ACT_NUM_Y = 4; //キャラチップの数y
const int ACT_NUM_ALL = ACT_NUM_X * ACT_NUM_Y; //キャラチップの合計数

const int ACT_DIR_SLIDE = ACT_NUM_X; //いまどのチップを選択しているか

int act_dir = 0; //キャラクタの向き

//エネミー情報

const int enemy_width = 32; //敵キャラ　ゴーストの幅、高さ
const int enemy_height = 32;
float x_enemy = (SCREEN_WIDTH - enemy_width) / 2 + 100; //ゴーストのx,y座標
float y_enemy = (SCREEN_HEIGHT - enemy_height) / 2 + 32 * 7;

const int ENE_NUM_X = 3; //ゴーストのキャラチップ数
const int ENE_NUM_Y = 3;
const int ENE_NUM_ALL = ENE_NUM_X * ENE_NUM_Y;

const int ENE_DIR_SLIDE = ENE_NUM_X; //いまどのチップを選択しているか

int enemy_act[12]; //ゴーストのチップ格納

int ene_motion[] = { 0,1,2,1 }; //ゴーストのアニメーションモーション
int ene_index = 0;
const int MAX_ENE_MOTION_INDEX = 4;

int ene_wait = 1; //エネミースピード

int ene_dir = 0;

bool enemyLive = TRUE; //ゴーストが生きているかどうかのフラグ

//コウモリ
float x_bat = (SCREEN_WIDTH - enemy_width) / 2 - 100;
float y_bat = (SCREEN_HEIGHT - enemy_height) / 2;

//コウモリのキャラチップ数
int bat_act[12];
//コウモリのアニメーションモーション
int bat_motion[] = { 0,1,2,1 };
int bat_index = 0;

int bat_wait = 1;

//コウモリの向き
int bat_dir = 0;

bool enemy2Live = FALSE; //コウモリが生きているかどうかフラグ

bool killBat = FALSE; //コウモリを殺したかどうかのフラグ

//コウモリ2体
float x_bat2[2] = { 100.0f,500.0f };
float y_bat2[2] = { 200.0f,200.0f };
int bat1_act[12];
int bat2_act[12];
int bat2_motion[] = { 0,1,2,1 };
int bat2_index = 0;
int bat2_wait = 1;
int bat2_dir = 0;
bool live[2] = { FALSE,FALSE }; //それぞれのコウモリの生きているかどうかフラグ
bool killBat2[2] = { FALSE,FALSE }; //それぞれのコウモリを殺したかどうかのフラグ


//アイテム(クリスタル)
float x_item; //x,y座標
float y_item;
int item_w = 32;//幅、高さ
int item_h = 32;
bool isDrop = FALSE; //落としたかどうか
int item_handle[12]; //クリスタルの画像ハンドル
bool itemGet = FALSE; //クリスタルを手に入れたか

//アイテム２(オーブ)
float x_item2 = 90; //x,y
float y_item2 = 370;
int item2_w = 32; //幅、高さ
int item2_h = 32;
int item2_handle[12]; //オーブの画像ハンドル
bool item2Get = FALSE; //オーブを手に入れたか


//タイトル画面定義
//タイトル画面ハンドル
int titleHandle;
int title_x = 100; //x,y
int title_y = 0;
int title_w = 597; //幅、高さ
int title_h = 269;
bool showTitle = TRUE; //タイトルを表示しているかどうか

//キャラクタ初期化
void Chara_Init() {
	LoadDivGraph("obake.png", ACT_NUM_ALL, ACT_NUM_X, ACT_NUM_Y, chara_width, chara_height, chara_act);

}
//敵キャラ初期化
void Enemy_Init() {
	LoadDivGraph("Enemy.png",ENE_NUM_ALL,ENE_NUM_X,ENE_NUM_Y,enemy_width,enemy_height,enemy_act);
}
//コウモリ初期化
void Bat_Init() {
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat_act);
}
//コウモリ２初期化
void Bat2_Init() {
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat1_act);
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat2_act);
}
//アイテム初期化
void Item_Init() {
	LoadDivGraph("pipo-etcchara002b.png", 12, 3, 4, 32, 32, item_handle); //クリスタルをロード
	LoadDivGraph("pipo-etcchara002b.png", 12, 3, 4, 32, 32, item2_handle);//オーブをロード
}

//タイトル画面ロード
void Title_Init() {
	titleHandle = LoadGraph("弾丸突破バレットチョイス　タイトル画面.png");
}

//弾丸の速度と向きを記憶する変数
float speed = 3.0f;
int direct = 3; //0:上　1:左　2:右　3:なし
int direct_Brack = 3; //暗黒弾版
int direct_Bullet = 3; //鉛弾版

//キャラクタ移動
void Chara_Move() {
	//前の位置
	old_x = x;
	old_y = y;

	//画面の外に行けば画面内に戻す
	if (y > 600) y = 500;
	if (x > 800) x = 100;
	if (x < 0) x = 700;

	//キー情報を取得
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (showTitle == FALSE) { //タイトルが表示されていなければ(タイトルをぶっ壊していたら動かせる)
		if (input & PAD_INPUT_RIGHT) { //右移動
			x++;
			act_dir = 2;
		}
		if (input & PAD_INPUT_LEFT) { //左移動
			x--;
			act_dir = 1;
		}
	}
	//上を向く(正面を向く)
	if (input & PAD_INPUT_UP) {
		act_dir = 0;
	}

	//弾が出ていないとき
	if (isShot == false) {

		//弾を表示
		if (input & PAD_INPUT_B) {
			PlaySoundMem(shotSEHandle, DX_PLAYTYPE_BACK);
			shot_x = x + 16;
			shot_y = y + 16;
			isShot = true;
		}
	}

	//弾が出ていないとき２
	if (isShot2== false && canShotBrackball == true) { //暗黒弾は撃てるが、まだ撃ってない状態のとき

		//弾を表示
		if (input & PAD_INPUT_C){
			PlaySoundMem(shotBrackSEHandle, DX_PLAYTYPE_BACK);
			shotBrack_x = x + 16;
			shotBrack_y = y + 16;
			isShot2= true;
		}
	}
	
	//弾が出ていないとき３
	if (canShotBulletFlag == 1) { //鉛弾を撃てるとき
		if (isShot3 == false) { //まだ撃ってないとき

			//弾を表示
			if (input & PAD_INPUT_X) {
				PlaySoundMem(shotBulletSEHandle, DX_PLAYTYPE_BACK);
				shotBullet_x = x + 16;
				shotBullet_y = y + 16;
				isShot3 = true;
			}
		}
	}
	//通常弾
	if (isShot && direct == 3) {
		if (act_dir == 2) { //右を向いていたら
			direct = 2; //弾向きを固定
		}
		if (act_dir == 1) { //左を向いていたら
			direct = 1;
		}
		if (act_dir == 0) {
			direct = 0;
		}
	}
	//弾の向き(directの値)によって行先が変わる
	if (direct == 2) {
		shot_x += 8;
		DrawCircle(shot_x, shot_y, 10, GetColor(255, 255, 255), TRUE);
	}
	if (direct == 1) {
		shot_x -= 8;
		DrawCircle(shot_x, shot_y, 10, GetColor(255, 255, 255), TRUE);
	}
	if (direct == 0) {
		shot_y -= 8;
		DrawCircle(shot_x, shot_y, 10, GetColor(255, 255, 255), TRUE);
	}

	//弾が画面外に出たら
	if (shot_x > 800 || shot_x < 0 || shot_y < 0) {
		isShot = false;
		direct = 3; //弾向きを初期化
	}
	//動きを止める弾(暗黒弾)
	if (isShot2 && direct_Brack == 3){
		if (act_dir == 2) { //右を向いていたら
			direct_Brack = 2;
		}
		if (act_dir == 1) { //左を向いていたら
			direct_Brack = 1;
		}
		if (act_dir == 0) {
			direct_Brack = 0;
		}
	}
	//向きによって行き先を変える
	if (direct_Brack == 2) {
		shotBrack_x += 8;
		DrawCircle(shotBrack_x, shotBrack_y, 10, GetColor(0, 0, 0), TRUE);
	}
	if (direct_Brack == 1) {
		shotBrack_x -= 8;
		DrawCircle(shotBrack_x, shotBrack_y, 10, GetColor(0, 0, 0), TRUE);
	}
	if (direct_Brack == 0) {
		shotBrack_y -= 8;
		DrawCircle(shotBrack_x, shotBrack_y, 10, GetColor(0, 0, 0), TRUE);
	}
	//暗黒弾が画面外に出たら消す
	if (shotBrack_x > 800 || shotBrack_x < 0 || shotBrack_y < 0) {
		isShot2 = false;
		direct_Brack = 3;
	}

	//鉛弾の場合
	if (isShot3 && direct_Bullet == 3) {
		if (act_dir == 2) {
			direct_Bullet = 2;
		}
		if (act_dir == 1) {
			direct_Bullet = 1;
		}
		if (act_dir == 0) {
			direct_Bullet = 0;
		}
	}
	//鉛弾の向きによって行き先を変える
	if (direct_Bullet == 2) {
		shotBullet_x += 3;
		DrawCircle(shotBullet_x, shotBullet_y, 10, GetColor(255, 0, 0), TRUE);
	}
	if (direct_Bullet == 1) {
		shotBullet_x -= 3;
		DrawCircle(shotBullet_x, shotBullet_y, 10, GetColor(255, 0, 0), TRUE);
	}
	if (direct_Bullet == 0) {
		shotBullet_y -= 3;
		DrawCircle(shotBullet_x, shotBullet_y, 10, GetColor(255, 0, 0), TRUE);
		y = shotBullet_y -20;
		yadd = 0.0f;
		jFlag = FALSE;
	}
	//鉛弾が画面外に出たら消す
	if (shotBullet_x > 800 || shotBullet_x < 0 || shotBullet_y > 800 || shotBullet_y < 0) {
		isShot3 = false;
		direct_Bullet = 3;
	}

	//ジャンプ処理
	if (showTitle == FALSE) {
		if (!jFlag) {
			if (input & PAD_INPUT_A) {
				PlaySoundMem(jumpSEHandle, DX_PLAYTYPE_BACK);
				yadd = initVy;
				jFlag = true;
			}
			y += yadd;
			yadd += gravity;
			yadd = std::min(30.0f, std::max(-30.0f, yadd)); //丸め
		}
		if (jFlag) {
			y += yadd;
			yadd += gravity;
			yadd = std::min(30.0f, std::max(-30.0f, yadd));
			if (y > (SCREEN_HEIGHT - enemy_height) / 2 + 32 * 7) {
				y = (SCREEN_HEIGHT - enemy_height) / 2 + 32 * 7;
				jFlag = false;
			}
		}
	}
}

//キャラクタアニメーション更新
void Chara_Ani() {
	if (--act_wait <= 0) {
		act_index++;
		act_wait = ACT_SPEED;
		act_index %= MAX_MOTION_INDEX;
	}
}


//キャラクタ更新
void Chara_Update() {
	if (damaged) {
		y += 3.0;
		return;
	}
	Chara_Move();
	Chara_Ani();
}

//キャラクタ描画
void Chara_Draw() {
	if (gameCrear) return;

	int motion_index = act_motion[act_index];

	DrawGraph(x, y, chara_act[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
}
//ゴーストの移動関数
void Enemy_Move() {

	const float speed = 1.0f;
	if (enemyLive) { //生きているかどうか
		
		x_enemy--;
		ene_dir = 1;

		if (x_enemy < 0) {
			x_enemy = 800;
		}

		if (x_enemy < 0) {
			enemyLive = FALSE;
			enemy2Live = TRUE;
		}

	}
}
//最初のコウモリ用
bool isBottom = FALSE; //それぞれ下にいるか、上にいるか、左にいるか、右にいるか確認するフラグ
bool isTop = TRUE;
bool isLeft = TRUE;
bool isRight = FALSE;
bool migikara;//右から降りてきたか
bool hidarikara;//左から降りてきたか

//コウモリ２の１用
bool isBottom1 = FALSE; //それぞれ下にいるか、上にいるか、左にいるか、右にいるか確認するフラグ
bool isTop1 = TRUE;
bool isLeft1 = TRUE;
bool isRight1 = FALSE;
bool migikara1;//右から降りてきたか
bool hidarikara1;//左から降りてきたか
bool isBind = FALSE;

//コウモリ２の２用
bool isBottom2 = FALSE; //それぞれ下にいるか、上にいるか、左にいるか、右にいるか確認するフラグ
bool isTop2 = TRUE;
bool isLeft2 = TRUE;
bool isRight2 = FALSE;
bool migikara2;//右から降りてきたか
bool hidarikara2;//左から降りてきたか
bool isBind2 = FALSE;

void Bat_Move() {
	//最初のコウモリの挙動
	if (enemy2Live) {
		if (x_bat == (SCREEN_WIDTH - enemy_width) / 2 - 100 && y_bat == (SCREEN_HEIGHT - enemy_height) / 2) { //左上(初期位置)にいるとき
			isBottom = FALSE;
			isTop = TRUE;
			isLeft = TRUE;
			isRight = FALSE;
		}

		if (isBottom == FALSE && isTop == TRUE && isLeft == TRUE && isRight == FALSE) { //左上から下へ降りている
			x_bat += 0.5f;
			y_bat += 1.5f;
		}
		if (y_bat == 500) { //一番下に行ったとき
			if (isLeft) {
				isBottom = TRUE;
				isTop = FALSE;
				isLeft = FALSE;
				isRight = FALSE;
				migikara = FALSE;
				hidarikara = TRUE;
			}
			if (isRight) {
				isBottom = TRUE;
				isTop = FALSE;
				isLeft = FALSE;
				isRight = FALSE;
				migikara = TRUE;
				hidarikara = FALSE;
			}
		}
		if (isBottom == TRUE && isTop == FALSE && migikara == FALSE && hidarikara == TRUE) { //左から降りてきたとき
			x_bat += 0.5f;
			y_bat -= 1.5f;
		}
		if (isBottom == TRUE && isTop == FALSE && migikara == TRUE && hidarikara == FALSE) { //右から降りてきたとき
			x_bat -= 0.5f;
			y_bat -= 1.5f;
		}
		if (x_bat != (SCREEN_WIDTH - enemy_width) / 2 - 100 && y_bat == (SCREEN_HEIGHT - enemy_height) / 2) { //右上にいるとき
			isRight = TRUE;
			isLeft = FALSE;
			isBottom = FALSE;
			isTop = TRUE;
		}
		if (isRight == TRUE && isLeft == FALSE) { //右上から下に向かう
			x_bat -= 0.5f;
			y_bat += 1.5f;
		}	
	}
	//コウモリ２の１の挙動
	if (live[0]) {
		if (!isBind) {
			if (x_bat2[0] == 100.0f && y_bat2[0] == 200.0f) { //左上(初期位置)にいるとき
				isBottom1 = FALSE;
				isTop1 = TRUE;
				isLeft1 = TRUE;
				isRight1 = FALSE;
			}

			if (isBottom1 == FALSE && isTop1 == TRUE && isLeft1 == TRUE && isRight1 == FALSE) { //左上から下へ降りている
				x_bat2[0] += 0.5f;
				y_bat2[0] += 1.5f;
			}
			if (y_bat2[0] == 500) { //一番下に行ったとき
				if (isLeft1) {
					isBottom1 = TRUE;
					isTop1 = FALSE;
					isLeft1 = FALSE;
					isRight1 = FALSE;
					migikara1 = FALSE;
					hidarikara1 = TRUE;
				}
				if (isRight1) {
					isBottom1 = TRUE;
					isTop1 = FALSE;
					isLeft1 = FALSE;
					isRight1 = FALSE;
					migikara1 = TRUE;
					hidarikara1 = FALSE;
				}
			}
			if (isBottom1 == TRUE && isTop1 == FALSE && migikara1 == FALSE && hidarikara1 == TRUE) { //左から降りてきたとき
				x_bat2[0] += 0.5f;
				y_bat2[0] -= 1.5f;
			}
			if (isBottom1 == TRUE && isTop1 == FALSE && migikara1 == TRUE && hidarikara1 == FALSE) { //右から降りてきたとき
				x_bat2[0] -= 0.5f;
				y_bat2[0] -= 1.5f;
			}
			if (x_bat2[0] != 100.0f && y_bat2[0] == 200.0f) { //右上にいるとき
				isRight1 = TRUE;
				isLeft1 = FALSE;
				isBottom1 = FALSE;
				isTop1 = TRUE;
			}
			if (isRight1 == TRUE && isLeft1 == FALSE) { //右上から下に向かう
				x_bat2[0] -= 0.5f;
				y_bat2[0] += 1.5f;
			}
		}
	}
	//コウモリ２の２の挙動
	if (live[1]) {
		if (!isBind2) {
			if (x_bat2[1] == 500.0f && y_bat2[1] == 200.0f) { //左上(初期位置)にいるとき
				isBottom2 = FALSE;
				isTop2 = TRUE;
				isLeft2 = TRUE;
				isRight2 = FALSE;
			}

			if (isBottom2 == FALSE && isTop2 == TRUE && isLeft2 == TRUE && isRight2 == FALSE) { //左上から下へ降りている
				x_bat2[1] += 0.5f;
				y_bat2[1] += 1.5f;
			}
			if (y_bat2[1] == 500) { //一番下に行ったとき
				if (isLeft2) {
					isBottom2 = TRUE;
					isTop2 = FALSE;
					isLeft2 = FALSE;
					isRight2 = FALSE;
					migikara2 = FALSE;
					hidarikara2 = TRUE;
				}
				if (isRight2) {
					isBottom2 = TRUE;
					isTop2 = FALSE;
					isLeft2 = FALSE;
					isRight2 = FALSE;
					migikara2 = TRUE;
					hidarikara2 = FALSE;
				}
			}
			if (isBottom2 == TRUE && isTop2 == FALSE && migikara2 == FALSE && hidarikara2 == TRUE) { //左から降りてきたとき
				x_bat2[1] += 0.5f;
				y_bat2[1] -= 1.5f;
			}
			if (isBottom2 == TRUE && isTop2 == FALSE && migikara2 == TRUE && hidarikara2 == FALSE) { //右から降りてきたとき
				x_bat2[1] -= 0.5f;
				y_bat2[1] -= 1.5f;
			}
			if (x_bat2[1] != 500.0f && y_bat2[1] == 200.0f) { //右上にいるとき
				isRight2 = TRUE;
				isLeft2 = FALSE;
				isBottom2 = FALSE;
				isTop2 = TRUE;
			}
			if (isRight2 == TRUE && isLeft2 == FALSE) { //右上から下に向かう
				x_bat2[1] -= 0.5f;
				y_bat2[1] += 1.5f;
			}
		}
	}
}

//エネミーアニメーション更新
void Enemy_Ani() {
	if (--ene_wait <= 0) {
		ene_index++;
		ene_wait = ACT_SPEED;
		ene_index %= MAX_ENE_MOTION_INDEX;
	}
}
//batアニメーション更新
void Bat_Ani() {
	if (--bat_wait <= 0) {
		bat_index++;
		bat_wait = ACT_SPEED;
		bat_index %= MAX_ENE_MOTION_INDEX;
	}
}

void Bat2_Ani() {
	
		if (--bat2_wait <= 0) {
			bat2_index++;
			bat2_wait = ACT_SPEED;
			bat2_index %= MAX_ENE_MOTION_INDEX;
		}
	
}
//アイテムドロップ関数
void Item_Drop(float x, float y) {
	isDrop = TRUE;
	x_item = x;
	y_item = y;
}

void Enemy_Update() {
	Enemy_Move();
	Enemy_Ani();
}

void Bat_Update() {
	Bat_Move();
	Bat_Ani();
}

void Bat2_Update() {
	Bat_Move();
	Bat2_Ani();
}

int Count = 0;

//敵全体の描画関数
void Enemy_Draw() {
	int motion_index = ene_motion[ene_index];
	int motion_index2 = bat_motion[bat_index];
	int motion_index3 = bat2_motion[bat2_index];
	int motion_index4 = bat2_motion[bat2_index];
	//ゴースト
	if (enemyLive){
	DrawGraph(x_enemy, y_enemy, enemy_act[motion_index + ene_dir * ENE_DIR_SLIDE], TRUE);
	}
	//最初のコウモリ
	if (enemy2Live && killBat == FALSE) {
		DrawRotaGraph(x_bat, y_bat, 1.0, 0.0, bat_act[motion_index2 + bat_dir * ENE_DIR_SLIDE], TRUE); //画像の描画
	}
	//コウモリ２
	if (live[0] == TRUE && killBat2[0] == FALSE) {
		DrawRotaGraph(x_bat2[0], y_bat2[0], 1.0, 0.0, bat1_act[motion_index3 + bat2_dir * ENE_DIR_SLIDE], TRUE); //画像の描画
	}
	if (live[1] == TRUE && killBat2[1] == FALSE) {
		DrawRotaGraph(x_bat2[1], y_bat2[1], 1.0, 0.0, bat2_act[motion_index4 + bat2_dir * ENE_DIR_SLIDE], TRUE); //画像の描画

	}
}

//アイテムの描画関数
void Item_Draw() {
	if (isDrop && itemGet == FALSE) {
		DrawRotaGraph(x_item, y_item, 1.0, 0.0, item_handle[7], TRUE);
	}
	if (item2Get == FALSE) {
		DrawRotaGraph(x_item2, y_item2, 1.0, 0.0, item_handle[10], TRUE);
	}
}

//操作方法描画
void SosaHoho_Draw() {
	if (gameCrear == FALSE) {
		DrawFormatString(100, 580, GetColor(255, 255, 255), "←→キー：左右移動");
		DrawFormatString(300, 580, GetColor(255, 255, 255), "Zキー：ジャンプ");
		DrawFormatString(450, 580, GetColor(255, 255, 255), "Xキー：通常弾");
		if (canShotBrackball && canShotBulletFlag == 0) {
			DrawFormatString(600, 580, GetColor(255, 255, 255), "Cキー：暗黒弾");
		}
		if (canShotBrackball && canShotBulletFlag == 1) {
			DrawFormatString(600, 580, GetColor(255, 255, 255), "C,Aキー：暗黒弾,鉛弾");
		}
	}
	else {
		DrawFormatString(100, 580, GetColor(255, 255, 255), "エスケープキー：ゲーム終了");
	}
}

//タイトル描画関数
void Draw_Title() {
	if (showTitle) {
		DrawGraph(title_x, title_y, titleHandle, FALSE);
	}
}

//どのアビリティ(通常弾や暗黒弾など)が使えるかどうかを表示する
void Abirity_Draw() {
	if (gameCrear) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "【キャラクター・マップチップ】");
		DrawFormatString(0, 32, GetColor(255, 255, 255), "ぴぽや倉庫 様");
		DrawFormatString(0, 64, GetColor(255, 255, 255), "【BGM・SE】");
		DrawFormatString(0, 96, GetColor(255, 255, 255), "魔王魂 様");
		DrawFormatString(0, 96+32+32, GetColor(255, 255, 255), "created by Daiki Nara");
	}
	else {
		DrawBox(0, 0, 200, 140, GetColor(125, 125, 125), TRUE);//バックの長方形
		DrawRotaGraph(32, 32, 1.0, 0.0, item_handle[7], TRUE); //クリスタル(暗黒弾を撃てるアイテム)のアイコン
		DrawFormatString(64, 30, GetColor(0, 0, 0), "：%d", canBrackBallFlag);
		if (canBrackBallFlag == 1) DrawFormatString(30, 47, GetColor(0, 0, 0), "(「暗黒弾」発射可能)");

		DrawRotaGraph(32, 88, 1.0, 0.0, item_handle[10], TRUE); //オーブ(鉛弾を撃てるアイテム)のアイコン
		DrawFormatString(64, 80, GetColor(0, 0, 0), "：%d", canShotBulletFlag);
		if (canShotBulletFlag == 1) DrawFormatString(30, 100, GetColor(0, 0, 0), "(「鉛弾」発射可能)");
	}
}
//当たり判定関数
int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;
	int R1 = x1 + w1;
	int L2 = x2;
	int R2 = x2 + w2;

	if (R1 <= L2) return 0;
	if (R2 <= L1) return 0;

	int U1 = y1;
	int D1 = y1 + h1;
	int U2 = y2;
	int D2 = y2 + h2;

	if (D1 <= U2) return 0;
	if (D2 <= U1) return 0;

	return 1;
}
int count = 0;
void CheckHitEnemy() {
	//ゴーストと当たっているかどうか
	if (enemyLive) {
		if (CheckHit(x, y, chara_width, chara_height, x_enemy, y_enemy, enemy_width, enemy_height) && count == 0) {
			speed -= 0.5;
			x -= 5;
			count = 10; //カウンターセット

		}
		if (count > 0) {
			--count;
			if (count <= 0) {
				count = 0;
			}
		}
	}

	//コウモリと当たっているかどうか
	if (enemy2Live) {
		if (CheckHit(x, y, chara_width, chara_height, x_bat, y_bat, enemy_width, enemy_height) && count == 0) {
			speed -= 0.2;
			x -= 5;
			count = 10; //カウンターセット

		}
		if (count > 0) {
			--count;
			if (count <= 0) {
				count = 0;
			}
		}
	}
	if (live[0] == TRUE && killBat2[0] == FALSE) {
		//暗黒弾で止まった場合コウモリ２－１
		if (isBind) {
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
				if (y >= old_y) {
					if (old_y <= y_bat2[0]) {
						yadd = 0.0f;
						jFlag = false;
					}
				}
			}
		}
		else {//暗黒弾で止まっていない場合コウモリ２－１
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[0], y_bat2[0], enemy_width, enemy_height) && count == 0) {
				damageCounter = 10; //ダメージカウンターが正のときはダメージを受けている＝硬直
				count = 10;
			}
			if (count > 0) {
				--count;
				if (count <= 0) {
					count = 0;
				}
			}
			if (damageCounter > 0) {
				--damageCounter;
				if (damageCounter <= 0) {
					damageCounter = 0;
				}
			}
		}
	}
	if (live[1] == TRUE && killBat2[1] == FALSE) {
		//暗黒弾で止まった場合コウモリ２－２
		if (isBind2) {
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
				if (y >= old_y) {
					if (old_y <= y_bat2[1]) {
						yadd = 0.0f;
						jFlag = false;
					}
				}
			}
		}
		else {//暗黒弾で止まっていない場合コウモリ２－２
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[1], y_bat2[1], enemy_width, enemy_height) && count == 0) {
				damageCounter = 10; //ダメージカウンターが正のときはダメージを受けている＝硬直
				count = 10;
			}
			if (count > 0) {
				--count;
				if (count <= 0) {
					count = 0;
				}
			}
			if (damageCounter > 0) {
				--damageCounter;
				if (damageCounter <= 0) {
					damageCounter = 0;
				}
			}
		}
	}
}

//アイテムとの当たり判定
void CheckHitItem() {
	if (CheckHit(x, y, chara_width, chara_height, x_item, y_item, item_w, item_h) && canBrackBallFlag == 0) {
		PlaySoundMem(getItemSEHandle, DX_PLAYTYPE_BACK);
		canShotBrackball = true;
		itemGet = TRUE;
		canBrackBallFlag = 1;
	}
	if (CheckHit(x, y, chara_width, chara_height, x_item2, y_item2, item2_w, item2_h) && canShotBulletFlag == 0) {
		PlaySoundMem(getItemSEHandle, DX_PLAYTYPE_BACK);
		canShotBulletFlag = 1;
		item2Get = TRUE;
	}
}

//タイトル画面との当たり判定
void CheckHitTitle() {
	if (CheckHit(shot_x, shot_y, 20, 20, title_x, title_y, title_w, title_h)) {
		showTitle = FALSE;
	}
}

//鉛弾との当たり判定
void CheckHitBullet() {
	if (CheckHit(x, y, chara_width, chara_height, shotBullet_x+30, shotBullet_y+30, 20, 20)) {
		if (y >= old_y) {
			if (old_y <= shotBullet_y) {
				yadd = 0.0f;
				jFlag = false;
			}
		}
		
	}
}

void CheckDamage() {
	if (damageCounter > 0) {
		damaged = TRUE;
	}
	else {
		damaged = FALSE;
	}
}

void Map_HitCheck() {
	for (int j = 0; j < NUM_MAP_Y; j++) {
		for (int i = 0; i < NUM_MAP_X; i++) {
			int no = data[i + j * NUM_MAP_X];
			if (no >= 10 && no < 20) {
				if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y, x, y, chara_width, chara_height)) {
					
					if (y >= old_y) { 
						if (j * SIZE_MAP_Y - chara_height >= old_y) {
							old_y = j * SIZE_MAP_Y - chara_height;
							y = old_y;
							jFlag = false;
						}
						else {
							int _x = std::max(x, old_x);
							_x /= SIZE_MAP_X;
							_x *= SIZE_MAP_X;
							x = _x;
							old_x = x;
							//jFlag = FALSE;
						}
					}
					else { //下から当たっているか
						if ((j + 1) * SIZE_MAP_Y <= old_y) {
							old_y = (j + 1) * SIZE_MAP_Y;
							y = old_y;
							yadd = 0.0f;
						}
						else {
							int _x = std::max(x, old_x);
							_x /= SIZE_MAP_X;
							_x *= SIZE_MAP_X;
							x = _x;
							old_x = x;
						}
					}
				}
				//鉛弾に触れた場合、それは破壊される
				if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y, shotBullet_x, shotBullet_y, 32, 32)) {
					if (data[i + j * NUM_MAP_X] != 10) {
						data[i + j * NUM_MAP_X] = 0;
					}
				}
			}
		}
	}
}

void AttackHit() {
	//ゴーストに攻撃
	if (CheckHit(shot_x, shot_y, 20, 20, x_enemy, y_enemy, enemy_width, enemy_height)) {
		enemyLive = FALSE; 
		if (enemy2Live == FALSE) enemy2Live = TRUE;
	}
	//コウモリに攻撃
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat, y_bat, enemy_width, enemy_height)) {
		enemy2Live = FALSE;
		killBat = TRUE;
		Item_Drop(x_bat,y_bat); //アイテムドロップ
		if (live[0] == FALSE && live[1] == FALSE) { live[0] = TRUE; live[1] = TRUE; } //第3ウェーブへ
	}
	//コウモリ２の１に攻撃(通常弾)
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		if (isBind) {
			isBind = FALSE;
		} //停止解除or効果なし
	}
	//コウモリ２の１に攻撃(暗黒弾)
	if (CheckHit(shotBrack_x, shotBrack_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		isBind = TRUE; //停止
	}
	//コウモリ２の１に攻撃(鉛弾)で倒す
	if (CheckHit(shotBullet_x, shotBullet_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		killBat2[0] = TRUE;
	}
	//コウモリ２の２に攻撃(通常弾)
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		if (isBind2) {
			isBind2 = FALSE;
		} //停止解除or効果なし
	}
	//コウモリ２の２に攻撃(暗黒弾)
	if (CheckHit(shotBrack_x, shotBrack_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		isBind2 = TRUE; //停止
	}
	//コウモリ２の２に攻撃(鉛弾)で倒す
	if (CheckHit(shotBullet_x, shotBullet_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		killBat2[1] = TRUE;
	}
}

//クリア判定
void IsClear() {
	//画面上部へ行ったか
	if (y < 0) {
		//コウモリ２体倒していたら
		if (killBat2[0] == TRUE && killBat2[1] == TRUE && gameCrear == FALSE) {
			StopSoundMem(bgmHandle);
			PlaySoundMem(clearSEHandle, DX_PLAYTYPE_BACK);
			gameCrear = TRUE;
		}
		else {
			y = 0;
			DrawBox(300, 0, 600, 100, GetColor(125, 100, 100), TRUE);//バックの長方形
			DrawFormatString(300, 0, GetColor(255, 255, 255), "ヒント：");
			DrawFormatString(300, 32, GetColor(0, 0, 255), "敵をたおしてから戻ってきて！");
		}
	}
}
//エンド処理関数
void End() {
	if (gameCrear) {
		//クリア画面表示
		DrawFormatString(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, GetColor(255, 255, 255), "You cleared it !");
		DrawFormatString(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, GetColor(0, 255, 0), "Congratulations!!");
		yadd = 0.0f;
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		DxLib_End();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	
	SetWindowText("弾丸突破バレットチョイス");

	SetGraphMode(SCREEN_WIDTH,SCREEN_HEIGHT,32);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	//タイトル画面ロード
	Title_Init();

	//キャラクタロード
	Chara_Init();
	
	//エネミーロード
	Enemy_Init();

	//コウモリロード
	Bat_Init();

	//コウモリ２ロード
	Bat2_Init();

	//アイテムロード
	Item_Init();

	//マップ初期化
	Map_Init();

	//BGM,SE初期化
	Music_Init();

	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

	//メインループ///
	while (ProcessMessage() == 0) {
		//裏画面消す
		ClearDrawScreen();

		//マップ描画
		Map_Draw();

		//キャラクタ更新
		Chara_Update();
		
		//エネミー更新
		Enemy_Update();

		//エネミー2更新
		Bat_Update();

		//コウモリ２更新
		Bat2_Update();

		//ブロックの当たり判定
		Map_HitCheck();

		//攻撃の当たり判定
		AttackHit();

		//敵ゴーストとの当たり判定
		CheckHitEnemy();

		//ダメージを受けているか
		CheckDamage();

		//アイテムとの当たり判定
		CheckHitItem();

		//タイトル画面との当たり判定
		CheckHitTitle();

		//鉛弾との当たり判定
		CheckHitBullet();
		
		//エネミー描画
		Enemy_Draw();

		//アイテム描画
		Item_Draw();

		//キャラクタ描画
		Chara_Draw();

		//操作方法描画
		SosaHoho_Draw();
		
		//アビリティ描画
		Abirity_Draw();

		//タイトル画面描画
		Draw_Title();

		//クリア判定
		IsClear();
		
		//エンド処理
		End();

		ScreenFlip();
	}

	DxLib_End();
	return 0;

}
