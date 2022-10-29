#define NOMINMAX
#include "DxLib.h"
#include <math.h>
#include <algorithm>
#define PI 3.141592654f


//��ʃT�C�Y�ݒ�
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//�}�b�v�`�b�v��`
const int SIZE_MAP_X = 32;
const int SIZE_MAP_Y = 32;
const int NUM_CHIP_X = 10;
const int NUM_CHIP_Y = 4;
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y;
int chip[NUM_CHIP_ALL];

//�}�b�v�`�b�v��
const int NUM_MAP_X = 25;
const int NUM_MAP_Y = 18;

//�N���A����p�ϐ�
bool gameCrear = FALSE;

//�X�e�[�W�f�[�^
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

//�}�b�v�̏�����
void Map_Init() {
	LoadDivGraph("mapchip.png", NUM_CHIP_ALL, NUM_CHIP_X, NUM_CHIP_Y, SIZE_MAP_X, SIZE_MAP_Y, chip);

}

//�}�b�v�`��
void Map_Draw() {
	if (gameCrear) return; //�N���A�t���O�������Ă������΂�
	//�w�i�̕\��
	for (int j = 0; j < NUM_MAP_Y; j++) {
		for (int i = 0; i < NUM_MAP_X; i++) {
			int no = data[i + j * NUM_MAP_X];
			DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, chip[no], FALSE);
		}
	}
}

//Music�n�̃n���h��
//BGM//
int bgmHandle;
//SE//
int jumpSEHandle;
int shotSEHandle;
int shotBrackSEHandle;
int shotBulletSEHandle;

int getItemSEHandle;

int clearSEHandle;

//BGM,SE�������A���[�h
void Music_Init() {
	jumpSEHandle = LoadSoundMem("������ ���ʉ� �V�X�e��38.ogg");
	bgmHandle = LoadSoundMem("������  8bit29.ogg");
	shotSEHandle = LoadSoundMem("������  �e02.ogg");
	shotBrackSEHandle = LoadSoundMem("������  �e05.ogg");
	shotBulletSEHandle = LoadSoundMem("������  ����05.ogg");
	getItemSEHandle = LoadSoundMem("������ ���ʉ� �V�X�e��10.ogg");
	clearSEHandle = LoadSoundMem("������ ���ʉ� �W���O��12.ogg");
}

//�L�����N�^��`
const int chara_width = 32; //�L�����N�^�̕�
const int chara_height = 32; //�L�����N�^�̍���
float x = (SCREEN_WIDTH - chara_width) / 2 ; //�L�����N�^��x���W
float y = (SCREEN_HEIGHT - chara_height) / 2 + 30; //�L�����N�^��y���W
float yadd = 0.0f; //y�����̑��xvy
float gravity = 0.2f; //�d��
float initVy = -6.0f; //y�����̏����x
//�O��̈ʒu
float old_x = 0.0f;
float old_y = 0.0f;

bool damaged = FALSE; //�_���[�W���󂯂Ă��邩
int damageCounter = 0; //�_���[�W�J�E���^�[

//�U��
int shot_x = 0; //�e���o��ʒu
int shot_y = 0;
int shotBrack_x = 0; //�Í��e���o��ʒu
int shotBrack_y = 0;
int shotBullet_x = 0; //���e���o��ʒu
int shotBullet_y = 0;
bool isShot = false; //�ʏ�e�������Ă��邩
bool isShot2 = false; //�������~�߂�e(�Í��e)�������Ă��邩
bool isShot3 = false; //���ʂ������Ă��邩
bool canShotBrackball = false; //�������~�߂�e(�Í��e)���u���Ă邩�v�ǂ���
int canBrackBallFlag = 0; //�Í��e���u���Ă邩�v�̃t���O(int)
int canShotBulletFlag = 0; //���e�����Ă邩�̃t���O

bool jFlag = FALSE; //�W�����v�t���O

int chara_act[12]; //�L�����N�^�摜�i�[

int act_motion[] = { 0,1,2,1, }; //�A�j���[�V�������[�V����
int act_index = 0; 
const int MAX_MOTION_INDEX = 4; //���[�V�����ő吔

