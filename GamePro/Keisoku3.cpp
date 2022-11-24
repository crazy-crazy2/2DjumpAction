#include "DxLib.h"
#include<math.h>

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
double VY; //y�����̑��x
double doubleJumpVy = 0.1f; //�_�u���W�����v�ł���͈͂�y�����̑��x
int jump_count = 1;

//�_�u���W�����v(2�i�W�����v)
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

		//2�i�W�����v����
		if (fabs(VY) < doubleJumpVy && (*inputP & PAD_INPUT_1) && JumpCount < jump_count) {
			VY = jumpSpeed;
			JumpCount++;
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
	
	DoubleJump(&input,&y,yuka); //�_�u���W�����v�Z�b�g

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64d�}�C�N���b", time);//������\��
    
	WaitKey();                     // �L�[�̓��͑҂�(�wWaitKey�x���g�p)
    DxLib_End();                   // �c�w���C�u�����g�p�̏I������
    return 0;                      // �\�t�g�̏I��
}