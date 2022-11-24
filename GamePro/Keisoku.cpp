#include "DxLib.h"

//��ʃT�C�Y��`
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

int canjumpFrag = 1; //�W�����v�ł��邩
double F = -1.0f; //�}���I�W�����v�̂Ƃ��ɉ�����́B�W�����v�̂Ƃ���-10,����ȊO��-1

double x = 100;
double y = 450;
double y_prev = y; //�}���I�W�����v�̂Ƃ��̑O���y���W���i�[����ϐ��B�P�t���[���O��y���W
int yuka = SCREEN_HEIGHT - 50;

//�}���I�W�����v�Z�b�g(�W�����v�Əd�͂̈�̌^)
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
    ChangeWindowMode(TRUE);              //�E�B���h�E���[�h�ɂ���B

	LONGLONG StartTime;

    if (DxLib_Init() == -1) return -1; // �c�w���C�u�������������� �G���[���N������I�� 

	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    int i, a = 0, time, White;
    White = GetColor(255, 255, 255); // ���F�̒l���擾

	// ���݌o�ߎ��Ԃ𓾂�
	StartTime = GetNowHiPerformanceCount();

	MarioJumpGravity(&input, &y, &y_prev, yuka); //�}���I�W�����v�Z�b�g

	time = GetNowHiPerformanceCount() - StartTime;

	DrawFormatString(0, 100, White, "%I64d�}�C�N���b", time);//������\��
    
	WaitKey();                     // �L�[�̓��͑҂�(�wWaitKey�x���g�p)
    DxLib_End();                   // �c�w���C�u�����g�p�̏I������
    return 0;                      // �\�t�g�̏I��
}