const int ACT_SPEED = 20; //�A�j���[�V�����ω��̑��x
int act_wait = ACT_SPEED;
const int ACT_NUM_X = 3; //�L�����`�b�v�̐�x
const int ACT_NUM_Y = 4; //�L�����`�b�v�̐�y
const int ACT_NUM_ALL = ACT_NUM_X * ACT_NUM_Y; //�L�����`�b�v�̍��v��

const int ACT_DIR_SLIDE = ACT_NUM_X; //���܂ǂ̃`�b�v��I�����Ă��邩

int act_dir = 0; //�L�����N�^�̌���

//�G�l�~�[���

const int enemy_width = 32; //�G�L�����@�S�[�X�g�̕��A����
const int enemy_height = 32;
float x_enemy = (SCREEN_WIDTH - enemy_width) / 2 + 100; //�S�[�X�g��x,y���W
float y_enemy = (SCREEN_HEIGHT - enemy_height) / 2 + 32 * 7;

const int ENE_NUM_X = 3; //�S�[�X�g�̃L�����`�b�v��
const int ENE_NUM_Y = 3;
const int ENE_NUM_ALL = ENE_NUM_X * ENE_NUM_Y;

const int ENE_DIR_SLIDE = ENE_NUM_X; //���܂ǂ̃`�b�v��I�����Ă��邩

int enemy_act[12]; //�S�[�X�g�̃`�b�v�i�[

int ene_motion[] = { 0,1,2,1 }; //�S�[�X�g�̃A�j���[�V�������[�V����
int ene_index = 0;
const int MAX_ENE_MOTION_INDEX = 4;

int ene_wait = 1; //�G�l�~�[�X�s�[�h

int ene_dir = 0;

bool enemyLive = TRUE; //�S�[�X�g�������Ă��邩�ǂ����̃t���O

//�R�E����
float x_bat = (SCREEN_WIDTH - enemy_width) / 2 - 100;
float y_bat = (SCREEN_HEIGHT - enemy_height) / 2;

//�R�E�����̃L�����`�b�v��
int bat_act[12];
//�R�E�����̃A�j���[�V�������[�V����
int bat_motion[] = { 0,1,2,1 };
int bat_index = 0;

int bat_wait = 1;

//�R�E�����̌���
int bat_dir = 0;

bool enemy2Live = FALSE; //�R�E�����������Ă��邩�ǂ����t���O

bool killBat = FALSE; //�R�E�������E�������ǂ����̃t���O

//�R�E����2��
float x_bat2[2] = { 100.0f,500.0f };
float y_bat2[2] = { 200.0f,200.0f };
int bat1_act[12];
int bat2_act[12];
int bat2_motion[] = { 0,1,2,1 };
int bat2_index = 0;
int bat2_wait = 1;
int bat2_dir = 0;
bool live[2] = { FALSE,FALSE }; //���ꂼ��̃R�E�����̐����Ă��邩�ǂ����t���O
bool killBat2[2] = { FALSE,FALSE }; //���ꂼ��̃R�E�������E�������ǂ����̃t���O


//�A�C�e��(�N���X�^��)
float x_item; //x,y���W
float y_item;
int item_w = 32;//���A����
int item_h = 32;
bool isDrop = FALSE; //���Ƃ������ǂ���
int item_handle[12]; //�N���X�^���̉摜�n���h��
bool itemGet = FALSE; //�N���X�^������ɓ��ꂽ��

//�A�C�e���Q(�I�[�u)
float x_item2 = 90; //x,y
float y_item2 = 370;
int item2_w = 32; //���A����
int item2_h = 32;
int item2_handle[12]; //�I�[�u�̉摜�n���h��
bool item2Get = FALSE; //�I�[�u����ɓ��ꂽ��


//�^�C�g����ʒ�`
//�^�C�g����ʃn���h��
int titleHandle;
int title_x = 100; //x,y
int title_y = 0;
int title_w = 597; //���A����
int title_h = 269;
bool showTitle = TRUE; //�^�C�g����\�����Ă��邩�ǂ���

