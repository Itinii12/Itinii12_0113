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
bool FLAGS[FLAG_MAX];

//�C�ӂ̃��b�Z�[�W��\������֐�
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
	int Result = 0;	 //�X�N���[���ύX����
	int Picture = 0; //�摜�\���n���h��
	int x = 0;
	int y = 0;

	Result = ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1){  
		return -1;			  
	}
	SetDrawScreen(DX_SCREEN_BACK);

	if (Result == DX_CHANGESCREEN_OK) {
		DrawString(10, 10, "��ʃT�C�Y�ύX�ɐ������܂���\n���s����ɂ͉����L�[�������Ă�������...", WHITE);
		ScreenFlip();
	}

	WaitKey();
	ClearDrawScreen();

	//�\���摜�n���h���ǂݍ���
	Picture = LoadGraph("Picture/walking6_oldwoman.png");

	//���C���������J�n
	while (FLAGS[GAME_END] == 0) {
		//�L�[������
		if (CheckHitKey(KEY_INPUT_UP) == 1)     y -= 10;	//��L�[
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   y += 10;	//���L�[
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  x += 10;	//�E�L�[
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   x -= 10;	//���L�[

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Z�L�[
			disp_msg("HANAKO", "����ɂ��́I\n2�s�̃e�X�g���b�Z�[�W�ł��I");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESC�L�[
		ClearDrawScreen();
		DrawExtendGraph(0+x, 0+y, 20+x, 20+y, Picture, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}