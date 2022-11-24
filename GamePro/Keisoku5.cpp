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
double jumpSpeed = -10.0f;
double VY;


//�Œ蒷�W�����v
void FixedJump(int* inputP, double* y, int yuka) {
	//�ʏ��Ԃ̂Ƃ�
	if (canjumpFrag) {
		//�W�����v�{�^����������Ă�����W�����v��ԂɈڍs����
		if (*inputP & PAD_INPUT_1) {
			canjumpFrag = FALSE;
			VY = jumpSpeed;
		}
	}
	else
		//�W�����v��Ԃ̂Ƃ�
	{
		VY += gravity;

		*y += VY;

		//���n�̔���
		if (*y >= yuka) {
			*y = yuka;
			canjumpFrag = TRUE;
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
	
	FixedJump(&input, &y, yuka); //�Œ蒷�W�����v

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64d�}�C�N���b", time);//������\��
    
	WaitKey();                     // �L�[�̓��͑҂�(�wWaitKey�x���g�p)
    DxLib_End();                   // �c�w���C�u�����g�p�̏I������
    return 0;                      // �\�t�g�̏I��
}