//�L�����N�^������
void Chara_Init() {
	LoadDivGraph("obake.png", ACT_NUM_ALL, ACT_NUM_X, ACT_NUM_Y, chara_width, chara_height, chara_act);

}
//�G�L����������
void Enemy_Init() {
	LoadDivGraph("Enemy.png",ENE_NUM_ALL,ENE_NUM_X,ENE_NUM_Y,enemy_width,enemy_height,enemy_act);
}
//�R�E����������
void Bat_Init() {
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat_act);
}
//�R�E�����Q������
void Bat2_Init() {
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat1_act);
	LoadDivGraph("koumori.png", ENE_NUM_ALL, ENE_NUM_X, ENE_NUM_Y, enemy_width, enemy_height, bat2_act);
}
//�A�C�e��������
void Item_Init() {
	LoadDivGraph("pipo-etcchara002b.png", 12, 3, 4, 32, 32, item_handle); //�N���X�^�������[�h
	LoadDivGraph("pipo-etcchara002b.png", 12, 3, 4, 32, 32, item2_handle);//�I�[�u�����[�h
}

//�^�C�g����ʃ��[�h
void Title_Init() {
	titleHandle = LoadGraph("�e�ۓ˔j�o���b�g�`���C�X�@�^�C�g�����.png");
}

//�e�ۂ̑��x�ƌ������L������ϐ�
float speed = 3.0f;
int direct = 3; //0:��@1:���@2:�E�@3:�Ȃ�
int direct_Brack = 3; //�Í��e��
int direct_Bullet = 3; //���e��

