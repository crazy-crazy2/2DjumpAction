#include "DxLib.h"
#include<math.h>

#define PI 3.14159265359

//��ʃT�C�Y��`
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

int canjumpFrag = 1; //�W�����v�ł��邩
int v0 = 0; //�����x
int times = 0;
double x = 100;
double y = 450;
double gravity = 0.5;
int yuka = SCREEN_HEIGHT - 50;
int JumpCount = 0; //�W�����v�J�E���g,�W�����v�̒i��
double jumpSpeed = -10.0f;
int jumpFrames = 0; //�W�����v���̃t���[���J�E���g
double radPerFrame = 2 * PI / 40;
int heightJump = 100;

//�T�C���W�����v�Z�b�g
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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ChangeWindowMode(TRUE);              //�E�B���h�E���[�h�ɂ���B

	LONGLONG StartTime;

    if (DxLib_Init() == -1) return -1; // �c�w���C�u�������������� �G���[���N������I�� 

	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    int i, a = 0, time, White;
    White = GetColor(255, 255, 255); // ���F�̒l���擾

	
	// ���݌o�ߎ��Ԃ𓾂�
	StartTime = GetNowHiPerformanceCount();
	
	SinJumpGravity(&input,&y,yuka); //sin�W�����v�Z�b�g

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64d�}�C�N���b", time);//������\��
    
	WaitKey();                     // �L�[�̓��͑҂�(�wWaitKey�x���g�p)
    DxLib_End();                   // �c�w���C�u�����g�p�̏I������
    return 0;                      // �\�t�g�̏I��
}