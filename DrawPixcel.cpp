#include "DxLib.h"

//�F�̒�`
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//�t���O���̒�`
enum FLAG_NAME{
	GAME_END,
	TAROU_TALK,
	YAMADA_TALK,
	FLAG_MAX
};
bool FLAGS[FLAG_MAX];	//�t���O�Ǘ��p�̔z��

//�C�ӂ̃��b�Z�[�W��\������֐�
//����ۑ�:���b�Z�[�W�\��������ɁA���b�Z�[�W���E�B���h�E��������
//+�����Ƃ��ɂ�Z�L�[���������Ƃ����������悤�ɂ��A�A���Ń��b�Z�[�W���o�Ȃ��悤�ɂ���B
void disp_msg(const char* charname,const char* msg) {

	DrawBox(30, 295, 100, 325, BLUE, TRUE);	//NameBox��`��
	DrawBox(30, 295, 100, 325, WHITE, FALSE);
	DrawBox(10, 320, 630, 470, BLUE, TRUE);	//MsgBox��`��
	DrawBox(10, 320, 630, 470, WHITE, FALSE);

	DrawString(35, 300, charname, WHITE);	//�L�������\��
	DrawString(20, 340, msg, WHITE);		//���b�Z�[�W�\��

	ScreenFlip();
	WaitKey();
	ClearDrawScreen();
	ScreenFlip();
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�ϐ���`��
	int Picture = 0; //�摜�\���n���h��
	int x = 0;
	int y = 0;

	ChangeWindowMode(TRUE);	//��ʃT�C�Y���E�B���h�E���[�h��
	if (DxLib_Init() == -1){  
		return -1;			  
	}
	SetDrawScreen(DX_SCREEN_BACK);	//�`���ʂ𗠂�

	//�^�C�g����ʏ���
	LoadGraphScreen(0,0,"Picture/title.bmp",TRUE);
	DrawString(100,260,"�Q�[�����J�n����ɂ͉����L�[�������Ă�������...",BLACK);
	ScreenFlip();
	WaitKey();

	ClearDrawScreen();
	ScreenFlip();

	//�\���摜�n���h���ǂݍ���
	Picture = LoadGraph("Picture/walking6_oldwoman.png");

	//���C���������J�n
	while (FLAGS[GAME_END] == 0) {
		//�L�[������
		if (CheckHitKey(KEY_INPUT_UP) == 1)     y -= 10;	//��L�[
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   y += 10;	//���L�[
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  x += 10;	//�E�L�[
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   x -= 10;	//���L�[
		//���E�l����
		if (y <= 0)y = 0;
		if (x <= 0)x = 0;
		if (y >= 450)y = 450;
		if (x >= 610)x = 610;

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Z�L�[
			disp_msg("HANAKO", "����ɂ��́I\n2�s�̃e�X�g���b�Z�[�W�ł��I");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESC�L�[

		WaitTimer(10);
		ClearDrawScreen();
		DrawExtendGraph(0+x, 0+y, 30+x, 30+y, Picture, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}