//�L�����N�^�ړ�
void Chara_Move() {
	//�O�̈ʒu
	old_x = x;
	old_y = y;

	//��ʂ̊O�ɍs���Ή�ʓ��ɖ߂�
	if (y > 600) y = 500;
	if (x > 800) x = 100;
	if (x < 0) x = 700;

	//�L�[�����擾
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (showTitle == FALSE) { //�^�C�g�����\������Ă��Ȃ����(�^�C�g�����Ԃ��󂵂Ă����瓮������)
		if (input & PAD_INPUT_RIGHT) { //�E�ړ�
			x++;
			act_dir = 2;
		}
		if (input & PAD_INPUT_LEFT) { //���ړ�
			x--;
			act_dir = 1;
		}
	}
	//�������(���ʂ�����)
	if (input & PAD_INPUT_UP) {
		act_dir = 0;
	}

	//�e���o�Ă��Ȃ��Ƃ�
	if (isShot == false) {

		//�e��\��
		if (input & PAD_INPUT_B) {
			PlaySoundMem(shotSEHandle, DX_PLAYTYPE_BACK);
			shot_x = x + 16;
			shot_y = y + 16;
			isShot = true;
		}
	}

	//�e���o�Ă��Ȃ��Ƃ��Q
	if (isShot2== false && canShotBrackball == true) { //�Í��e�͌��Ă邪�A�܂������ĂȂ���Ԃ̂Ƃ�

		//�e��\��
		if (input & PAD_INPUT_C){
			PlaySoundMem(shotBrackSEHandle, DX_PLAYTYPE_BACK);
			shotBrack_x = x + 16;
			shotBrack_y = y + 16;
			isShot2= true;
		}
	}
	
	//�e���o�Ă��Ȃ��Ƃ��R
	if (canShotBulletFlag == 1) { //���e�����Ă�Ƃ�
		if (isShot3 == false) { //�܂������ĂȂ��Ƃ�

			//�e��\��
			if (input & PAD_INPUT_X) {
				PlaySoundMem(shotBulletSEHandle, DX_PLAYTYPE_BACK);
				shotBullet_x = x + 16;
				shotBullet_y = y + 16;
				isShot3 = true;
			}
		}
	}
	//�ʏ�e
	if (isShot && direct == 3) {
		if (act_dir == 2) { //�E�������Ă�����
			direct = 2; //�e�������Œ�
		}
		if (act_dir == 1) { //���������Ă�����
			direct = 1;
		}
		if (act_dir == 0) {
			direct = 0;
		}
	}
	//�e�̌���(direct�̒l)�ɂ���čs�悪�ς��
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

	//�e����ʊO�ɏo����
	if (shot_x > 800 || shot_x < 0 || shot_y < 0) {
		isShot = false;
		direct = 3; //�e������������
	}
	//�������~�߂�e(�Í��e)
	if (isShot2 && direct_Brack == 3){
		if (act_dir == 2) { //�E�������Ă�����
			direct_Brack = 2;
		}
		if (act_dir == 1) { //���������Ă�����
			direct_Brack = 1;
		}
		if (act_dir == 0) {
			direct_Brack = 0;
		}
	}
	//�����ɂ���čs�����ς���
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
	//�Í��e����ʊO�ɏo�������
	if (shotBrack_x > 800 || shotBrack_x < 0 || shotBrack_y < 0) {
		isShot2 = false;
		direct_Brack = 3;
	}

	//���e�̏ꍇ
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
	//���e�̌����ɂ���čs�����ς���
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
	//���e����ʊO�ɏo�������
	if (shotBullet_x > 800 || shotBullet_x < 0 || shotBullet_y > 800 || shotBullet_y < 0) {
		isShot3 = false;
		direct_Bullet = 3;
	}

	//�W�����v����
	if (showTitle == FALSE) {
		if (!jFlag) {
			if (input & PAD_INPUT_A) {
				PlaySoundMem(jumpSEHandle, DX_PLAYTYPE_BACK);
				yadd = initVy;
				jFlag = true;
			}
			y += yadd;
			yadd += gravity;
			yadd = std::min(30.0f, std::max(-30.0f, yadd)); //�ۂ�
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

//�L�����N�^�A�j���[�V�����X�V
void Chara_Ani() {
	if (--act_wait <= 0) {
		act_index++;
		act_wait = ACT_SPEED;
		act_index %= MAX_MOTION_INDEX;
	}
}


//�L�����N�^�X�V
void Chara_Update() {
	if (damaged) {
		y += 3.0;
		return;
	}
	Chara_Move();
	Chara_Ani();
}

//�L�����N�^�`��
void Chara_Draw() {
	if (gameCrear) return;

	int motion_index = act_motion[act_index];

	DrawGraph(x, y, chara_act[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
}
//�S�[�X�g�̈ړ��֐�
void Enemy_Move() {

	const float speed = 1.0f;
	if (enemyLive) { //�����Ă��邩�ǂ���
		
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
//�ŏ��̃R�E�����p
bool isBottom = FALSE; //���ꂼ�ꉺ�ɂ��邩�A��ɂ��邩�A���ɂ��邩�A�E�ɂ��邩�m�F����t���O
bool isTop = TRUE;
bool isLeft = TRUE;
bool isRight = FALSE;
bool migikara;//�E����~��Ă�����
bool hidarikara;//������~��Ă�����

//�R�E�����Q�̂P�p
bool isBottom1 = FALSE; //���ꂼ�ꉺ�ɂ��邩�A��ɂ��邩�A���ɂ��邩�A�E�ɂ��邩�m�F����t���O
bool isTop1 = TRUE;
bool isLeft1 = TRUE;
bool isRight1 = FALSE;
bool migikara1;//�E����~��Ă�����
bool hidarikara1;//������~��Ă�����
bool isBind = FALSE;

//�R�E�����Q�̂Q�p
bool isBottom2 = FALSE; //���ꂼ�ꉺ�ɂ��邩�A��ɂ��邩�A���ɂ��邩�A�E�ɂ��邩�m�F����t���O
bool isTop2 = TRUE;
bool isLeft2 = TRUE;
bool isRight2 = FALSE;
bool migikara2;//�E����~��Ă�����
bool hidarikara2;//������~��Ă�����
bool isBind2 = FALSE;

void Bat_Move() {
	//�ŏ��̃R�E�����̋���
	if (enemy2Live) {
		if (x_bat == (SCREEN_WIDTH - enemy_width) / 2 - 100 && y_bat == (SCREEN_HEIGHT - enemy_height) / 2) { //����(�����ʒu)�ɂ���Ƃ�
			isBottom = FALSE;
			isTop = TRUE;
			isLeft = TRUE;
			isRight = FALSE;
		}

		if (isBottom == FALSE && isTop == TRUE && isLeft == TRUE && isRight == FALSE) { //���ォ�牺�֍~��Ă���
			x_bat += 0.5f;
			y_bat += 1.5f;
		}
		if (y_bat == 500) { //��ԉ��ɍs�����Ƃ�
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
		if (isBottom == TRUE && isTop == FALSE && migikara == FALSE && hidarikara == TRUE) { //������~��Ă����Ƃ�
			x_bat += 0.5f;
			y_bat -= 1.5f;
		}
		if (isBottom == TRUE && isTop == FALSE && migikara == TRUE && hidarikara == FALSE) { //�E����~��Ă����Ƃ�
			x_bat -= 0.5f;
			y_bat -= 1.5f;
		}
		if (x_bat != (SCREEN_WIDTH - enemy_width) / 2 - 100 && y_bat == (SCREEN_HEIGHT - enemy_height) / 2) { //�E��ɂ���Ƃ�
			isRight = TRUE;
			isLeft = FALSE;
			isBottom = FALSE;
			isTop = TRUE;
		}
		if (isRight == TRUE && isLeft == FALSE) { //�E�ォ�牺�Ɍ�����
			x_bat -= 0.5f;
			y_bat += 1.5f;
		}	
	}
	//�R�E�����Q�̂P�̋���
	if (live[0]) {
		if (!isBind) {
			if (x_bat2[0] == 100.0f && y_bat2[0] == 200.0f) { //����(�����ʒu)�ɂ���Ƃ�
				isBottom1 = FALSE;
				isTop1 = TRUE;
				isLeft1 = TRUE;
				isRight1 = FALSE;
			}

			if (isBottom1 == FALSE && isTop1 == TRUE && isLeft1 == TRUE && isRight1 == FALSE) { //���ォ�牺�֍~��Ă���
				x_bat2[0] += 0.5f;
				y_bat2[0] += 1.5f;
			}
			if (y_bat2[0] == 500) { //��ԉ��ɍs�����Ƃ�
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
			if (isBottom1 == TRUE && isTop1 == FALSE && migikara1 == FALSE && hidarikara1 == TRUE) { //������~��Ă����Ƃ�
				x_bat2[0] += 0.5f;
				y_bat2[0] -= 1.5f;
			}
			if (isBottom1 == TRUE && isTop1 == FALSE && migikara1 == TRUE && hidarikara1 == FALSE) { //�E����~��Ă����Ƃ�
				x_bat2[0] -= 0.5f;
				y_bat2[0] -= 1.5f;
			}
			if (x_bat2[0] != 100.0f && y_bat2[0] == 200.0f) { //�E��ɂ���Ƃ�
				isRight1 = TRUE;
				isLeft1 = FALSE;
				isBottom1 = FALSE;
				isTop1 = TRUE;
			}
			if (isRight1 == TRUE && isLeft1 == FALSE) { //�E�ォ�牺�Ɍ�����
				x_bat2[0] -= 0.5f;
				y_bat2[0] += 1.5f;
			}
		}
	}
	//�R�E�����Q�̂Q�̋���
	if (live[1]) {
		if (!isBind2) {
			if (x_bat2[1] == 500.0f && y_bat2[1] == 200.0f) { //����(�����ʒu)�ɂ���Ƃ�
				isBottom2 = FALSE;
				isTop2 = TRUE;
				isLeft2 = TRUE;
				isRight2 = FALSE;
			}

			if (isBottom2 == FALSE && isTop2 == TRUE && isLeft2 == TRUE && isRight2 == FALSE) { //���ォ�牺�֍~��Ă���
				x_bat2[1] += 0.5f;
				y_bat2[1] += 1.5f;
			}
			if (y_bat2[1] == 500) { //��ԉ��ɍs�����Ƃ�
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
			if (isBottom2 == TRUE && isTop2 == FALSE && migikara2 == FALSE && hidarikara2 == TRUE) { //������~��Ă����Ƃ�
				x_bat2[1] += 0.5f;
				y_bat2[1] -= 1.5f;
			}
			if (isBottom2 == TRUE && isTop2 == FALSE && migikara2 == TRUE && hidarikara2 == FALSE) { //�E����~��Ă����Ƃ�
				x_bat2[1] -= 0.5f;
				y_bat2[1] -= 1.5f;
			}
			if (x_bat2[1] != 500.0f && y_bat2[1] == 200.0f) { //�E��ɂ���Ƃ�
				isRight2 = TRUE;
				isLeft2 = FALSE;
				isBottom2 = FALSE;
				isTop2 = TRUE;
			}
			if (isRight2 == TRUE && isLeft2 == FALSE) { //�E�ォ�牺�Ɍ�����
				x_bat2[1] -= 0.5f;
				y_bat2[1] += 1.5f;
			}
		}
	}
}

//�G�l�~�[�A�j���[�V�����X�V
void Enemy_Ani() {
	if (--ene_wait <= 0) {
		ene_index++;
		ene_wait = ACT_SPEED;
		ene_index %= MAX_ENE_MOTION_INDEX;
	}
}
//bat�A�j���[�V�����X�V
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
//�A�C�e���h���b�v�֐�
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

//�G�S�̂̕`��֐�
void Enemy_Draw() {
	int motion_index = ene_motion[ene_index];
	int motion_index2 = bat_motion[bat_index];
	int motion_index3 = bat2_motion[bat2_index];
	int motion_index4 = bat2_motion[bat2_index];
	//�S�[�X�g
	if (enemyLive){
	DrawGraph(x_enemy, y_enemy, enemy_act[motion_index + ene_dir * ENE_DIR_SLIDE], TRUE);
	}
	//�ŏ��̃R�E����
	if (enemy2Live && killBat == FALSE) {
		DrawRotaGraph(x_bat, y_bat, 1.0, 0.0, bat_act[motion_index2 + bat_dir * ENE_DIR_SLIDE], TRUE); //�摜�̕`��
	}
	//�R�E�����Q
	if (live[0] == TRUE && killBat2[0] == FALSE) {
		DrawRotaGraph(x_bat2[0], y_bat2[0], 1.0, 0.0, bat1_act[motion_index3 + bat2_dir * ENE_DIR_SLIDE], TRUE); //�摜�̕`��
	}
	if (live[1] == TRUE && killBat2[1] == FALSE) {
		DrawRotaGraph(x_bat2[1], y_bat2[1], 1.0, 0.0, bat2_act[motion_index4 + bat2_dir * ENE_DIR_SLIDE], TRUE); //�摜�̕`��

	}
}

//�A�C�e���̕`��֐�
void Item_Draw() {
	if (isDrop && itemGet == FALSE) {
		DrawRotaGraph(x_item, y_item, 1.0, 0.0, item_handle[7], TRUE);
	}
	if (item2Get == FALSE) {
		DrawRotaGraph(x_item2, y_item2, 1.0, 0.0, item_handle[10], TRUE);
	}
}

//������@�`��
void SosaHoho_Draw() {
	if (gameCrear == FALSE) {
		DrawFormatString(100, 580, GetColor(255, 255, 255), "�����L�[�F���E�ړ�");
		DrawFormatString(300, 580, GetColor(255, 255, 255), "Z�L�[�F�W�����v");
		DrawFormatString(450, 580, GetColor(255, 255, 255), "X�L�[�F�ʏ�e");
		if (canShotBrackball && canShotBulletFlag == 0) {
			DrawFormatString(600, 580, GetColor(255, 255, 255), "C�L�[�F�Í��e");
		}
		if (canShotBrackball && canShotBulletFlag == 1) {
			DrawFormatString(600, 580, GetColor(255, 255, 255), "C,A�L�[�F�Í��e,���e");
		}
	}
	else {
		DrawFormatString(100, 580, GetColor(255, 255, 255), "�G�X�P�[�v�L�[�F�Q�[���I��");
	}
}

//�^�C�g���`��֐�
void Draw_Title() {
	if (showTitle) {
		DrawGraph(title_x, title_y, titleHandle, FALSE);
	}
}

//�ǂ̃A�r���e�B(�ʏ�e��Í��e�Ȃ�)���g���邩�ǂ�����\������
void Abirity_Draw() {
	if (gameCrear) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�y�L�����N�^�[�E�}�b�v�`�b�v�z");
		DrawFormatString(0, 32, GetColor(255, 255, 255), "�҂ۂ�q�� �l");
		DrawFormatString(0, 64, GetColor(255, 255, 255), "�yBGM�ESE�z");
		DrawFormatString(0, 96, GetColor(255, 255, 255), "������ �l");
		DrawFormatString(0, 96+32+32, GetColor(255, 255, 255), "created by Daiki Nara");
	}
	else {
		DrawBox(0, 0, 200, 140, GetColor(125, 125, 125), TRUE);//�o�b�N�̒����`
		DrawRotaGraph(32, 32, 1.0, 0.0, item_handle[7], TRUE); //�N���X�^��(�Í��e�����Ă�A�C�e��)�̃A�C�R��
		DrawFormatString(64, 30, GetColor(0, 0, 0), "�F%d", canBrackBallFlag);
		if (canBrackBallFlag == 1) DrawFormatString(30, 47, GetColor(0, 0, 0), "(�u�Í��e�v���ˉ\)");

		DrawRotaGraph(32, 88, 1.0, 0.0, item_handle[10], TRUE); //�I�[�u(���e�����Ă�A�C�e��)�̃A�C�R��
		DrawFormatString(64, 80, GetColor(0, 0, 0), "�F%d", canShotBulletFlag);
		if (canShotBulletFlag == 1) DrawFormatString(30, 100, GetColor(0, 0, 0), "(�u���e�v���ˉ\)");
	}
}
//�����蔻��֐�
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
	//�S�[�X�g�Ɠ������Ă��邩�ǂ���
	if (enemyLive) {
		if (CheckHit(x, y, chara_width, chara_height, x_enemy, y_enemy, enemy_width, enemy_height) && count == 0) {
			speed -= 0.5;
			x -= 5;
			count = 10; //�J�E���^�[�Z�b�g

		}
		if (count > 0) {
			--count;
			if (count <= 0) {
				count = 0;
			}
		}
	}

	//�R�E�����Ɠ������Ă��邩�ǂ���
	if (enemy2Live) {
		if (CheckHit(x, y, chara_width, chara_height, x_bat, y_bat, enemy_width, enemy_height) && count == 0) {
			speed -= 0.2;
			x -= 5;
			count = 10; //�J�E���^�[�Z�b�g

		}
		if (count > 0) {
			--count;
			if (count <= 0) {
				count = 0;
			}
		}
	}
	if (live[0] == TRUE && killBat2[0] == FALSE) {
		//�Í��e�Ŏ~�܂����ꍇ�R�E�����Q�|�P
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
		else {//�Í��e�Ŏ~�܂��Ă��Ȃ��ꍇ�R�E�����Q�|�P
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[0], y_bat2[0], enemy_width, enemy_height) && count == 0) {
				damageCounter = 10; //�_���[�W�J�E���^�[�����̂Ƃ��̓_���[�W���󂯂Ă��遁�d��
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
		//�Í��e�Ŏ~�܂����ꍇ�R�E�����Q�|�Q
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
		else {//�Í��e�Ŏ~�܂��Ă��Ȃ��ꍇ�R�E�����Q�|�Q
			if (CheckHit(x, y, chara_width, chara_height, x_bat2[1], y_bat2[1], enemy_width, enemy_height) && count == 0) {
				damageCounter = 10; //�_���[�W�J�E���^�[�����̂Ƃ��̓_���[�W���󂯂Ă��遁�d��
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

//�A�C�e���Ƃ̓����蔻��
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

//�^�C�g����ʂƂ̓����蔻��
void CheckHitTitle() {
	if (CheckHit(shot_x, shot_y, 20, 20, title_x, title_y, title_w, title_h)) {
		showTitle = FALSE;
	}
}

//���e�Ƃ̓����蔻��
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
					else { //�����瓖�����Ă��邩
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
				//���e�ɐG�ꂽ�ꍇ�A����͔j�󂳂��
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
	//�S�[�X�g�ɍU��
	if (CheckHit(shot_x, shot_y, 20, 20, x_enemy, y_enemy, enemy_width, enemy_height)) {
		enemyLive = FALSE; 
		if (enemy2Live == FALSE) enemy2Live = TRUE;
	}
	//�R�E�����ɍU��
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat, y_bat, enemy_width, enemy_height)) {
		enemy2Live = FALSE;
		killBat = TRUE;
		Item_Drop(x_bat,y_bat); //�A�C�e���h���b�v
		if (live[0] == FALSE && live[1] == FALSE) { live[0] = TRUE; live[1] = TRUE; } //��3�E�F�[�u��
	}
	//�R�E�����Q�̂P�ɍU��(�ʏ�e)
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		if (isBind) {
			isBind = FALSE;
		} //��~����or���ʂȂ�
	}
	//�R�E�����Q�̂P�ɍU��(�Í��e)
	if (CheckHit(shotBrack_x, shotBrack_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		isBind = TRUE; //��~
	}
	//�R�E�����Q�̂P�ɍU��(���e)�œ|��
	if (CheckHit(shotBullet_x, shotBullet_y, 20, 20, x_bat2[0], y_bat2[0], enemy_width, enemy_height)) {
		killBat2[0] = TRUE;
	}
	//�R�E�����Q�̂Q�ɍU��(�ʏ�e)
	if (CheckHit(shot_x, shot_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		if (isBind2) {
			isBind2 = FALSE;
		} //��~����or���ʂȂ�
	}
	//�R�E�����Q�̂Q�ɍU��(�Í��e)
	if (CheckHit(shotBrack_x, shotBrack_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		isBind2 = TRUE; //��~
	}
	//�R�E�����Q�̂Q�ɍU��(���e)�œ|��
	if (CheckHit(shotBullet_x, shotBullet_y, 20, 20, x_bat2[1], y_bat2[1], enemy_width, enemy_height)) {
		killBat2[1] = TRUE;
	}
}

//�N���A����
void IsClear() {
	//��ʏ㕔�֍s������
	if (y < 0) {
		//�R�E�����Q�̓|���Ă�����
		if (killBat2[0] == TRUE && killBat2[1] == TRUE && gameCrear == FALSE) {
			StopSoundMem(bgmHandle);
			PlaySoundMem(clearSEHandle, DX_PLAYTYPE_BACK);
			gameCrear = TRUE;
		}
		else {
			y = 0;
			DrawBox(300, 0, 600, 100, GetColor(125, 100, 100), TRUE);//�o�b�N�̒����`
			DrawFormatString(300, 0, GetColor(255, 255, 255), "�q���g�F");
			DrawFormatString(300, 32, GetColor(0, 0, 255), "�G���������Ă���߂��Ă��āI");
		}
	}
}
//�G���h�����֐�
void End() {
	if (gameCrear) {
		//�N���A��ʕ\��
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
	
	SetWindowText("�e�ۓ˔j�o���b�g�`���C�X");

	SetGraphMode(SCREEN_WIDTH,SCREEN_HEIGHT,32);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	//�^�C�g����ʃ��[�h
	Title_Init();

	//�L�����N�^���[�h
	Chara_Init();
	
	//�G�l�~�[���[�h
	Enemy_Init();

	//�R�E�������[�h
	Bat_Init();

	//�R�E�����Q���[�h
	Bat2_Init();

	//�A�C�e�����[�h
	Item_Init();

	//�}�b�v������
	Map_Init();

	//BGM,SE������
	Music_Init();

	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

	//���C�����[�v///
	while (ProcessMessage() == 0) {
		//����ʏ���
		ClearDrawScreen();

		//�}�b�v�`��
		Map_Draw();

		//�L�����N�^�X�V
		Chara_Update();
		
		//�G�l�~�[�X�V
		Enemy_Update();

		//�G�l�~�[2�X�V
		Bat_Update();

		//�R�E�����Q�X�V
		Bat2_Update();

		//�u���b�N�̓����蔻��
		Map_HitCheck();

		//�U���̓����蔻��
		AttackHit();

		//�G�S�[�X�g�Ƃ̓����蔻��
		CheckHitEnemy();

		//�_���[�W���󂯂Ă��邩
		CheckDamage();

		//�A�C�e���Ƃ̓����蔻��
		CheckHitItem();

		//�^�C�g����ʂƂ̓����蔻��
		CheckHitTitle();

		//���e�Ƃ̓����蔻��
		CheckHitBullet();
		
		//�G�l�~�[�`��
		Enemy_Draw();

		//�A�C�e���`��
		Item_Draw();

		//�L�����N�^�`��
		Chara_Draw();

		//������@�`��
		SosaHoho_Draw();
		
		//�A�r���e�B�`��
		Abirity_Draw();

		//�^�C�g����ʕ`��
		Draw_Title();

		//�N���A����
		IsClear();
		
		//�G���h����
		End();

		ScreenFlip();
	}

	DxLib_End();
	return 0;

}
