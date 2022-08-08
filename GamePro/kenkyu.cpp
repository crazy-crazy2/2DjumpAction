#include"DxLib.h"
#include<math.h>
#include"teigi.cpp"

#define PI 3.14159265359

//��ʃT�C�Y��`
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

//�L�����N�^��`
const int chara_width = 32;
const int chara_height = 32;
double x = 100;
double y = 450;
int charaH[12]; //�n���h��
int canjumpFrag = 1; //�W�����v�ł��邩

//�L�����N�^���x�֌W
int v0 = 0; //�����x
int time = 0;
double gravity = 0.5;

//�G�l�~�[��`
const int enemy_width = 32;
const int enemy_height = 32;
int x_enemy = 300;
int y_enemy = SCREEN_HEIGHT - 50;
int enemyH[12];

//�L����������
void Chara_Init() {
	LoadDivGraph("obake.png", 12, 3, 4, 32, 32, charaH);
}

int jumpFrames = 0; //�W�����v���̃t���[���J�E���g
double radPerFrame = 2 * PI / 40;
int heightJump = 100;

//sin�g�𗘗p�����d��
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
//sin�g�𗘗p�����W�����v
void SinJump() {
	if (canjumpFrag) {
		canjumpFrag = 0;
		jumpFrames = 0;
	}
}

//�����̌����d��
void PhysicsGravity(double* y, int* v0, int yuka, int time) {
	*y = (0.5 * gravity * time * time - *v0 * time) + yuka;

	if (*y >= yuka) {
		*y = yuka;
		canjumpFrag = 1;
	}
}
//���������̃W�����v
void PhysicsJump(int* v0,int* time) {
	
	if (canjumpFrag == 1) {
		*v0 = 10;
		*time = 0;
		canjumpFrag = 0;
	}	
}
int yuka = SCREEN_HEIGHT - 50;
//�L�����ړ�
void Chara_Move() {
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input & PAD_INPUT_RIGHT) {
		x += 5;
	}
	if (input & PAD_INPUT_LEFT) {
		x -= 5;
	}
	if (input & PAD_INPUT_1) {
		//���p�������֐��ȊO�̓R�����g�ɂ��邱��
		//PhysicsJump(&v0, &time);
		SinJump();
	}

	//���p�������֐��ɍ��킹���֐�(PhysicsJump���g���������PhysicsGravity�Ƃ������悤��)���R�����g�O�����邱�ƁB����ȊO�̓R�����g�ɂ��邱�ƁB
	//PhysicsGravity(&y, &v0, 450, time);
	SinGravity(&y, 450);

	time += 1;
}
//�L�����`��
void Chara_Draw() {
	DrawGraph(x, y, charaH[8], TRUE);
}
//�G�l�~�[������
void Enemy_Init() {
	LoadDivGraph("Enemy.png",12,3,4,32,32,enemyH);
}
//�G�l�~�[�ړ�
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

		//�L�����ړ�
		Chara_Move();
		//�G�l�~�[�ړ�
		Enemy_Move();

		//�L�����`��
		Chara_Draw();
		//�G�l�~�[�`��
		Enemy_Draw();

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}