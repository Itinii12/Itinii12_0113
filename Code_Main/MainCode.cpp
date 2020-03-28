//���̉ۑ�
//��ʍX�V���n�`+�L�������Ə�肭�s���ĂȂ��̂łǂ��ɂ�����(���΂���񂪓_�ł�������Ă�)
//����{���j�́A���ꂼ���\�������邽�߂̕`��̈��MakeScreen�Ŋm�ۂ��āA�K�؂ȃ^�C�~���O�ōX�V�����邱��
//�@�����AScreenFlip�̎d�l���\��ʁ̗���ʂ̔��f�݂̂��Ƃ�₱�������ƂɂȂ�A�v���؁B

//�e�X�g�p��`
//#define TEST

#include "DxLib.h"
#include <iostream>
#include <fstream>

//�F�̒�`
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//�t���O���̒�`
enum FLAG_NAME {
	GAME_END,
	TAROU_TALK,
	YAMADA_TALK,
	FLAG_MAX
};
bool FLAGS[FLAG_MAX];	//�t���O�Ǘ��p�̔z��

//�L�������Ǘ��N���X
class Charactor {
public:
	int chara_pic;	//�L�����摜
	int chara_x;	//�L�������W(x)
	int chara_y;	//�L�������W(y)
	Charactor()
	{
		chara_pic = 0;
		chara_x = 0;
		chara_y = 0;
	}
};

//�e�X�g�Q�[���Ŏg���L�����N�^����
Charactor Obatyan;

//�v���g�^�C�v�錾
void disp_msg(const char* charname, const char* msg);
bool create_map(const char* map_file_name);

//----------//
//���C������//
//----------//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���[�J���ϐ���`��

	//��ʃT�C�Y���E�B���h�E���[�h��
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	//�`���ʂ𗠂�
	SetDrawScreen(DX_SCREEN_BACK);

	//�^�C�g����ʏ���
	LoadGraphScreen(0, 0, "Picture/title.bmp", TRUE);
	DrawString(100, 260, "�Q�[�����J�n����ɂ͉����L�[�������Ă�������...", BLACK);
	ScreenFlip();
	WaitKey();

	ClearDrawScreen();
	ScreenFlip();

	//�\���摜�n���h���ǂݍ���
	Obatyan.chara_pic = LoadGraph("Picture/walking6_oldwoman.png");
	//���C���������J�n
	while (FLAGS[GAME_END] == 0) {
		//�L�[������
		if (CheckHitKey(KEY_INPUT_UP) == 1)     Obatyan.chara_y -= 10;	//��L�[
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   Obatyan.chara_y += 10;	//���L�[
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  Obatyan.chara_x += 10;	//�E�L�[
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   Obatyan.chara_x -= 10;	//���L�[
		//���E�l����
		if (Obatyan.chara_y <= 0)Obatyan.chara_y = 0;
		if (Obatyan.chara_x <= 0)Obatyan.chara_x = 0;
		if (Obatyan.chara_y >= 450)Obatyan.chara_y = 450;
		if (Obatyan.chara_x >= 610)Obatyan.chara_x = 610;

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Z�L�[
			disp_msg("HANAKO", "����ɂ��́I\n2�s�̃e�X�g���b�Z�[�W�ł��I");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESC�L�[

		WaitTimer(1);

		ClearDrawScreen();
		create_map("Picture/Map01.bmp");
		//���W�ɕ`�悷��
		DrawExtendGraph(0 + Obatyan.chara_x, 0 + Obatyan.chara_y, 30 + Obatyan.chara_x, 30 + Obatyan.chara_y, Obatyan.chara_pic, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}

//�C�ӂ̃��b�Z�[�W��\������֐�
void disp_msg(const char* charname, const char* msg) {
	//NameBox��`��
	DrawBox(30, 295, 100, 325, BLUE, TRUE);
	DrawBox(30, 295, 100, 325, WHITE, FALSE);
	//MsgBox��`��
	DrawBox(10, 320, 630, 470, BLUE, TRUE);
	DrawBox(10, 320, 630, 470, WHITE, FALSE);

	// �L�������\��
	DrawString(35, 300, charname, WHITE);
	//���b�Z�[�W�\��
	DrawString(20, 340, msg, WHITE);
	ScreenFlip();
	//���̃L�[���͂���������ƕςȋ����ɂȂ�̂ł�����Ƒ҂�
	WaitTimer(100);

	//Z�L�[���������܂ŕ\����������
	while (CheckHitKey(KEY_INPUT_Z) == 0) {
	}

	ClearDrawScreen();
	create_map("Picture/Map01.bmp");
	//���W�ɕ`�悷��
	DrawExtendGraph(0 + Obatyan.chara_x, 0 + Obatyan.chara_y, 30 + Obatyan.chara_x, 30 + Obatyan.chara_y, Obatyan.chara_pic, TRUE);
	ScreenFlip();
}

//�n�`�����֐�
//�P�s�N�Z������RGB���擾���āA��ʍ��ォ�疄�߂Ă���
//�g�p����̂�24bitBMP�t�@�C��
bool create_map(const char* map_file_name) {
	std::FILE* fp;	      //�}�b�v�f�[�^�p�̃t�@�C���|�C���^
	errno_t err_code;     //�e�֐��̃G���[�R�[�h�i�[�p
	BITMAPFILEHEADER bf;  //BitMap�t�@�C���w�b�_�[
	BITMAPINFOHEADER bi;  //BitMap���w�b�_�[
	//RGBQUAD rgb;		  //�p���b�g�f�[�^�͐F�r�b�g����1,4,8�̏ꍇ�̂ݑ��݁B�����舵���̂�24bit��BMP�Ȃ̂ŕs�v�B
	int x, y = 0;		  //�����p
	u_int color = 0;      //�F�f�[�^�쐬�p
	typedef struct {
		u_char b,g,r;
	}BGR_MAP;
	BGR_MAP         bgr_map;  //BitMapBGR�f�[�^(RGB�ł͂Ȃ�)(RGB�ł͂Ȃ�)

	//�}�b�v�t�@�C�����J��
	fopen_s(&fp, map_file_name, "r");
	if (fp != NULL) {
		//�t�@�C���w�b�_�ǂݍ���
		err_code = fread_s(&bf, sizeof bf, sizeof BITMAPFILEHEADER, 1, fp);
		//���w�b�_�ǂݍ���
		err_code = fread_s(&bi, sizeof bi, sizeof BITMAPINFOHEADER, 1, fp);
		long map_width = bi.biWidth;	//�悱
		long map_height = bi.biHeight;	//����

		//�摜�f�[�^���T�C�Y���ǂݍ���
		for (y = 0; y <= map_height; y++) {
			for (x = 0; x < map_width; x++) {
				err_code = fread_s(&bgr_map, sizeof bgr_map, sizeof BGR_MAP, 1, fp);
				color = GetColor((int)bgr_map.r, (int)bgr_map.g, (int)bgr_map.b);
				DrawPixel(x, map_height - y, color);
			}
		}
		fclose(fp);
		return TRUE;
	}
	else {
		//�k���|�̏ꍇ
		return FALSE;
	}

	
}